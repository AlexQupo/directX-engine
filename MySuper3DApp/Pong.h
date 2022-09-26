#pragma once
#include "Engine.h"
#include "Paddle.h"
#include "Ball.h"

class Pong : public Engine {
public:
	Pong(LPCWSTR WinName) : Engine(WinName) {}

	virtual void Initialize() override;
	virtual void Update(float delta_time) override;

	virtual void ShowScore();
	virtual void BallBounce(float ballY, float paddleY);

	int scoreLeft;
	int scoreRight;
};