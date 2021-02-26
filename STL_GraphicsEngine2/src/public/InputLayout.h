#pragma once

#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class InputLayout
{
public:
	bool Initialize(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layout, int count, ID3DBlob* vertexShaderBuffer);
	void Bind(ID3D11DeviceContext* deviceContext);

	ID3D11InputLayout* Get() { return inputLayout.Get(); }
	ID3D11InputLayout** GetAddressOf() { return inputLayout.GetAddressOf(); }

private:
	ComPtr<ID3D11InputLayout> inputLayout;
};

