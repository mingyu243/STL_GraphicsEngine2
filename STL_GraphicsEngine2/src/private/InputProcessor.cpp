#include "InputProcessor.h"

Keyboard InputProcessor::keyboard;
Mouse InputProcessor::mouse;

void InputProcessor::InitializeInput(HWND hwnd)
{
    mouse.SetWindow(hwnd);

    //mouse.SetMode(Mouse::Mode::MODE_ABSOLUTE); // 마우스의 절대 위치.
    mouse.SetMode(Mouse::Mode::MODE_RELATIVE); // 이전 프레임 마우스, 현재 프레임 마우스의 상대 위치. (그 대신 마우스 포인터 안 보임.)
}

bool InputProcessor::IsKeyDown(Keyboard::Keys key)
{
    return keyboard.GetState().IsKeyDown(key);
}

bool InputProcessor::IsKeyUp(Keyboard::Keys key)
{
    return keyboard.GetState().IsKeyUp(key);
}

Vector2f InputProcessor::MouseDragState()
{
    Mouse::State state = mouse.GetState();
    return Vector2f((float)state.x, (float)state.y);
}

Mouse::State InputProcessor::MouseState()
{
    return mouse.GetState();
}
