#include "Asteroid.h"

Asteroid::Asteroid(int typeIdx) : Entity(ASTEROID_TYPES[typeIdx].sprite) {
	this->typeIdx = typeIdx;

	float xVelocity = randFloat(MIN_ASTEROID_VELOCITY, MAX_ASTEROID_VELOCITY);
	if (rand() % 2 == 0) xVelocity = -xVelocity;
	float yVelocity = randFloat(MIN_ASTEROID_VELOCITY, MAX_ASTEROID_VELOCITY);
	if (rand() % 2 == 0) yVelocity = -yVelocity;
	velocityVec = Vector2{ xVelocity, yVelocity };
	
	Vector2 spawnPoint;
	do {
		spawnPoint = Vector2{
			static_cast<float>(rand() % WINDOW_WIDTH),
			static_cast<float>(rand() % WINDOW_HEIGHT)
		};
	} while (
		((spawnPoint.x <= (WINDOW_WIDTH / 2 - SPAWNPOINT_SAFEZONE)) || ((WINDOW_WIDTH / 2 + SPAWNPOINT_SAFEZONE) <= spawnPoint.x))
		&& 
		((spawnPoint.y <= (WINDOW_HEIGHT / 2 - SPAWNPOINT_SAFEZONE)) || ((WINDOW_HEIGHT / 2 + SPAWNPOINT_SAFEZONE) <= spawnPoint.y))
	);
	reposition(spawnPoint);
}

std::unique_ptr<Asteroid> Asteroid::split() {
	const AsteroidType& t = ASTEROID_TYPES[typeIdx];

	if (t.splitCount == 0) {
		alive = false;
		return nullptr;
	}
	int childTypeIdx = t.splitInto[rand() % t.splitCount];
	typeIdx = t.splitInto[rand() % t.splitCount];
	this->prefab = &SPRITES[ASTEROID_TYPES[typeIdx].sprite];

	auto child = std::make_unique<Asteroid>(childTypeIdx);
	child->position = position;
	return child;
}