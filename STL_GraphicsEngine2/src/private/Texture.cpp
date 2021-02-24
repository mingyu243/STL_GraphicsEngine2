#include "Texture.h"
#include "..\public\Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::LoadTextureFromFile(ID3D11Device* device)
{
    textureResource = ResourceLoader::LoadTextureFromFile(device, filename);

    if (textureResource == nullptr)
    {
        return false;
    }

    return true;
}
