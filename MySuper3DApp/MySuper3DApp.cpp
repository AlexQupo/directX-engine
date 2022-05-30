#include "Engine.h"

int main()
{
	LPCWSTR applicationName = L"My3DApp";
	int screenWidth = 800;
	int screenHeight = 800;

	Engine engine;
	if (engine.Initialize(applicationName, screenWidth, screenHeight)) {
		while (engine.ProcessMessages() == true) {
			engine.Update();
			engine.RenderFrame();
		}
	}

}
