#include "ModelPTN.h"
#include "VertexPTN.h"

#include <vector>
#include "ResourceLoader.h"

ModelPTN::ModelPTN()
{
}

ModelPTN::~ModelPTN()
{
}

bool ModelPTN::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    return true;
}

bool ModelPTN::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName)
{
    std::vector<VertexPTN> vertices;
    std::vector<unsigned int> indices;

    // 리소스 로드.
    ResourceLoader::LoadModel(modelFileName, &vertices, &indices);

    // 버텍스 버퍼 생성.
    if (vertexBuffer.Initialize(device, vertices.data(), vertices.size(), sizeof(VertexPTN)) == false) // 크기 알려줘야 함.
    {
        return false;
    }

    // 인덱스 버퍼 생성.
    if (indexBuffer.Initialize(device, indices.data(), indices.size()) == false)
    {
        return false;
    }

    // 정점에 대한 명세 만들기 (입력 레이아웃).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        // 0, 12, 20 같은 거는 자동으로 계산하는 D3D11_APPEND_ALIGNED_ELEMENT 키워드가 있음.
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, // 앞에 position이 float 4개라서 12바이트니까 12.
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}, // position 12바이트 + texcoord 8바이트 = 20
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
