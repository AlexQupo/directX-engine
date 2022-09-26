#pragma once
#include "WindowContainer.h"
#include "Timer.h"
//After
#include "GameObject.h"


class Engine : WindowContainer
{
public:
	bool Initialize(LPCWSTR appName, int width, int height);
	bool InitializeScene(Vertex v[], int numOfVertices, DWORD indices[], int numOfIndices);
	bool ProcessMessages();

	void Update();
	void RenderFrame();

	//After
	std::vector<GameObject*> Components;

private:
	Timer timer;
};