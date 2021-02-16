#include "Window.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pCmdLine,
	int nCmdShow)
{
	// 윈도우 생성.
	if (Window::InitializeWindow(hInstance, 1280, 800, L"그래픽스 엔진") == false)
	{
		MessageBox(nullptr, L"윈도우 초기화 실패", L"오류", 0);
		exit(-1);
	}

	// 메시지 처리 루프.
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