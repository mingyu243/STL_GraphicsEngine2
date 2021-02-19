#include <d3dcompiler.h>

#include "PixelShader.h"

PixelShader::PixelShader()
    : Shader()
{
}

PixelShader::PixelShader(std::wstring filename)
    : Shader(filename)
{
    profile = "ps_5_0";
}

PixelShader::PixelShader(std::wstring filename, std::string entry, std::string profile)
    : Shader(filename, entry, profile), pixelShader(0)
{
}

PixelShader::~PixelShader()
{
}

bool PixelShader::Compile(ID3D11Device* device)
{
    // PS 컴파일
    HRESULT result = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        entry.c_str(),
        profile.c_str(),
        NULL,
        NULL,
        &shaderBuffer,
        NULL
    );
    if (FAILED(result)) 
    { 
        MessageBox(nullptr, L"픽셀 쉐이더 컴파일 실패", L"오류", 0);
        return false;
    }

    return true;
}

bool PixelShader::Create(ID3D11Device* device)
{
    // PS 생성.
    HRESULT result = device->CreatePixelShader(
        shaderBuffer->GetBufferPointer(), // 시작 지점 주소.
        shaderBuffer->GetBufferSize(), // 얼마만큼 읽을 지.
        nullptr,
        &pixelShader
    );
    if (FAILED(result)) 
    { 
        MessageBox(nullptr, L"픽셀 쉐이더 생성 실패", L"오류", 0); 
        return false;
    }

    return true;
}

void PixelShader::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->PSSetShader(pixelShader, NULL, NULL);
}
