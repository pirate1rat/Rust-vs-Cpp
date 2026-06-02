#pragma once
#include "Entity.h"
#include "Constants.h"

class Asteroid : public Entity
{
private:
	AsteroidSize asteroidSize;

public:
	Asteroid(Sprite spriteEnum);
	std::unique_ptr<Asteroid> split();
	Vector2 getPosition();
};