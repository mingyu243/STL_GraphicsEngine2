#include "Engine.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pCmdLine,
	int nCmdShow)
{
	// ��ü.
	Engine engine = Engine(hInstance, 1280, 800, L"�׷��Ƚ� ����");

	// �ʱ�ȭ.
	if (engine.Initialize() == false)
	{
		MessageBox(nullptr, L"���� �ʱ�ȭ ����", L"����", 0);
		exit(-1);
	}
	
	//  ����.
	return engine.Run();
}