#include "Window.h"

HINSTANCE Window::hInstance;
HWND Window::hwnd;
int Window::width;
int Window::height;
std::wstring Window::title;

// 윈도우 메시지 처리할 때 사용할 프로시저 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// 창이 닫히면 프로그램 종료.
	switch (msg)
	{
	case WM_DESTROY:
		// 종료 메시지 발생 시킴.
		PostQuitMessage(0);
		return 0;
	}

	// 기본 윈도우 프로시저 함수 호출. (기본 메시지는 윈도우에 맡김.)
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Window::InitializeWindow()
{
	return InitializeWindow(hInstance, width, height, title);
}

// 윈도우 생성 및 초기화.
bool Window::InitializeWindow(HINSTANCE hInstance, int width, int height, std::wstring title)
{
	// 윈도우 클래스 생성.
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc)); // 모두 0으로 초기화.

	// 값 설정.
	wc.lpszClassName = TEXT("GfxEngine");		// 클래스 이름.
	wc.hInstance = hInstance;					// 인스턴스.
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);	// 아이콘.
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	// 커서.
	wc.lpfnWndProc = WindowProc;					// 메시지 처리 함수.

	// 클래스 등록.
	if (RegisterClass(&wc) == false)
	{
		// 오류 검출.
		MessageBox(nullptr, L"클래스 등록 실패", L"오류", 0);

		// 강제 종료.
		exit(-1);
	}

	// 너비 조정.
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	// 윈도우 생성.
	hwnd = CreateWindow(
		wc.lpszClassName,
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == nullptr)
	{
		MessageBox(nullptr, L"윈도우 생성 실패", L"오류", 0);
		return false;
	}

	// 윈도우 보이기.
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return true;
}

HINSTANCE Window::Instance()
{
	return hInstance;
}

HWND Window::WindowHandle()
{
	return hwnd;
}

int Window::Width()
{
	return width;
}

int Window::Height()
{
	return height;
}

std::wstring Window::Title()
{
	return title;
}
