#pragma once
#include "WindowContainer.h"

class Engine : WindowContainer
{
public:
	bool Initialize(LPCWSTR appName, int width, int height);
	bool ProcessMessages();

	void Update();
	void RenderFrame();
};