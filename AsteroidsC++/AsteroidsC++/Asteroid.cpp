#include "Asteroid.h"

Asteroid::Asteroid() : Entity() {
	graphPts = {
		Vector2{18.5f, 0.0f},
		Vector2{8.0f, 15.5f},
		Vector2{-9.5f, 14.0f},
		Vector2{-19.0f, 3.0f},
		Vector2{-12.0f, -11.0f},
		Vector2{0.0f, -17.5f},
		Vector2{11.5f, -12.0f}
	};
	hitboxPts = {
		Vector2 {-20.0f, -20.0f},
		Vector2 {-20.0f, 20.0f},
		Vector2 {20.0f, 20.0f},
		Vector2 {20.0f, -20.0f},
	};
	movementVec = Vector2{ randFloat(-0.1f, 0.1f), randFloat(-0.1f, 0.1f)};
	centerOfGravity = Vector2{ 0.0f, 2.5f };
	Vector2 spawnPoint = Vector2{ (float)(rand() % WINDOW_WIDTH), (float)(rand() % WINDOW_HIGHT) };
	reposition(spawnPoint);
}

float Asteroid::randFloat(float min, float max) {
	return min + (float)(rand()) / RAND_MAX * (max - min);
}
