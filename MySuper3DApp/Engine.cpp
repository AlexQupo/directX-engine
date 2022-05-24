#include "Engine.h"


bool Engine::Initialize(LPCWSTR appName, int height, int width) {
	return this->display.Initialize(this, appName, height, width);
}

bool Engine::ProcessMessages() {
	return this->display.ProcessMessages();
}



//LRESULT Game::WindowProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
//	OutputDebugStringA("AAAAA");
//	return DefWindowProc(hwnd, umessage, wparam, lparam);
//}
//
//void Game::Update() {
//	//while(!keyboard.CharBufferIsEmpty())
//}

