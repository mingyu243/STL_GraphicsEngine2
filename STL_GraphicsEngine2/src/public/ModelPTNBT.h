#pragma once
#include "Mesh.h"
#include <string>

class ModelPTNBT : public Mesh
{
public:
	ModelPTNBT();
	~ModelPTNBT();

	// 정점 버퍼 초기화 함수 오버라이딩.
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) override;
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName);
};