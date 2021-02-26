#pragma once

#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class IndexBuffer
{
public:
	bool Initialize(ID3D11Device* device, void* data, int count);
	void Bind(ID3D11DeviceContext* deviceContext);

	int Count() { return count; }

	ID3D11Buffer* Get() { return buffer.Get(); }
	ID3D11Buffer** GetAddressOf() { return buffer.GetAddressOf(); }

private:
	int count;
	ComPtr<ID3D11Buffer> buffer;
};

