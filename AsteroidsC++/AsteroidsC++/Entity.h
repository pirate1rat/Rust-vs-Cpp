#pragma once
#include "raylib.h"
#include "Constants.h"
#include <vector>
#include "Sprites.h"

class Entity
{
protected:
	std::vector<Vector2> graphPts;
	std::vector<Vector2> hitboxPts;
	Vector2 movementVec;
	Vector2 centerOfGravity;
	Color defaultColor = RAYWHITE;
public:

private:
public:
	Entity();
	void reposition(Vector2 center);
	void draw();
	void move();
};

