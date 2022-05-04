#pragma once
#include <Windows.h>
#include <WinUser.h>


class DisplayWin32 {
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

	DisplayWin32(LPCWSTR appName, int Height, int Width, HINSTANCE hInst, WNDPROC MessageHandler, HWND &handlerWindow);
	//: applicationName(appName), clientHeight(Height), clientWidth(Width), hInstance(hInst), hWnd(hWND), WndProc(MessageHandler), wc(WC) {


	//	hInstance = GetModuleHandle(nullptr);

	//	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	//	wc.lpfnWndProc = WndProc;
	//	wc.cbClsExtra = 0;
	//	wc.cbWndExtra = 0;
	//	wc.hInstance = hInstance;
	//	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	//	wc.hIconSm = wc.hIcon;
	//	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	//	wc.lpszMenuName = nullptr;
	//	wc.lpszClassName = applicationName;
	//	wc.cbSize = sizeof(WNDCLASSEX);
	//	
	//	// Register the window class.
	//	RegisterClassEx(&wc);
	//	
	//	RECT windowRect = { 0,0,static_cast<LONG>(clientWidth), static_cast<LONG>(clientHeight) };
	//	AdjustWindowRect(&windowRect, WS_EX_OVERLAPPEDWINDOW, FALSE);
	//	
	//	auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;
	//	
	//	auto posX = (GetSystemMetrics(SM_CXSCREEN) - clientWidth) / 2;
	//	auto posY = (GetSystemMetrics(SM_CYSCREEN) - clientHeight) / 2;
	//	
	//	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
	//		dwStyle,
	//		posX, posY,
	//		windowRect.right - windowRect.left,
	//		windowRect.bottom - windowRect.top,
	//		nullptr, nullptr, hInstance, nullptr);
	//	
	//	ShowWindow(hWnd, SW_SHOW);
	//	SetForegroundWindow(hWnd);
	//	SetFocus(hWnd);
	//	
	//	ShowCursor(true);

	//}

};




//LPCWSTR applicationName = L"My3DApp";
//HINSTANCE hInstance = GetModuleHandle(nullptr);
//
//#pragma region Window init
//WNDCLASSEX wc;
//
//wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//wc.lpfnWndProc = WndProc;
//wc.cbClsExtra = 0;
//wc.cbWndExtra = 0;
//wc.hInstance = hInstance;
//wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
//wc.hIconSm = wc.hIcon;
//wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
//wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
//wc.lpszMenuName = nullptr;
//wc.lpszClassName = applicationName;
//wc.cbSize = sizeof(WNDCLASSEX);
//
//// Register the window class.
//RegisterClassEx(&wc);
//
//auto screenWidth = 800;
//auto screenHeight = 800;
//
//RECT windowRect = { 0,0,static_cast<LONG>(screenWidth), static_cast<LONG>(screenHeight) };
//AdjustWindowRect(&windowRect, WS_EX_OVERLAPPEDWINDOW, FALSE);
//
//auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;
//
//auto posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
//auto posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
//
//HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
//	dwStyle,
//	posX, posY,
//	windowRect.right - windowRect.left,
//	windowRect.bottom - windowRect.top,
//	nullptr, nullptr, hInstance, nullptr);
//
//ShowWindow(hWnd, SW_SHOW);
//SetForegroundWindow(hWnd);
//SetFocus(hWnd);
//
//ShowCursor(true);