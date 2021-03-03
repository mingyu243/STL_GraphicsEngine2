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

    // 스왑 체인 정보 설정. 설정양이 너무 많아서 구조체로 나눠놓았음.
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;                          // 백버퍼 1개. Double Buffering. Screen Tearing. 프론트버퍼, 백퍼버 합쳐서 총 2개 쓴다는 뜻.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // 사용 목적. 화면 출력용으로 쓴다는 뜻.
    swapChainDesc.OutputWindow = Window::WindowHandle();    // 출력할 윈도우 설정.
    swapChainDesc.Windowed = true;                          // 창 모드 설정.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;    // 프론트버퍼와 백버퍼를 바꿀 때, 효과 안 쓴다는 뜻. (요즘엔 빨라서 안 씀).

    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // 타입. RGBA를 8비트씩 써라. (0~255 값.) UNORM은 정규화. (0~255 값을 0~1로 바꿈.)
    swapChainDesc.BufferDesc.Width = Window::Width();               // 너비.
    swapChainDesc.BufferDesc.Height = Window::Height();             // 길이.

    swapChainDesc.SampleDesc.Count = 1;             // 멀티 샘플링 개수 1개. (안 쓴다는 말.) Anti-Alasing.
    swapChainDesc.SampleDesc.Quality = 0;           // Count - 1.

    // 장치 생성.
    HRESULT result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE, // 그래픽 가속기. 요즘엔 이거만 씀. 옛날 꺼 호환한다고 남아 있음.
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        swapChain.GetAddressOf(),
        device.GetAddressOf(),
        NULL,
        deviceContext.GetAddressOf()
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
    result = swapChain.Get()->GetBuffer(
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
    result = device.Get()->CreateRenderTargetView(
        backbufferTexture, // 여기에 정보 있고,
        nullptr,
        renderTargetView.GetAddressOf() // 거기에 맞춰서 생성해달라.
    );

    // 오류 검사.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"렌더 타겟 뷰 생성 실패", L"오류", 0);
        return false;
    }

    // 임시 버퍼(리소스) 해제.
    backbufferTexture->Release(); // delete 키워드와 하는 일이 같지만, Release로 해야 안전하게 해제 가능.

    // 뎁스 스텐실 뷰 (DepthStencilView)
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    memset(&depthStencilDesc, 0, sizeof(depthStencilDesc));
    depthStencilDesc.Width = Window::Width();
    depthStencilDesc.Height = Window::Height();
    depthStencilDesc.MipLevels = 1; // 밉맵. 원본 하나만 쓴다는 뜻.
    depthStencilDesc.ArraySize = 1; // 다른 리소스 쓰지 않고, 이것만 쓴다는 뜻.
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // D는 Depth(UNORM unsigned normalized), S는 Stencil. 24+8 총 32bit
    
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; // 사용 목적. 이 프로젝트에서는 모두 Default 값 사용 중.
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 뎁스 스텐실로 쓸 것이다.
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    // 뎁스 스텐실 버퍼 생성.
    ComPtr<ID3D11Texture2D> depthStecilBuffer;
    result = device.Get()->CreateTexture2D(
        &depthStencilDesc,
        NULL,
        depthStecilBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"뎁스 스텐실 버퍼 생성 실패", L"오류", 0);
        return false;
    }
    // 뎁스 스텐실 버퍼는 언제 채워지나?

    // 뎁스 스텐실 뷰 생성.
    result = device.Get()->CreateDepthStencilView(
        depthStecilBuffer.Get(),
        NULL,
        depthStencilView.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"뎁스 스텐실 뷰 생성 실패", L"오류", 0);
        return false;
    }

    // 렌더 타겟 뷰 할당.(설정)
    // 디퍼드 렌더링 | 포워드 렌더링.
    deviceContext.Get()->OMSetRenderTargets( // OM : Output Merger 합쳐준다는 의미. 얘는 성공 실패 반환 안 함.
        1, // 화면을 4개로 나눈다면, 4가 입력됨.
        renderTargetView.GetAddressOf(),
        depthStencilView.Get()
    );

    // 뷰포트(화면) - 크기 설정.
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)Window::Width();
    viewport.Height = (float)Window::Height();

    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    // 뷰포트 할당.
    deviceContext.Get()->RSSetViewports(1, &viewport); // RS : 레스터라이져

    return true;
}
