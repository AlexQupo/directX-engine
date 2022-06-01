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
	WNDCLASSEX wc;
	void RegisterWindowClass();
public:

	bool Initialize(WindowContainer* pWindowContainer, LPCWSTR appName, int width, int height);
	bool ProcessMessages();
	HWND GetHWND() const;
	~Display();
};