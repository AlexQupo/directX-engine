#pragma once
#include <Windows.h>
#include <WinUser.h>


class Display
{
private:
	LPCWSTR applicationName = L"";
	int clientHeight = 0;
	int clientWidth = 0;
	HINSTANCE hInstance = nullptr;
	HWND hWnd;
	WNDPROC WndProc;
	WNDCLASSEX wc;
public:

	bool Initialize(LPCWSTR appName, int Height, int Width, WNDPROC MessageHandler);
	bool ProcessMessages();
	~Display();
};