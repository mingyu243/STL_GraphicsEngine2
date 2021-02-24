#pragma once

#include "VertexShader.h"
#include "PixelShader.h"

#include <string>

// Wrapping 감싸는 코드.
// 래퍼 (Wrapper).
class TextureMappingShader
{
public:
	static bool Compile(ID3D11Device* device, std::wstring textureFileName);
	static bool Create(ID3D11Device* device);
	static void Bind(ID3D11DeviceContext* deviceContext);

	static ID3DBlob* ShaderBuffer();

private:
	static VertexShader vertexShader;
	static PixelShader pixelShader;
};

