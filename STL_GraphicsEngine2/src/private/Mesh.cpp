#include "Mesh.h"

Mesh::Mesh()
	: vertexCount(0), vertexBuffer(0), inputLayout(0),
    transform(), // transform(TransformBuffer())랑 같음.
    position(Vector3f::Zero),
    rotation(Vector3f::Zero),
    scale(Vector3f::One)
{
}

Mesh::~Mesh()
{
}


void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
    BindBuffers(deviceContext);
    DrawBuffers(deviceContext);
}

void Mesh::BindBuffers(ID3D11DeviceContext* deviceContext)
{
    // Bind
    unsigned int stride = sizeof(Vertex); // 한번에 몇 개씩 읽을 지.
    unsigned int offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    deviceContext->IASetInputLayout(inputLayout.Get());
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 선을 그릴 때는 LineList.

    transform.Bind(deviceContext);
}

void Mesh::DrawBuffers(ID3D11DeviceContext* deviceContext)
{
    // Draw
    //deviceContext->Draw(vertexCount, 0); // 이게 DrawCall이다.
    deviceContext->DrawIndexed(indexCount, 0, 0);
}

void Mesh::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
    transform.transformMatrix = Matrix4f::Scale(scale) * Matrix4f::Rotation(rotation) * Matrix4f::Translation(position);
}

void Mesh::SetPosition(float x, float y, float z)
{
    position = Vector3f(x, y, z);
}

void Mesh::SetPosition(Vector3f position)
{
    this->position = position;
}

void Mesh::SetRotation(float x, float y, float z)
{
    rotation = Vector3f(x, y, z);
}

void Mesh::SetRotation(Vector3f rotation)
{
    this->rotation = rotation;
}

void Mesh::SetScale(float x, float y, float z)
{
    scale = Vector3f(x, y, z);
}

void Mesh::SetScale(Vector3f scale)
{
    this->scale = scale;
}
