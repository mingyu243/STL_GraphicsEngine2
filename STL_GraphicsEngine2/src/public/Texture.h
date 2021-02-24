#pragma once

#include "ResourceLoader.h"
#include <string>

#include <wrl.h>

using Microsoft::WRL::ComPtr;

class Texture
{
public:
	Texture();
	~Texture();

	std::wstring filename;
	ComPtr<ID3D11ShaderResourceView> textureResource;

	bool LoadTextureFromFile(ID3D11Device* device);
};

