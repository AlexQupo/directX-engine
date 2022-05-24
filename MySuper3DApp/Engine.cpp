#include "Engine.h"


bool Engine::Initialize(LPCWSTR appName, int height, int width) {
	return this->display.Initialize(this, appName, height, width);
}

bool Engine::ProcessMessages() {
	return this->display.ProcessMessages();
}

void Engine::Update() {
	while (!keyboard.CharBufferIsEmpty()) {
		unsigned char ch = keyboard.ReadChar();
	}
	while (!keyboard.KeyBufferIsEmpty()) {
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}
}


