#include "Engine.h"
#include <d3dcompiler.h>

#include "Vertex.h"

#include "InputProcessor.h"

#include "MathUtil.h"

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
           
            Update();
            DrawScene();
        }
    }

    return 0;
}

void Engine::Update()
{
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
    modelPTN.UpdateBuffers(deviceContext.Get());

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
    lightBuffer.data.position.y = lightXPos;
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
    diffuseShader.Bind(deviceContext.Get());
    modelPTN.RenderBuffers(deviceContext.Get());

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
    camera.SetPosition(0.0f, 0.0f, -200.0f);

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

    if (diffuseShader.Initialize(device.Get(), L"T_CharM_Warrior_D.TGA") == false)
    {
        return false;
    }

    if (modelPTN.InitializeBuffers(device.Get(), diffuseShader.ShaderBuffer(), "SK_CharM_Warrior.fbx") == false)
    {
        return false;
    }
    modelPTN.SetPosition(0.0f, -90.0f, 0.5f);
    modelPTN.SetRotation(-90.0f, 0.0f, 0.0f);
    modelPTN.SetScale(1.0f, 1.0f, 1.0f);

    return true;
}
