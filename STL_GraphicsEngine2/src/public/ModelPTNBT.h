#pragma once
#include "Mesh.h"
#include <string>

class ModelPTNBT : public Mesh
{
public:
	ModelPTNBT();
	~ModelPTNBT();

	// ���� ���� �ʱ�ȭ �Լ� �������̵�.
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) override;
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName);
};