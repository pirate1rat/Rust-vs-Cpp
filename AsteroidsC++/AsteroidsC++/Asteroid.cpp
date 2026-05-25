#include "Asteroid.h"

Asteroid::Asteroid(Sprite spriteEnum) : Entity(spriteEnum) {
	movementVec = Vector2{ randFloat(-0.1f, 0.1f), randFloat(-0.1f, 0.1f) };
	position = Vector2{ 0.0f, 0.0f };
	Vector2 spawnPoint = Vector2{ static_cast<float>(rand() % WINDOW_WIDTH), static_cast<float>(rand() % WINDOW_HEIGHT) };
	reposition(spawnPoint);
}

Vector2 Asteroid::getPosition()
{
	return position;
}
