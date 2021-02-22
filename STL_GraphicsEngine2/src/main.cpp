#include "Engine.h"
#include "public/Vector3f.h"

#include <iostream>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pCmdLine,
	int nCmdShow)
{
	//// 객체.
	//Engine engine = Engine(hInstance, 1280, 800, L"그래픽스 엔진");

	//// 초기화.
	//if (engine.Initialize() == false)
	//{
	//	MessageBox(nullptr, L"엔진 초기화 실패", L"오류", 0);
	//	exit(-1);
	//}
	//
	////  실행.
	//return engine.Run();

	Vector3f vector(1, 1, 1);
	Vector3f vector2(2, 2, 2);
	Vector3f vector3 = vector + vector2;

}