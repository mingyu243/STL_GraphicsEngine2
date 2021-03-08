#pragma once
#include "DXApp.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "DiffuseShader.h"
#include "SpecularShader.h"
#include "NormalMappingShader.h"
#include "GrassShader.h"

#include "Mesh.h"
#include "Triangle.h"
#include "Quad.h"
#include "QuadUV.h"
#include "ModelUV.h"
#include "ModelPTN.h"
#include "ModelPTNBT.h"

#include "Matrix4f.h"

#include <wrl.h>

using Microsoft::WRL::ComPtr;

#include "CameraClass.h"
#include "LightBuffer.h"

class Engine : public DXApp
{
public:
	Engine(HINSTANCE hInstance, int width, int height, std::wstring title);
	~Engine();

	bool Initialize() override; // Ÿ�̸�, �� � ���� �ʱ�ȭ
	int Run() override;

protected:
	void Update() override;
	void DrawScene() override;
	
private:
	// ��� �ʱ�ȭ.
	bool InitializeScene();
	
	DiffuseShader diffuseShader1;
	DiffuseShader diffuseShader2;
	GrassShader grassShader;
	NormalMappingShader normalMappingShader;

	ModelPTN modelPTN1;
	ModelPTN modelPTN2;
	ModelPTN modelPTN3;
	ModelPTNBT modelPTNBT;

	Camera camera;

	// ����Ʈ ����
	LightBuffer lightBuffer;
};