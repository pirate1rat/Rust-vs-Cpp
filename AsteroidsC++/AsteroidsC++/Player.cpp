#include "Player.h"
#include "Constants.h"
#include "raymath.h"

Player::Player(Vector2 windowCenter) : Entity(){
	graphPts = { 
		Vector2{0.0f, -16.0f},
		Vector2{-8.0f, 14.0f},
		Vector2{0.0f, 9.5f},
		Vector2{8.0f, 14.0f} 
	};
	hitboxPts = {
		Vector2{0.0f, -16.0f},
		Vector2{-8.0f, 14.0f},
		Vector2{8.0f, 14.0f}
	};
	movementVec = Vector2{ 0.0f, 0.0f };
	centerOfGravity = Vector2{ 0.0f, 2.5f };
	reposition(windowCenter);
}

void Player::rotate(float rotationDirection) {
	double currentRotation = rotation * rotationDirection;
	movementVec = Vector2Rotate(movementVec, currentRotation);
	accelerationVec = Vector2Rotate(accelerationVec, currentRotation);
	
	for (int i = 0; i < graphPts.size(); i++) {
		Vector2 supportVec = Vector2{ graphPts[i].x - centerOfGravity.x,
									  graphPts[i].y - centerOfGravity.y };
		supportVec = Vector2Rotate(supportVec, currentRotation);
		graphPts[i] = Vector2{ centerOfGravity.x + supportVec.x,
							 centerOfGravity.y + supportVec.y };
	}

	for (int i = 0; i < hitboxPts.size(); i++) {
		Vector2 supportVec = Vector2{ hitboxPts[i].x - centerOfGravity.x,
									  hitboxPts[i].y - centerOfGravity.y };
		supportVec = Vector2Rotate(supportVec, currentRotation);
		hitboxPts[i] = Vector2{ centerOfGravity.x + supportVec.x,
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
