#pragma once
#include "raylib.h"
#include "Constants.h"
#include <vector>
#include "Sprites.h"

class Entity
{
protected:
	const SpriteStruct* prefab;
	Vector2 movementVec;
	Vector2 position; //centerOfGravity
	double rotation = 0.0f;
	Color defaultColor = RAYWHITE;
public:

private:
	float cross(Vector2 a, Vector2 b, Vector2 c);
	bool onSegment(Vector2 a, Vector2 b, Vector2 p);
public:
	Entity(Sprite spriteEnum);
	void reposition(Vector2 center);
	void draw();
	void move();
	bool checkCollision(Entity* other); // true if collides with other
};

