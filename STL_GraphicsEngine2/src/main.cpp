#include "Engine.h"
#include "public/Vector3f.h"

#include <iostream>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pCmdLine,
	int nCmdShow)
{
	//// ��ü.
	//Engine engine = Engine(hInstance, 1280, 800, L"�׷��Ƚ� ����");

	//// �ʱ�ȭ.
	//if (engine.Initialize() == false)
	//{
	//	MessageBox(nullptr, L"���� �ʱ�ȭ ����", L"����", 0);
	//	exit(-1);
	//}
	//
	////  ����.
	//return engine.Run();

	Vector3f vector(1, 1, 1);
	Vector3f vector2(2, 2, 2);
	Vector3f vector3 = vector + vector2;

}