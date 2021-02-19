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

	bool Initialize() override; // Ÿ�̸�, �� � ���� �ʱ�ȭ
	int Run() override;

protected:
	void Update() override;
	void DrawScene() override;
	
private:
	// ��� �ʱ�ȭ.
	bool InitializeScene();

	VertexShader vertexShader;
	PixelShader pixelShader;
	Mesh mesh;

};
