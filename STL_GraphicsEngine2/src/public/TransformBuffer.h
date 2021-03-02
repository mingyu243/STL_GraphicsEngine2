#pragma once

#include "Matrix4f.h"
#include <wrl.h>
#include <d3d11.h>

using Microsoft::WRL::ComPtr;

class TransformBuffer
{
public:
	Matrix4f transformMatrix;

	TransformBuffer()
	{
		memset(&transformMatrix, 0, sizeof(transformMatrix));
	}
	~TransformBuffer() = default;

	bool Create(ID3D11Device* device);
	void Bind(ID3D11DeviceContext* deviceContext);

private:
	ComPtr<ID3D11Buffer> constantBuffer;
};

