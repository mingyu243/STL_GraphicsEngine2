#pragma once

#include "Vertex.h"
#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer);
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

private:
	int vertexCount;				// 정점 개수.
	ComPtr<ID3D11Buffer> vertexBuffer;		// 정점 버퍼.
	ComPtr<ID3D11InputLayout> inputLayout; // 입력 레이아웃.
};

