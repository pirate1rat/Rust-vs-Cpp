#pragma once
#include "Entity.h"
#include "Constants.h"
#include "Projectile.h"

class Player : public Entity
{
private:
	Vector2 directionUnitVec;
	const float rotationUnit = 2.0f;
	const float maxMovementVecLength = 300.0f;
	const float acceleration = 300.0f;
	float accelerationDirection = FORWARD;
public:

private:
public:
	Player(Vector2 center, Sprite spriteEnum);
	void rotate(float rotationDirection, float deltaTime);
	void changeVelocity(float accelerationDirection, float deltaTime);
	std::unique_ptr<Projectile> createProjectile();
};

