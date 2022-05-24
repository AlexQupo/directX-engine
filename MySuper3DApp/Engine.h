#pragma once
#include "WindowContainer.h"

class Engine : WindowContainer
{
public:
	bool Initialize(LPCWSTR appName, int height, int width);
	bool ProcessMessages();
};