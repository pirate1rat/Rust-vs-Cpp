#pragma once
#include "raylib.h"
#include "Hitboxes.h"

enum AsteroidSize
{
	NONE,
	SMALL,
	MEDIUM,
	BIG
};

struct SpriteStruct {
	const Vector2* gPoints;
	const int gLength;
	const Vector2* hPoints;
	const int hLength;
	AsteroidSize asteroidSize; //used only by asteroids
};

enum Sprite
{
	PLAYER = 0,
	SMALL1,
	SMALL2,
	MEDIUM1,
	MEDIUM2,
	MEDIUM3,
	BIG1,
	BIG2,
	BIG3,
	PROJECTILE, //ends asteroid sprites
};

extern const SpriteStruct static_sprites[];