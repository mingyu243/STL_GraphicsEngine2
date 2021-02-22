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
	int vertexCount;				// ���� ����.
	ComPtr<ID3D11Buffer> vertexBuffer;		// ���� ����.
	ComPtr<ID3D11InputLayout> inputLayout; // �Է� ���̾ƿ�.
};

