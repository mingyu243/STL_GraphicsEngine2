#include "LightBuffer.h"

bool LightBuffer::Create(ID3D11Device* device)
{
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.ByteWidth = sizeof(LightData);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    // 상수 버퍼에 담을 데이터.
    D3D11_SUBRESOURCE_DATA bufferData;
    ZeroMemory(&bufferData, sizeof(bufferData));
    bufferData.pSysMem = &data;

    HRESULT result = device->CreateBuffer(
        &desc,
        &bufferData,
        buffer.GetAddressOf()
    );

    if (FAILED(result))
    {
        MessageBox(nullptr, L"라이트 버퍼 생성 실패", L"오류", 0);
        return false;
    }

    return true;
}

void LightBuffer::Bind(ID3D11DeviceContext* deviceContext)
{
    // 데이터를 버퍼에 업데이트한다.
    deviceContext->UpdateSubresource(
        buffer.Get(),
        0,
        NULL,
        &data,
        0,
        0
    );

    // 버퍼를 등록한다.
    deviceContext->PSSetConstantBuffers(
        0,
        1, 
        buffer.GetAddressOf()
    );
}
