#pragma once

#include "Window.h"
#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

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

	// 스마트 포인터 사용
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;

	ComPtr<ID3D11RenderTargetView> renderTargetView;	// 렌더타겟 뷰.
	ComPtr<ID3D11DepthStencilView> depthStencilView;	// 뎁스스텐실 뷰.

	D3D11_VIEWPORT viewport;					// 뷰포트 (화면)
};

