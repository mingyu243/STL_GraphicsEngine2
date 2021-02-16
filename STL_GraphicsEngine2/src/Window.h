#pragma once

#include <Windows.h>
#include <string>

class Window
{
public:
	static bool InitializeWindow();

	static bool InitializeWindow(
		HINSTANCE hInstance,
		int width,
		int height,
		std::wstring title
	);

	static HINSTANCE Instance();
	static HWND WindowHandle();
	static int Width();
	static int Height();
	static std::wstring Title();

private:
	static HINSTANCE hInstance;
	static HWND hwnd;
	static int width;
	static int height;
	static std::wstring title;
};

