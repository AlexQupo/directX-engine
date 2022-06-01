#pragma once
#include "WindowContainer.h"
#include "Timer.h"


class Engine : WindowContainer
{
public:
	bool Initialize(LPCWSTR appName, int width, int height);
	bool InitializeScene(Vertex v[], int numOfVertices, DWORD indices[], int numOfIndices);
	bool ProcessMessages();

	void Update();
	void RenderFrame();
private:
	Timer timer;
};