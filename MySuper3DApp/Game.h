#pragma once
#include "DisplayWin32.h"

class Game : DisplayWin32
{
protected:
	DisplayWin32 display;
public:
	bool Initialize(LPCWSTR appName, int Height, int Width, HINSTANCE hInst, WNDPROC MessageHandler, HWND& handlerWindow);

};