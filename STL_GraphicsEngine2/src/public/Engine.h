#pragma once
#include "DXApp.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "DiffuseShader.h"
#include "SpecularShader.h"

#include "Mesh.h"
#include "Triangle.h"
#include "Quad.h"
#include "QuadUV.h"
#include "ModelUV.h"
#include "ModelPTN.h"

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
	
	DiffuseShader diffuseShader;
	SpecularShader specularShader;

	ModelPTN modelPTN;
	ModelPTN modelPTN2;

	Camera camera;

	// ����Ʈ ����
	LightBuffer lightBuffer;
};