#include "Projectile.h"
#include "raymath.h"

Projectile::Projectile(Vector2 startingPosition, Vector2 velocityVec, Sprite spriteEnum) : Entity(spriteEnum) {
	this->velocityVec = velocityVec;
	reposition(startingPosition);
}

void Projectile::move(float deltaTime) {
	position = Vector2Add(position, Vector2Scale(velocityVec, deltaTime));

	if (position.x < static_cast<float>(-MARGIN)) {
		alive = false;
	}
	else if (static_cast<float>(WINDOW_WIDTH + MARGIN) < position.x) {
		alive = false;
	}
	else if (position.y < static_cast<float>(-MARGIN)) {
		alive = false;
	}
	else if (static_cast<float>(WINDOW_HEIGHT + MARGIN) < position.y) {
		alive = false;
	}
}