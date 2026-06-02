#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(Vector2 startingPosition, Vector2 velocityVec, Sprite spriteEnum);
	void move(float deltaTime) override;
};

