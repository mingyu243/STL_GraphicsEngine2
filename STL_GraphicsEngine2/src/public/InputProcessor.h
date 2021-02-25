#pragma once

#include <Windows.h>

#include <Keyboard.h>
#include <Mouse.h>

#include "Vector2f.h"

using DirectX::Keyboard;
using DirectX::Mouse;

class InputProcessor
{
public:
	// 장치 초기화.
	static void InitializeInput(HWND hwnd);
	static bool IsKeyDown(Keyboard::Keys key);
	static bool IsKeyUp(Keyboard::Keys key);

	// 리셋.
	static void ResetKeyboardState() { keyboard.Reset(); }

	// 마우스 입력.
	static Vector2f MouseDragState();
	static Mouse::State MouseState();

private:
	// 키보드, 마우스.
	static Keyboard keyboard;
	static Mouse mouse;
};

