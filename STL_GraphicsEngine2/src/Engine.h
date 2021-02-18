#pragma once
#include "DXApp.h"
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

	// 변수.
	// 쉐이더도 코드이다. (프로그램.)
	// 쉐이더 생성하는 과정.
	// 1. 컴파일.
	// 2. 생성. (컴파일 완료된 이진 파일 필요 .cso)
	ID3D11VertexShader* vertexShader;	// 컴파일 된 이진코드로 생성한 쉐이더.
	ID3D11PixelShader* pixelShader;		// 컴파일 된 이진코드로 생성한 쉐이더.
	ID3DBlob* vertexShaderBuffer;		// .hlsl 쉐이더 코드 파일로 컴파일 된 이진코드.
	ID3DBlob* pixelShaderBuffer;		// .hlsl 쉐이더 코드 파일로 컴파일 된 이진코드.

	// IA - Input Assembler. (렌더링 파이프라인 중에 젤 첫 단계.)
	ID3D11Buffer* vertexBuffer; // 정점 버퍼. (Vertex 전달 용도.)
	ID3D11InputLayout* inputLayout; // 입력 레이아웃. Vertex에 어떤 정보들(x,y,z,u,v,nx,ny,nz 등)이 담길 지.

	// 점 개수.
	int vertexCount = 0; // 전달할 때 알려줘야 하기 때문에 갖고 있자.
};

