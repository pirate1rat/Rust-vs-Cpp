#include "Player.h"
#include "raymath.h"

Player::Player(Vector2 windowCenter) {
	for (int i = 0; i < 4; i++) {
		points[i] = Vector2Add(points[i], windowCenter);
	}
	centerOfGravity = Vector2Add(centerOfGravity, windowCenter);
}

void Player::Draw() {
	DrawLineV(points[0], points[1], RAYWHITE);
	DrawLineV(points[1], points[2], RAYWHITE);
	DrawLineV(points[2], points[3], RAYWHITE);
	DrawLineV(points[3], points[0], RAYWHITE);
}

void Player::Move() {
	for (int i = 0; i < 4; i++) {
		points[i] = Vector2Add(points[i], movementVec);
	}
	centerOfGravity = Vector2Add(centerOfGravity, movementVec);
}

void Player::Rotate(int rotationDirection) {
	double currentRotation = rotation * rotationDirection;
	movementVec = Vector2Rotate(movementVec, currentRotation);
	
	for (int i = 0; i < 4; i++) {
		Vector2 supportVec = Vector2{ points[i].x - centerOfGravity.x,
									  points[i].y - centerOfGravity.y };
		supportVec = Vector2Rotate(supportVec, currentRotation);
		points[i] = Vector2{ centerOfGravity.x + supportVec.x,
							 centerOfGravity.y + supportVec.y };
	}
}
