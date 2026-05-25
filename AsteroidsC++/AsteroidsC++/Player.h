#pragma once
#include "Entity.h"
#include "Constants.h"

class Player : public Entity
{
private:
	Vector2 accelerationVec = Vector2{ 0.0f, -0.00005f };
	const float rotationUnit = 0.001f;
	const float maxMovementVecLength = 0.12f;
	float accelerationDirection = FORWARD;
public:

private:
public:
	Player(Vector2 center, Sprite spriteEnum);
	void rotate(float rotationDirection);
	void changeVelocity(float accelerationDirection);
};

