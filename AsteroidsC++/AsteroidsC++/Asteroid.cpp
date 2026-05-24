#include "Asteroid.h"

Asteroid::Asteroid() : Entity() {
	points = {
		Vector2{0.0f, -16.0f},
		Vector2{-8.0f, 14.0f},
		Vector2{0.0f, 9.5f},
		Vector2{8.0f, 14.0f}
	};
	movementVec = Vector2{ randFloat(-0.1f, 0.1f), randFloat(-0.1f, 0.1f)};
	centerOfGravity = Vector2{ 0.0f, 2.5f };
	Vector2 spawnPoint = Vector2{ (float)(rand() % WINDOW_WIDTH), (float)(rand() % WINDOW_HIGHT) };
	reposition(spawnPoint);
}

float Asteroid::randFloat(float min, float max) {
	return min + (float)(rand()) / RAND_MAX * (max - min);
}
