#pragma once
#include "Entity.h"
#include "Constants.h"
#include "Projectile.h"

class Player : public Entity
{
private:
	Vector2 startPosition;
	const float rotationUnit = PLAYER_ROTATION_UNIT;
	const float maxMovementVecLength = PLAYER_MAX_SPEED;
	const float acceleration = PLAYER_ACCELERATION;
	float accelerationDirection = FORWARD;
public:

private:
public:
	Player(Vector2 center, Sprite spriteEnum);
	void respawn();
	void changeVelocity(float accelerationDirection, float deltaTime);
	std::unique_ptr<Projectile> shootProjectile();
};

