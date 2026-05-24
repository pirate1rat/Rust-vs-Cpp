#pragma once
#include "raylib.h"
#include "Constants.h"
#include <vector>

class Entity
{
protected:
	std::vector<Vector2> points;
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

