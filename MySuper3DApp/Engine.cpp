#include "Engine.h"


bool Engine::Initialize(LPCWSTR appName, int width, int height) {
	if(!this->display.Initialize(this, appName, width, height))
		return false;

	if(!gfx.Initialize(this->display.GetHWND(), width, height))
		return false;

	return true;
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

	while(!mouse.EventBufferIsEmpty()) {
		MouseEvent me = mouse.ReadEvent();
	}
}

void Engine::RenderFrame()
{
	gfx.RenderFrame();
}


