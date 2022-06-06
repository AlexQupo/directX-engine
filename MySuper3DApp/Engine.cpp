#include "Engine.h"


bool Engine::Initialize(LPCWSTR appName, int width, int height) {
	timer.Start();
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
	float dtime = timer.GetMilisecondsElapsed();
	timer.Restart();
	while (!keyboard.CharBufferIsEmpty()) {
		unsigned char ch = keyboard.ReadChar();
	}
	while (!keyboard.KeyBufferIsEmpty()) {
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}

	while(!mouse.EventBufferIsEmpty()) {
		MouseEvent me = mouse.ReadEvent();

		if (mouse.IsRightDown())
		{
			if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
			{
				this->gfx.camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
			}
		}
	}

	const float cameraSpeed = 0.01f;

	if (keyboard.KeyIsPressed('W'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed * dtime);
	}
	if (keyboard.KeyIsPressed('S'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed * dtime);
	}
	if (keyboard.KeyIsPressed('A'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetLeftVector() * cameraSpeed * dtime);
	}
	if (keyboard.KeyIsPressed('D'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetRightVector() * cameraSpeed * dtime);
	}
	if (keyboard.KeyIsPressed(VK_SPACE))
	{
		this->gfx.camera.AdjustPosition(0.0f, cameraSpeed * dtime, 0.0f);
	}
	if (keyboard.KeyIsPressed('Z'))
	{
		this->gfx.camera.AdjustPosition(0.0f, -cameraSpeed * dtime, 0.0f);
	}

}

void Engine::RenderFrame()
{
	gfx.RenderFrame();
}



ID3D11Device* Engine::GetDevice() const {
	return gfx.GetDevice();
}
ID3D11DeviceContext* Engine::GetDeviceContext() const {
	return gfx.GetDeviceContext();
}




