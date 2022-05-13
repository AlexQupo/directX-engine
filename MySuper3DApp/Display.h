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
	HWND hWnd = nullptr;
	//WNDPROC WndProc;
	WNDCLASSEX wc;
	void RegisterWindowClass();
	//LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
public:

	bool Initialize(LPCWSTR appName, int Height, int Width);
	bool ProcessMessages();
	~Display();
};