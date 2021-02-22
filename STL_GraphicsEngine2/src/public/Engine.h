#pragma once
#include "DXApp.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Mesh.h"

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

	Mesh mesh;
};

