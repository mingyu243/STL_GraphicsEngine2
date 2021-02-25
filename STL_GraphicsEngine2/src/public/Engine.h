#pragma once
#include "DXApp.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "TextureMappingShader.h"

#include "Mesh.h"
#include "Triangle.h"
#include "Quad.h"
#include "QuadUV.h"
#include "ModelUV.h"

#include "Matrix4f.h"

#include <wrl.h>

using Microsoft::WRL::ComPtr;

class Engine : public DXApp
{
public:
	Engine(HINSTANCE hInstance, int width, int height, std::wstring title);
	~Engine();

	bool Initialize() override; // 타이머, 씬 등에 대한 초기화
	int Run() override;

protected:
	void Update() override;
	void DrawScene() override;
	
private:
	// 장면 초기화.
	bool InitializeScene();
	
	TextureMappingShader textureShader;

	Quad quad;
	Triangle triangle;
	QuadUV quadUV;

	ModelUV modelUV;
};