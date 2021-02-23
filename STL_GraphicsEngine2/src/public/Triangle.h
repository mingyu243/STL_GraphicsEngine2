#pragma once
#include "Mesh.h"
class Triangle : public Mesh
{
public:
	Triangle();
	~Triangle();

	// 정점 버퍼 초기화 함수 오버라이딩.
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) override;
private:

};

