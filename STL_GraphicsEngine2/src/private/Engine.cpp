#include "Engine.h"
#include <d3dcompiler.h>

#include "Vertex.h"

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
            Update();
            DrawScene();
        }
    }

    return 0;
}

void Engine::Update()
{
}

void Engine::DrawScene()
{
    // 색상 고르기.
    float backgroundColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f };
    
    // 지우기 (Clear) - 실제로는 덮어씌워서 색칠하기.
    // Begin Draw(Render) - DX9.
    deviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);

    // 그리기 준비.
    vertexShader.Bind(deviceContext);
    pixelShader.Bind(deviceContext);

    // 그리기.
    mesh.RenderBuffers(deviceContext);

    // 프레임 바꾸기. FrontBuffer <-> BackBuffer.
    swapChain->Present(1, 0);
}

bool Engine::InitializeScene()
{
    vertexShader = VertexShader(L"..//shaders//BasicVS.hlsl", "main", "vs_5_0");
    pixelShader = PixelShader(L"..//shaders//BasicPS.hlsl", "main", "ps_5_0");

    // 컴파일
    if (vertexShader.Compile(device) == false)
    {
        return false;
    }
    if (pixelShader.Compile(device) == false)
    {
        return false;
    }
    // 생성
    if (vertexShader.Create(device) == false)
    {
        return false;
    }
    if (pixelShader.Create(device) == false)
    {
        return false;
    }

    // 메쉬 초기화
    if (mesh.InitializeBuffers(device, vertexShader.ShaderBuffer()) == false)
    {
        return false;
    }

    return true;
}
