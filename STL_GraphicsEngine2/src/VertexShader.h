#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader();
	VertexShader(std::wstring filename);
	VertexShader(std::wstring filename, std::string entry, std::string profile);
	~VertexShader();

	bool Compile(ID3D11Device* device) override;
	bool Create(ID3D11Device* device) override;
	void Bind(ID3D11DeviceContext* deviceContext) override;

	ID3D11VertexShader* GetVertexShader() { return vertexShader; }

private:
	ID3D11VertexShader* vertexShader;
};

