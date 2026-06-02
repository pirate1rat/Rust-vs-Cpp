#include "Asteroid.h"

Asteroid::Asteroid(Sprite spriteEnum) : Entity(spriteEnum) {
	asteroidSize = prefab->asteroidSize;
	velocityVec = Vector2{ randFloat(-80.0f, 80.0f), randFloat(-80.0f, 80.0f) };
	position = Vector2{ 0.0f, 0.0f };
	Vector2 spawnPoint = Vector2{ static_cast<float>(rand() % WINDOW_WIDTH), static_cast<float>(rand() % WINDOW_HEIGHT) };
	reposition(spawnPoint);
}

std::unique_ptr<Asteroid> Asteroid::split() {
	switch (asteroidSize) {
		case AsteroidSize::BIG:
		{
			Sprite randomMediumSprite = static_cast<Sprite>((rand() % 3 + 3));
			auto newAsteroid = std::make_unique<Asteroid>(randomMediumSprite);
			newAsteroid->position = this->position;
			this->prefab = &static_sprites[randomMediumSprite];
			this->asteroidSize = this->prefab->asteroidSize;
			return newAsteroid;
		}
		case AsteroidSize::MEDIUM:
		{
			Sprite randomSmallSprite = static_cast<Sprite>((rand() % 2 + 1));
			auto newAsteroid = std::make_unique<Asteroid>(randomSmallSprite);
			newAsteroid->position = this->position;
			this->prefab = &static_sprites[randomSmallSprite];
			this->asteroidSize = this->prefab->asteroidSize;
			return newAsteroid;
		}
		case AsteroidSize::SMALL:
		{
			alive = false;
			return nullptr;
		}

		return nullptr;
	}
}

Vector2 Asteroid::getPosition() {
	return this->position;
}
