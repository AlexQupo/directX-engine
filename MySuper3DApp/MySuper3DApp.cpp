#include "Engine.h"

int main()
{
	LPCWSTR applicationName = L"My3DApp";
	int screenWidth = 800;
	int screenHeight = 800;

	Engine engine;

	CameraController cameraContr;
	Platform plform_Player;
	Platform plform_Player2;
	Ball ball;
	engine.AddComponent();
	engine.AddComponent();
	engine.AddComponent();


	if (engine.Initialize(applicationName, screenWidth, screenHeight)) {
		while (engine.ProcessMessages() == true) {
			engine.Update();
			engine.RenderFrame();
		}
	}

}
