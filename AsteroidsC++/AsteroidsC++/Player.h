#pragma once
#include "raylib.h"

class Player
{
private:
	Vector2 points[4] = { 
		Vector2{0.0f, -16.0f},
		Vector2{-8.0f, 14.0f},
		Vector2{0.0f, 9.5f},
		Vector2{8.0f, 14.0f}
	};
	Vector2 centerOfGravity = Vector2{ 0.0f, -2.5f };

	Vector2 movementVec = Vector2{ 0.0f, -0.1f };
	const float rotation = 0.001f;
	
	const Color playerColor = Color{255, 255, 255, 255};	

private:
public:
	Player(Vector2 windowCenter);
	void Draw();
	void Move();
	void Rotate(int rotationDirection);
};

