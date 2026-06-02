#include "Player.h"
#include "Constants.h"
#include "raymath.h"

Player::Player(Vector2 windowCenter, Sprite spriteEnum) : Entity(spriteEnum){
	velocityVec = Vector2{ 0.0f, 0.0f };
	directionUnitVec = Vector2{ 0.0f, -1.0f };
	position = Vector2{ 0.0f, 2.5f }; //center of gravity
	reposition(windowCenter);
}

void Player::rotate(float rotationDirection, float deltaTime) {
	float r = rotationUnit * rotationDirection * deltaTime;
	rotation += r;
	directionUnitVec = Vector2Rotate(directionUnitVec, r);
	velocityVec = Vector2Rotate(velocityVec, r);
}

void Player::changeVelocity(float accelerationDirection, float deltaTime) {
	if (accelerationDirection == BACKWARD && velocityVec == Vector2Zero())
		return;

	if (this->accelerationDirection != accelerationDirection) {
		this->accelerationDirection = accelerationDirection;
	}
	float currentAcceleration = acceleration * this->accelerationDirection;

	Vector2 forwardUnitVec = Vector2Scale(directionUnitVec, currentAcceleration);
	Vector2 newVelocityVec = Vector2Add(velocityVec, Vector2Scale(forwardUnitVec, deltaTime));
	if (Vector2DotProduct(newVelocityVec, velocityVec) < 0) {
		velocityVec = Vector2Zero();
	}
	else if (Vector2Length(newVelocityVec) <= maxMovementVecLength) {
		velocityVec = newVelocityVec;
	}
}

std::unique_ptr<Projectile> Player::createProjectile() {
	Vector2 start = position + Vector2Scale(directionUnitVec, 10.0f);
	Vector2 speed = Vector2Scale(directionUnitVec, 500.0f);
	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(start, speed, Sprite::PROJECTILE);
	return projectile;
}
