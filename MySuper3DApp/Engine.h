#pragma once
#include "WindowContainer.h"
#include "Timer.h"


class Engine : WindowContainer
{
public:
	bool Initialize(LPCWSTR appName, int width, int height);
	bool ProcessMessages();

	void Update();
	void RenderFrame();

	bool AddComponent();

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetDeviceContext() const;


private:
	Timer timer;
};