#pragma once
#include "Shapes.h"

class Ball : Shapes {
private:
	float speed;
	float width;
	float height;
	DirectX::XMFLOAT3 color;
	DirectX::XMFLOAT3 position;
public:
	Ball(Engine engine,float width, float height);
	void SetSpeed(float speed);
	void SetColor(float red, float green, float blue);
	void SetPosition(float x, float y, float z);

	void ResetPosition();

};