#include "QuadUV.h"
#include <VertexUV.h>

QuadUV::QuadUV()
{
}

QuadUV::~QuadUV()
{
}

bool QuadUV::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    // 정점 데이터 만들기.
    // 정점(Vertex) 배열.
    // 왼손 좌표계.
    VertexUV vertices[] =
    {
        VertexUV(Vector3f(-0.5f, -0.5f, 0.5f), Vector2f(0.0f, 1.0f)),
        VertexUV(Vector3f(-0.5f, 0.5f, 0.5f), Vector2f(0.0f, 0.0f)),
        VertexUV(Vector3f(0.5f, 0.5f, 0.5f), Vector2f(1.0f, 0.0f)),
        VertexUV(Vector3f(0.5f, -0.5f, 0.5f), Vector2f(1.0f, 1.0f))
    };
    if (vertexBuffer.Initialize(device, vertices, ARRAYSIZE(vertices), sizeof(VertexUV)) == false)
    {
        return false;
    } 

    // 인덱스 버퍼 생성.
    unsigned int indices[] =
    {
        0, 1, 2, // 시계 방향으로만 돌려주면 됌.
        0, 2, 3
    };
    if (indexBuffer.Initialize(device, indices, ARRAYSIZE(indices)) == false)
    {
        return false;
    }

    // 정점에 대한 명세 만들기 (입력 레이아웃).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} // 앞에 position이 float 4개라서 12바이트니까 12.
    };
    if (inputLayout.Initialize(device, layout, ARRAYSIZE(layout), vertexShaderBuffer) == false)
    {
        return false;
    }

    // 상수 버퍼.
    if (transform.Create(device) == false)
    {
        return false;
    }

    return true;
}
