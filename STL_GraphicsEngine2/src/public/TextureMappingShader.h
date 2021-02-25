#pragma once

#include "VertexShader.h"
#include "PixelShader.h"

#include <string>

// Wrapping 감싸는 코드.
// 래퍼 (Wrapper).
class TextureMappingShader
{
public:
	// 컴파일 / 생성 한번에. 편의 함수.
	bool Initialize(ID3D11Device* device, std::wstring textureFileName);

	bool Compile(ID3D11Device* device, std::wstring textureFileName);
	bool Create(ID3D11Device* device);
	void Bind(ID3D11DeviceContext* deviceContext);

	ID3DBlob* ShaderBuffer();

private:
	VertexShader vertexShader;
	PixelShader pixelShader;
};

