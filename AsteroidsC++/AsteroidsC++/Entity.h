#pragma once
#include "raylib.h"
#include "Constants.h"
#include <vector>
#include "Sprites.h"

class Entity
{
protected:
	const SpriteStruct* sprite;
	std::vector<Vector2> hitboxPts;
	Vector2 movementVec;
	Vector2 position; //centerOfGravity
	double rotation = 0.0f;
	Color defaultColor = RAYWHITE;
public:

private:
public:
	Entity(Sprite spriteEnum);
	void reposition(Vector2 center);
	void draw();
	void move();
};

