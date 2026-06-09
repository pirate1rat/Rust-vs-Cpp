#include "Entity.h"

Entity::Entity(Sprite spriteEnum) {
	this->prefab = &SPRITES[spriteEnum];
	this->directionUnitVec = Vector2{ 0.0f, -1.0f };
}

void Entity::draw() {
	drawSprite(*prefab, this->position, this->rotation, this->defaultColor);
}

void Entity::reposition(Vector2 repositionVec) {
	this->position = Vector2Add(this->position, repositionVec);
}

void Entity::rotate(float rotationDirection, float deltaTime) {
	float r = rotationUnit * rotationDirection * deltaTime;
	rotation += r;
	directionUnitVec = Vector2Rotate(directionUnitVec, r);
}

void Entity::move(float deltaTime) {
	position = Vector2Add(position, Vector2Scale(velocityVec, deltaTime));

	if (position.x < static_cast<float>(-MARGIN)) {
		reposition(Vector2{ static_cast<float>(WINDOW_WIDTH + 2 * MARGIN), 0.0f });
	}
	else if (static_cast<float>(WINDOW_WIDTH + MARGIN) < position.x) {
		reposition(Vector2{ static_cast<float>(-WINDOW_WIDTH - 2 * MARGIN), 0.0f });
	}

	if (position.y < static_cast<float>(-MARGIN)) {
		reposition(Vector2{ 0.0f, static_cast<float>(WINDOW_HEIGHT + 2 * MARGIN) });
	}
	else if (static_cast<float>(WINDOW_HEIGHT + MARGIN) < position.y) {
		reposition(Vector2{ 0.0f, static_cast<float>(-WINDOW_HEIGHT - 2 * MARGIN) });
	}
}

bool Entity::checkCollision(Entity& other) {
	return ::checkCollision(*prefab, position, rotation, *(other.prefab), other.position, other.rotation);
}

Vector2 Entity::getPosition(){
	return position;
}


