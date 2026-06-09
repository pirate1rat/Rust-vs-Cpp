#pragma once
#include <memory>
#include "raylib.h"
#include "Constants.h"
#include "Sprites.h"
#include "Renderer.h"
#include "CollisionChecker.h"

class Entity
{
protected:
	const SpriteStruct* prefab;
	Vector2 directionUnitVec;
	Vector2 velocityVec;
	Vector2 position; //centerOfGravity
	float rotation = 0.0f;
	const float rotationUnit = DEFAULT_ROTATION_UNIT;
	Color defaultColor = RAYWHITE;
public:
	bool alive = true;

public:
	Entity(Sprite spriteEnum);
	void reposition(Vector2 center);
	virtual void move(float deltaTime);
	void rotate(float rotationDirection, float deltaTime);
	void draw();
	// true if collides with other
	bool checkCollision(Entity& other);
	Vector2 getPosition();
};

