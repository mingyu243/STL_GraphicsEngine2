#pragma once

#include "LightData.h"

#include <d3d11.h>
#include <wrl.h>

class LightBuffer
{
public:
	LightData data;

	LightBuffer() = default;
	~LightBuffer() = default;

	bool Create(ID3D11Device* device);
	void Bind(ID3D11DeviceContext* deviceContext);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
};

