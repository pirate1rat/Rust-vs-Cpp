#include "Player.h"
#include "Constants.h"
#include "raymath.h"

Player::Player(Vector2 windowCenter, Sprite spriteEnum) : Entity(spriteEnum){
	movementVec = Vector2{ 0.0f, 0.0f };
	position = Vector2{ 0.0f, 2.5f }; //center of gravity
	reposition(windowCenter);
}

void Player::rotate(float rotationDirection, float deltaTime) {
	float r = rotationUnit * rotationDirection * deltaTime;
	rotation += r;
	movementVec = Vector2Rotate(movementVec, r);
	accelerationVec = Vector2Rotate(accelerationVec, r);
}

void Player::changeVelocity(float accelerationDirection, float deltaTime) {
	if (accelerationDirection == BACKWARD && movementVec == Vector2{ 0.0f, 0.0f })
		return;

	if (this->accelerationDirection != accelerationDirection) {
		this->accelerationDirection = accelerationDirection;
		accelerationVec = Vector2Negate(accelerationVec);
	}

	Vector2 newMovementVec = Vector2Scale(Vector2Add(movementVec, accelerationVec), deltaTime);
	if (Vector2DotProduct(newMovementVec, movementVec) < 0) {
		movementVec = { 0.0f, 0.0f };
	}
	else if (Vector2Length(newMovementVec) <= maxMovementVecLength) {
		movementVec = newMovementVec;
	}
}
