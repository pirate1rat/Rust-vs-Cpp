#pragma once
#include "raylib.h"
#include "Constants.h"

class Player
{
private:
	Vector2 points[4] = { Vector2{0.0f, -16.0f},
						  Vector2{-8.0f, 14.0f},
						  Vector2{0.0f, 9.5f},
						  Vector2{8.0f, 14.0f} };
	Vector2 movementVec = Vector2{ 0.0f, 0.0f };
	Vector2 accelerationVec = Vector2{ 0.0f, -0.00005f };
	const double rotation = 0.001f;
	const float maxMovementVecLength = 0.12f;
	const float minMovementVecLength = 0.0001f;
	float accelerationDirection = FORWARD;

	Vector2 centerOfGravity = Vector2{ 0.0f, 2.5f };
	Color playerColor = Color{255, 255, 255, 255};	

private:
public:
	Player(Vector2 center);
	void reposition(Vector2 center);
	void draw();
	void move();
	void rotate(float rotationDirection);
	void changeVelocity(float accelerationDirection);
};

