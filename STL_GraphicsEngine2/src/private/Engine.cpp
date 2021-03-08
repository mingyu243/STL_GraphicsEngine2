#include "Engine.h"
#include <d3dcompiler.h>

#include "Vertex.h"

#include "InputProcessor.h"

#include "MathUtil.h"

#include "GameTimer.h"

Engine::Engine(HINSTANCE hInstance, int width, int height, std::wstring title)
    : DXApp(hInstance, width, height, title)
{

}

Engine::~Engine()
{
}

bool Engine::Initialize()
{
    // 창 만들기.
    // 장치 생성.
    if (DXApp::Initialize() == false)
    {
        return false;
    }

    // 장면 초기화.
    if (InitializeScene() == false)
    {
        return false;
    }

    return true;
}

// 1. 메시지 처리 루프.
// 2. 엔진 루프.
int Engine::Run()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // 타이머 시작.
    GameTimer::Start();


    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // ESC 종료.
            if (InputProcessor::IsKeyDown(Keyboard::Keys::Escape) == true)
            {
                if (MessageBox(nullptr, L"종료하시겠습니까?", L"종료", MB_YESNO) == IDYES)
                {
                    DestroyWindow(Window::WindowHandle());
                    return 0;
                }
            }

            // 타이머 업데이트.
            GameTimer::Update();
           
            Update();
            DrawScene();
        }
    }

    return 0;
}

void Engine::Update()
{
    double deltaTime = GameTimer::DeltaTime();

    // 카메라 이동 처리.
    static float moveSpeed = 2.0f;
    if (InputProcessor::IsKeyDown(Keyboard::Keys::W) == true)
    {
        camera.MoveForward(moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::S) == true)
    {
        camera.MoveForward(-moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::A) == true)
    {
        camera.MoveRight(-moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::D) == true)
    {
        camera.MoveRight(moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::Q) == true)
    {
        camera.MoveUp(moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::E) == true)
    {
        camera.MoveUp(-moveSpeed);
    }

    // 카메라 회전 처리.
    Mouse::State state = InputProcessor::MouseState();
    static float rotationSpeed = 0.2f;
    if (state.leftButton == true)
    {
        camera.Yaw((float)state.x * rotationSpeed);
        camera.Pitch((float)state.y * rotationSpeed);
    }

    camera.UpdateCamera();
    modelPTN1.UpdateBuffers(deviceContext.Get());
    modelPTN2.UpdateBuffers(deviceContext.Get());
    modelPTN3.UpdateBuffers(deviceContext.Get());
    modelPTNBT.UpdateBuffers(deviceContext.Get());

    static float lightXPos = lightBuffer.data.position.x;
    static float direction = 1.0f;
    lightXPos += 10.0f * direction;
    if (lightXPos >= 500.0f)
    {
        direction = -1.0f;
    }
    if (lightXPos <= -500.0f)
    {
        direction = 1.0f;
    }
    lightBuffer.data.position.x = lightXPos;
}

void Engine::DrawScene()
{
    // 색상 고르기.
    float backgroundColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f };
    
    // 지우기 (Clear) - 실제로는 덮어씌워서 색칠하기.
    // Begin Draw(Render) - DX9.
    deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

    // 뎁스 지우기
    deviceContext.Get()->ClearDepthStencilView(
        depthStencilView.Get(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, // 비트 연산이 빠름.
        1.0f, 0 // 보통 뎁스는 1로 초기화, 스텐실은 0으로 초기화.
    );

    // 카메라 바인딩.
    camera.BindBuffer(deviceContext.Get());

    // 라이트 버퍼 바인딩.  
    lightBuffer.Bind(deviceContext.Get());

    // 그리기 준비. (쉐이더 바꾸기.)
    diffuseShader1.Bind(deviceContext.Get());
    modelPTN1.RenderBuffers(deviceContext.Get());

    diffuseShader2.Bind(deviceContext.Get());
    modelPTN2.RenderBuffers(deviceContext.Get());

    grassShader.Bind(deviceContext.Get());
    modelPTN3.RenderBuffers(deviceContext.Get());

    normalMappingShader.Bind(deviceContext.Get());
    modelPTNBT.RenderBuffers(deviceContext.Get());

    // 프레임 바꾸기. FrontBuffer <-> BackBuffer.
    swapChain.Get()->Present(1, 0);
}

bool Engine::InitializeScene()
{
    // 카메라 생성.
    camera = Camera(
        70.0f * MathUtil::Deg2Rad,
        (float)Window::Width(),
        (float)Window::Height(),
        0.1f,
        1000.0f
    );
    // 카메라 위치 설정.
    camera.SetPosition(100.0f, 0.0f, -200.0f);

    // 카메라 버퍼 생성.
    if (camera.CreateBuffer(device.Get()) == false)
    {
        return false;
    }

    lightBuffer.data.position = Vector3f(500.0f, 500.0f, -500.0f);
    if (lightBuffer.Create(device.Get()) == false)
    {
        return false;
    }

    if (diffuseShader1.Initialize(device.Get(), L"T_Char1_D.TGA") == false)
    {
        return false;
    }

    if (diffuseShader2.Initialize(device.Get(), L"T_Char2_D.png") == false)
    {
        return false;
    }

    if (grassShader.Initialize(device.Get(), L"T_Char2_D.png") == false)
    {
        return false;
    }

    if (normalMappingShader.Initialize(device.Get(), L"Char_M_Cardboard_D.png", L"Char_M_Cardboard_N.png") == false)
    {
        return false;
    }

    if (modelPTN1.InitializeBuffers(device.Get(), diffuseShader1.ShaderBuffer(), "Char1.fbx") == false)
    {
        return false;
    }
    modelPTN1.SetPosition(0.0f, -90.0f, 0.5f);
    modelPTN1.SetRotation(-90.0f, 0.0f, 0.0f);
    modelPTN1.SetScale(1.0f, 1.0f, 1.0f);

    if (modelPTN2.InitializeBuffers(device.Get(), diffuseShader2.ShaderBuffer(), "Char2.fbx") == false)
    {
        return false;
    }
    modelPTN2.SetPosition(120.0f, -90.0f, 0.5f);
    modelPTN2.SetRotation(0.0f, 0.0f, 0.0f);
    modelPTN2.SetScale(1.0f, 1.0f, 1.0f);

    if (modelPTN3.InitializeBuffers(device.Get(), grassShader.ShaderBuffer(), "Grass.fbx") == false)
    {
        return false;
    }
    modelPTN3.SetPosition(70.0f, -90.0f, 0.0f);
    modelPTN3.SetRotation(-90.0f, 0.0f, 0.0f);
    modelPTN3.SetScale(1.0f, 1.0f, 1.0f);

    if (modelPTNBT.InitializeBuffers(device.Get(), normalMappingShader.ShaderBuffer(), "SK_CharM_Cardboard.FBX") == false)
    {
        return false;
    }
    modelPTNBT.SetPosition(300.0f, -90.0f, 0.5f);
    modelPTNBT.SetRotation(-90.0f, 0.0f, 0.0f);
    modelPTNBT.SetScale(1.0f, 1.0f, 1.0f);

    return true;
}
