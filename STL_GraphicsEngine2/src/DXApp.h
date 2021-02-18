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

	// �������̽�
	virtual int Run() = 0; // ���� ���� �Լ�.

protected:
	virtual void Update() = 0;
	virtual void DrawScene() = 0;

	bool InitializeDirect3D();

	ID3D11Device* device;						// d3d ��ġ.
	ID3D11DeviceContext* deviceContext;			// d3d ��ġ����.
	IDXGISwapChain* swapChain;					// ����ü��.
	ID3D11RenderTargetView* renderTargetView;	// ����Ÿ��.

	D3D11_VIEWPORT viewport;					// ����Ʈ (ȭ��)
};

