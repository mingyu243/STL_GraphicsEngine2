#include "InputProcessor.h"

Keyboard InputProcessor::keyboard;
Mouse InputProcessor::mouse;

void InputProcessor::InitializeInput(HWND hwnd)
{
    mouse.SetWindow(hwnd);
    mouse.SetMode(Mouse::Mode::MODE_ABSOLUTE);
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
