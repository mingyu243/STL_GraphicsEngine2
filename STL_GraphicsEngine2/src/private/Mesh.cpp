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

bool Mesh::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    // 정점 데이터 만들기.
    // 정점(Vertex) 배열.
    // 왼손 좌표계.
    Vertex vertices[] =
    {
        Vertex(0.0f, 0.5f, 0.5f),
        Vertex(0.5f, -0.5f, 0.5f),
        Vertex(-0.5f, -0.5f, 0.5f)
    };

    // 정점의 개수.
    vertexCount = ARRAYSIZE(vertices);

    // 정점 버퍼 만들기.
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
    vertexBufferDesc.ByteWidth = sizeof(vertices); // 얼마만큼 읽을까.
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 정점 데이터 버퍼로 쓸 것이다.
    vertexBufferDesc.CPUAccessFlags = 0; // 성능을 올리기 위해 CPU가 GPU 접근할 수 있게 할까? 우리가 구분 잘해서 코딩할 수 있으면 접근하게 만들어도 됨. 0은 못 접근하게.
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // 데이터 담기.
    D3D11_SUBRESOURCE_DATA vertexBufferData;
    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = vertices;

    // 정점 버퍼 생성.
    HRESULT result = device->CreateBuffer(
        &vertexBufferDesc,
        &vertexBufferData,
        vertexBuffer.GetAddressOf()
    );
    if (FAILED(result)) 
    { 
        MessageBox(nullptr, L"정점 버퍼 생성 실패", L"오류", 0); 
        return false;
    }

    // 정점에 대한 명세 만들기 (입력 레이아웃).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    // 입력 레이아웃 설정.
    result = device->CreateInputLayout(
        layout,
        ARRAYSIZE(layout),
        vertexShaderBuffer->GetBufferPointer(),
        vertexShaderBuffer->GetBufferSize(),
        inputLayout.GetAddressOf()
    );
    if (FAILED(result)) 
    { 
        MessageBox(nullptr, L"입력 레이아웃 생성 실패", L"오류", 0); 
        return false;
    }
    
    // 상수 버퍼.
    if (transform.Create(device) == false)
    {
        return false;
    }
        
	return true;
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
    deviceContext->IASetInputLayout(inputLayout.Get());
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 선을 그릴 때는 LineList.

    transform.Bind(deviceContext);
}

void Mesh::DrawBuffers(ID3D11DeviceContext* deviceContext)
{
    // Draw
    deviceContext->Draw(vertexCount, 0); // 이게 DrawCall이다.
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
