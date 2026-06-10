#include "Player.h"
#include "Constants.h"
#include "raymath.h"

Player::Player(Vector2 windowCenter, Sprite spriteEnum) : Entity(spriteEnum){
	position = Vector2{ 0.0f, 2.5f }; //center of gravity
	reposition(windowCenter);
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

std::unique_ptr<Projectile> Player::shootProjectile() {
	Vector2 start = position + Vector2Scale(directionUnitVec, PROJECTILE_START_OFFSET);
	Vector2 speed = Vector2Scale(directionUnitVec, PROJECTILE_SPEED);
	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(start, speed, Sprite::PROJECTILE);
	return projectile;
}
