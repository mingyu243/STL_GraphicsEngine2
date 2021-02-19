#pragma once

#include "Window.h"
#include <d3d11.h>

//#pragma comment(lib, "d3d11.lib")

class DXApp
{
public:
	DXApp(HINSTANCE hInstance, int width, int height, std::wstring title);

	virtual ~DXApp();

	virtual bool Initialize();

	// 인터페이스
	virtual int Run() = 0; // 완전 가상 함수.

protected:
	virtual void Update() = 0;
	virtual void DrawScene() = 0;

	bool InitializeDirect3D();

	ID3D11Device* device;						// d3d 장치.
	ID3D11DeviceContext* deviceContext;			// d3d 장치문맥.
	IDXGISwapChain* swapChain;					// 스왑체인.
	ID3D11RenderTargetView* renderTargetView;	// 렌더타겟.

	D3D11_VIEWPORT viewport;					// 뷰포트 (화면)
};

