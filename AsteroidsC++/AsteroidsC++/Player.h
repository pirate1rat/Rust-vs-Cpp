#pragma once
#include "Entity.h"
#include "Constants.h"

class Player : public Entity
{
private:
	Vector2 accelerationVec = Vector2{ 0.0f, -15.0f };
	const float rotationUnit = 2.0f;
	const float maxMovementVecLength = 60.0f;
	float accelerationDirection = FORWARD;
public:

private:
public:
	Player(Vector2 center, Sprite spriteEnum);
	void rotate(float rotationDirection, float deltaTime);
	void changeVelocity(float accelerationDirection, float deltaTime);
};

