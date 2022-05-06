#include "Game.h"

bool Game::Initialize(LPCWSTR appName, int Height, int Width, HINSTANCE hInst, WNDPROC MessageHandler, HWND& handlerWindow)
	: applicationName(appName), clientHeight(Height), clientWidth(Width), hInstance(hInst), WndProc(MessageHandler), hWnd(handlerWindow) {
	return this->display.Initialize
}