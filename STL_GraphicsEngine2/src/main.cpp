#include "Window.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pCmdLine,
	int nCmdShow)
{
	// ������ ����.
	if (Window::InitializeWindow(hInstance, 1280, 800, L"�׷��Ƚ� ����") == false)
	{
		MessageBox(nullptr, L"������ �ʱ�ȭ ����", L"����", 0);
		exit(-1);
	}

	// �޽��� ó�� ����.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}