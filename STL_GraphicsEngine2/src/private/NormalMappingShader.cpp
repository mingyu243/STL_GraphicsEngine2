#include "NormalMappingShader.h"

bool NormalMappingShader::Initialize(ID3D11Device* device, std::wstring diffuseMapTexture, std::wstring normalMapTexture)
{
	vertexShader = VertexShader(L"..//shaders//NormalMappingVS.hlsl", "main", "vs_5_0");
	pixelShader = PixelShader(L"..//shaders//NormalMappingPS.hlsl", "main", "ps_5_0");

	if (Compile(device, diffuseMapTexture, normalMapTexture) == false)
	{
		return false;
	}
	if (Create(device) == false)
	{
		return false;
	}

	return true;
}

bool NormalMappingShader::Compile(ID3D11Device* device, std::wstring diffuseMapTexture, std::wstring normalMapTexture)
{
	if (vertexShader.Compile(device) == false)
	{
		return false;
	}
	if (pixelShader.Compile(device) == false)
	{
		return false;
	}

	// �ؽ��� �ε�.
	if (pixelShader.LoadTexture(device, diffuseMapTexture) == false)
	{
		return false;
	}
	if (pixelShader.LoadTexture(device, normalMapTexture) == false)
	{
		return false;
	}

	return true;
}

bool NormalMappingShader::Create(ID3D11Device* device)
{
	if (vertexShader.Create(device) == false)
	{
		return false;
	}
	if (pixelShader.Create(device) == false)
	{
		return false;
	}

	// ���÷� ������Ʈ ����.
	if (pixelShader.CreateSamplerState(device) == false)
	{
		return false;
	}

	return true;
}

void NormalMappingShader::Bind(ID3D11DeviceContext* deviceContext)
{
	vertexShader.Bind(deviceContext);
	pixelShader.Bind(deviceContext);
	pixelShader.BindTextures(deviceContext);
	pixelShader.BindSamplerState(deviceContext);
}

ID3DBlob* NormalMappingShader::ShaderBuffer()
{
	return vertexShader.ShaderBuffer();
}
