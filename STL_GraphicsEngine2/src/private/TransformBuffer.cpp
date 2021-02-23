#include "TransformBuffer.h"

bool TransformBuffer::Create(ID3D11Device* device)
{
    // 상수 버퍼.
    D3D11_BUFFER_DESC transformBufferDesc;
    ZeroMemory(&transformBufferDesc, sizeof(transformBufferDesc));
    transformBufferDesc.ByteWidth = sizeof(Matrix4f);
    transformBufferDesc.CPUAccessFlags = 0;
    transformBufferDesc.MiscFlags = 0;
    transformBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    transformBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // 단위 행렬.
    transformMatrix = Matrix4f::Identity();

    // 데이터 담기.
    D3D11_SUBRESOURCE_DATA transformBufferData;
    ZeroMemory(&transformBufferData, sizeof(transformBufferData));
    transformBufferData.pSysMem = &transformMatrix;

    // 버퍼 생성.
    HRESULT result = device->CreateBuffer(
        &transformBufferDesc,
        &transformBufferData,
        constantBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"상수 버퍼 생성 실패", L"오류", 0);
        return false;
    }

    return true;
}

void TransformBuffer::Bind(ID3D11DeviceContext* deviceContext)
{
    // 행렬 데이터 업데이트.
    deviceContext->UpdateSubresource(constantBuffer.Get(), 0, NULL, &transformMatrix, 0, 0);

    // 행렬 데이터가 담긴 버퍼 바인딩. (설정.)
    deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
}
