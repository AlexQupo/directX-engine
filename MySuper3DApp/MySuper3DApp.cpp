#include "Engine.h"

int main()
{
	LPCWSTR applicationName = L"My3DApp";
	int screenWidth = 800;
	int screenHeight = 800;

	Vertex v[] =
	{
		Vertex(-0.5f,  -0.5f, 0.0f, 1.0f, 0.4f, 0.0f),	//Bottom Left		[0] 
		Vertex(0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f),		//Top Left			[1]
		Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f),	//Bottom Right		[2]
	};
	DWORD indices[] =
	{
		0, 1, 2,
	};

	Engine engine;
	if (engine.Initialize(applicationName, screenWidth, screenHeight)) {
		engine.InitializeScene(v, ARRAYSIZE(v), indices, ARRAYSIZE(indices));
		while (engine.ProcessMessages() == true) {
			engine.Update();
			engine.RenderFrame();
		}
	}

}
