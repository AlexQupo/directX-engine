#pragma once
#include <Windows.h>
#include <WinUser.h>


class DisplayWin32
{
private:

public:
	LPCWSTR applicationName;
	int clientHeight;
	int clientWidth;
	HINSTANCE hInstance;
	HWND &hWnd;
	//Module;
	WNDPROC WndProc;
	WNDCLASSEX wc;

	bool Initialize(LPCWSTR appName, int Height, int Width, HINSTANCE hInst, WNDPROC MessageHandler, HWND &handlerWindow);
	~DisplayWin32();
};