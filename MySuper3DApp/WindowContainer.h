#pragma once
#include "Display.h"
#include "Keyboard/KeyboardClass.h"
#include "Mouse/MouseClass.h"
#include "Graphics/Graphics.h"

class WindowContainer {
protected:
	Display display;
	KeyboardClass keyboard;
	MouseClass mouse;
	Graphics gfx;
public:
	WindowContainer();
	LRESULT WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

};