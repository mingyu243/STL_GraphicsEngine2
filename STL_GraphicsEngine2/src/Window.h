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
	static void SetInstance(HINSTANCE hInstance);

	static HWND WindowHandle();

	static int Width();
	static void SetWidth(int width);

	static int Height();
	static void SetHeight(int height);

	static std::wstring Title();
	static void SetTitle(std::wstring title);

private:
	static HINSTANCE hInstance;
	static HWND hwnd;
	static int width;
	static int height;
	static std::wstring title;
};

