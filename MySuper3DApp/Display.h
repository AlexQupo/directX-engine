#pragma once
#include <Windows.h>
#include <WinUser.h>

#include "ErrorLogger.h"

class WindowContainer;

class Display
{
private:
	LPCWSTR applicationName = L"";
	int clientHeight = 0;
	int clientWidth = 0;
	HINSTANCE hInstance = nullptr;
	HWND hWnd = nullptr;
	//WNDPROC WndProc;
	WNDCLASSEX wc;
	void RegisterWindowClass();
	//LRESULT WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
public:

	bool Initialize(WindowContainer* pWindowContainer, LPCWSTR appName, int height, int width);
	bool ProcessMessages();
	~Display();
};