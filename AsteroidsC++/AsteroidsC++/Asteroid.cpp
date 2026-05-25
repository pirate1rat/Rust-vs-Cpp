#include "Asteroid.h"

Asteroid::Asteroid(Sprite spriteEnum) : Entity(spriteEnum) {
	movementVec = Vector2{ randFloat(-0.1f, 0.1f), randFloat(-0.1f, 0.1f)};
	position = Vector2{ 0.0f, 0.0f };
	Vector2 spawnPoint = Vector2{ (float)(rand() % WINDOW_WIDTH), (float)(rand() % WINDOW_HIGHT) };
	reposition(spawnPoint);
}

float Asteroid::randFloat(float min, float max) {
	return min + (float)(rand()) / RAND_MAX * (max - min);
}
