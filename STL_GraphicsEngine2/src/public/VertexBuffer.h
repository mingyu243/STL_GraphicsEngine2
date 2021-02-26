#pragma once

#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class VertexBuffer
{
public:
    bool Initialize(ID3D11Device* device, void* data, int count, int elementByteWidth);
    void Bind(ID3D11DeviceContext* deviceContext);

    int Count() { return count; }
    unsigned int ElementByteWidth() { return elementByteWidth; }

    ID3D11Buffer* Get() { return buffer.Get(); }
    ID3D11Buffer** GetAddressOf() { return buffer.GetAddressOf(); }

private:
    int count;                              // 정점 개수.
    unsigned int elementByteWidth;          // 정점 배열 원소 바이트 수.
    ComPtr<ID3D11Buffer> buffer;            // DX11 버퍼.

};

