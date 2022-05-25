#pragma once
#include "Display.h"
#include "Keyboard/KeyboardClass.h"
#include "Mouse/MouseClass.h"

class WindowContainer {
protected:
	Display display;
	KeyboardClass keyboard;
	MouseClass mouse;
public:
	WindowContainer();
	LRESULT WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

	/*bool Initialize(LPCWSTR appName, int Height, int Width);
	bool ProcessMessages();


	LRESULT WindowProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
	void Update();*/
};