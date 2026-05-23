#include "Player.h"
#include "raymath.h"

#define EPS 0.000001f
#define FORWARD 1.0f
#define BACKWARD -1.0f
#define LEFT -1.0f
#define RIGHT 1.0f

Player::Player(Vector2 windowCenter) {
	for (int i = 0; i < 4; i++) {
		points[i] = Vector2Add(points[i], windowCenter);
	}
	centerOfGravity = Vector2Add(centerOfGravity, windowCenter);
}

void Player::draw() {
	DrawLineV(points[0], points[1], RAYWHITE);
	DrawLineV(points[1], points[2], RAYWHITE);
	DrawLineV(points[2], points[3], RAYWHITE);
	DrawLineV(points[3], points[0], RAYWHITE);
}

void Player::move() {
	for (int i = 0; i < 4; i++) {
		points[i] = Vector2Add(points[i], movementVec);
	}
	centerOfGravity = Vector2Add(centerOfGravity, movementVec);
}

void Player::rotate(float rotationDirection) {
	double currentRotation = rotation * rotationDirection;
	movementVec = Vector2Rotate(movementVec, currentRotation);
	accelerationVec = Vector2Rotate(accelerationVec, currentRotation);
	
	for (int i = 0; i < 4; i++) {
		Vector2 supportVec = Vector2{ points[i].x - centerOfGravity.x,
									  points[i].y - centerOfGravity.y };
		supportVec = Vector2Rotate(supportVec, currentRotation);
		points[i] = Vector2{ centerOfGravity.x + supportVec.x,
							 centerOfGravity.y + supportVec.y };
	}
}

void Player::changeVelocity(float accelerationDirection) {
	if (accelerationDirection == BACKWARD && movementVec == Vector2{ 0.0f, 0.0f })
		return;

	if (this->accelerationDirection != accelerationDirection) {
		this->accelerationDirection = accelerationDirection;
		accelerationVec = Vector2Negate(accelerationVec);
	}

	Vector2 newMovementVec = Vector2Add(movementVec, accelerationVec);
	if (Vector2DotProduct(newMovementVec, movementVec) < 0) {
		movementVec = { 0.0f, 0.0f };
	}
	else if (Vector2Length(newMovementVec) <= maxMovementVecLength) {
		movementVec = newMovementVec;
	}
}
