#pragma once

#include "Shader.h"

class PixelShader : public Shader
{
public:
	PixelShader();
	PixelShader(std::wstring filename);
	PixelShader(std::wstring filename, std::string entry, std::string profile);
	~PixelShader();

	bool Compile(ID3D11Device* device) override;
	bool Create(ID3D11Device* device) override;
	void Bind(ID3D11DeviceContext* deviceContext) override;

	ID3D11PixelShader* GetPixelShader() { return pixelShader; }

private:
	ID3D11PixelShader* pixelShader;
};

