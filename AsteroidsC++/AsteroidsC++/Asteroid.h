#pragma once
#include "Entity.h"
#include "Constants.h"

class Asteroid : public Entity
{
public:
	Asteroid(Sprite spriteEnum);
	Vector2 getPosition();
};