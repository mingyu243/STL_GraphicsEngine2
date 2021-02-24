#pragma once
#include "Mesh.h"

class QuadUV : public Mesh
{
public:
	QuadUV();
	~QuadUV();

	// 정점 버퍼 초기화 함수 오버라이딩.
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) override;
private:
	void BindBuffers(ID3D11DeviceContext* deviceContext) override;

};

