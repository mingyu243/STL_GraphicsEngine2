#include <d3dcompiler.h>

#include "VertexShader.h"

VertexShader::VertexShader()
	: Shader()
{
}

VertexShader::VertexShader(std::wstring filename)
	: Shader(filename)
{
	profile = "vs_5_0";
}

VertexShader::VertexShader(std::wstring filename, std::string entry, std::string profile)
	: Shader(filename, entry, profile), vertexShader(0)
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::Compile(ID3D11Device* device)
{
    // VS 컴파일
    HRESULT result = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        entry.c_str(),
        profile.c_str(),
        NULL,
        NULL,
        shaderBuffer.GetAddressOf(),
        NULL
    );
    if (FAILED(result)) { MessageBox(nullptr, L"정점 쉐이더 컴파일 실패", L"오류", 0); }

	return true;
}

bool VertexShader::Create(ID3D11Device* device)
{
    // VS 생성.
    HRESULT result = device->CreateVertexShader(
        shaderBuffer->GetBufferPointer(), // 시작 지점 주소.
        shaderBuffer->GetBufferSize(), // 얼마만큼 읽을 지.
        nullptr,
        vertexShader.GetAddressOf()
    );
    if (FAILED(result)) { MessageBox(nullptr, L"정점 쉐이더 생성 실패", L"오류", 0); }

	return true;
}

void VertexShader::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->VSSetShader(vertexShader.Get(), NULL, NULL);
}
