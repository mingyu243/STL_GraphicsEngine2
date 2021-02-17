#include "DXApp.h"

DXApp::DXApp(HINSTANCE hInstance, int width, int height, std::wstring title)
{
    // Window 클래스에 값 전달.
    Window::SetInstance(hInstance);
    Window::SetWidth(width);
    Window::SetHeight(height);
    Window::SetTitle(title);
}

DXApp::~DXApp()
{

}

bool DXApp::Initialize()
{
    if (Window::InitializeWindow() == false)
    {
        return false;
    }
    if (InitializeDirect3D() == false)
    {
        return false;
    }
    return true;
}

bool DXApp::InitializeDirect3D()
{
    // 장치 생성.
    // Device - 생성.
    // DeviceContext - 값, 장치 설정.
    // SwapChain - 표시.

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;                          // 백버퍼 1개. Double Buffering. Screen Tearing.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // 사용 목적.
    swapChainDesc.OutputWindow = Window::WindowHandle();    // 출력할 윈도우 설정.
    swapChainDesc.Windowed = true;                          // 창 모드 설정.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;    // 효과 없음 (안 씀).

    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // 타입. RGBA를 8비트씩 써라. (0~255 값.) UNORM은 정규화. (0~255 값을 0~1로 바꿈.)
    swapChainDesc.BufferDesc.Width = Window::Width();               // 너비.
    swapChainDesc.BufferDesc.Height = Window::Height();             // 길이.

    swapChainDesc.SampleDesc.Count = 1;             // 멀티 샘플링 개수 1개. (안 쓴다는 말.) Anti-Alasing.
    swapChainDesc.SampleDesc.Quality = 0;           // Count - 1.

    // 장치 생성.
    HRESULT result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE, // 요즘엔 이거만 씀. 옛날 꺼 호환한다고 남아 있음.
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        NULL,
        &deviceContext
    );

    // 오류 검사.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"장치 생성 실패", L"오류", 0);
        return false;
    }

    // 백버퍼 생성?보다는 정보 받아오기. 
    // 우리는 백버퍼에 바로 못 그림. View를 통해 간접적으로 접근함.
    // 백버퍼 정보를 복사해서 주니까 받자.
    ID3D11Texture2D* backbufferTexture;
    result = swapChain->GetBuffer(
        NULL,
        __uuidof(ID3D11Texture2D), // 타입 정보 명시. uuidof : 여기에 백퍼버 정보 달라.
        (void**)(&backbufferTexture) // 타입에 상관없이 주소값을 받고 싶을 때 void 포인터.
    );

    // 오류 검사.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"백버퍼 정보 얻어오는데 실패", L"오류", 0);
        return false;
    }

    // 렌더 타겟 뷰(View)
    // 백버퍼에 직접 접근하지 못하기 때문에 뷰를 통해 정보 전달.
    result = device->CreateRenderTargetView(
        backbufferTexture,
        nullptr,
        &renderTargetView
    );

    // 오류 검사.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"렌더 타겟 뷰 생성 실패", L"오류", 0);
        return false;
    }

    // 임시 버퍼 해제.
    backbufferTexture->Release(); // delete 키워드와 하는 일이 같지만, Release로 해야 안전하게 해제 가능.

    // 렌더 타겟 뷰 할당.(설정)
    deviceContext->OMSetRenderTargets( // OM : Output Merge 합쳐준다는 의미.
        1, // 화면을 4개로 나눈다면, 4가 입력됨.
        &renderTargetView,
        nullptr
    );

    // 뷰포트(화면) - 크기 설정.
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)Window::Width();
    viewport.Height = (float)Window::Height();

    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    // 뷰포트 할당.
    deviceContext->RSSetViewports(1, &viewport);

    return true;
}
