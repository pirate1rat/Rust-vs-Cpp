#pragma once
#include <vector>
#include <memory>
#include "raylib.h"
#include "Constants.h"
#include "Sprites.h"

class Entity
{
protected:
	const SpriteStruct* prefab;
	//Vector2 directionUnitVec;
	Vector2 velocityVec;
	Vector2 position; //centerOfGravity
	float rotation = 0.0f;
	Color defaultColor = RAYWHITE;
public:
private:

protected:
	Vector2 transform(Vector2 p);
	float randFloat(float min, float max);
private:
	float cross(Vector2 a, Vector2 b, Vector2 c);
	bool onSegment(Vector2 a, Vector2 b, Vector2 p);
public:
	Entity(Sprite spriteEnum);
	void reposition(Vector2 center);
	void move(float deltaTime);
	//void rotate(float rotationDirection, float deltaTime);
	void draw();
	bool checkCollision(Entity& other); // true if collides with other
};

