#pragma once

#include <DirectXTex.h>
#include <string>

#include <d3d11.h>
#include <Windows.h>

class ResourceLoader
{
public:
	static ID3D11ShaderResourceView* LoadTextureFromFile(
		ID3D11Device* device,
		std::wstring filename
	);
	static std::wstring GetExtension(std::wstring str);

private:
	static HRESULT GetScratchImage(
		std::wstring filename,
		DirectX::ScratchImage* image
	);
};

