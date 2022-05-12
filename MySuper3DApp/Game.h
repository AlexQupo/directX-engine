#pragma once
#include "Display.h"

class Game : Display
{
protected:
	Display display;
public:
	bool Initialize(LPCWSTR appName, int Height, int Width, HINSTANCE hInst, WNDPROC MessageHandler, HWND& handlerWindow);

};