#include "Asteroid.h"

Asteroid::Asteroid(Sprite spriteEnum) : Entity(spriteEnum) {
	velocityVec = Vector2{ randFloat(-40.0f, 40.0f), randFloat(-40.0f, 40.0f) };
	position = Vector2{ 0.0f, 0.0f };
	Vector2 spawnPoint = Vector2{ static_cast<float>(rand() % WINDOW_WIDTH), static_cast<float>(rand() % WINDOW_HEIGHT) };
	reposition(spawnPoint);
}

Vector2 Asteroid::getPosition()
{
	return position;
}
