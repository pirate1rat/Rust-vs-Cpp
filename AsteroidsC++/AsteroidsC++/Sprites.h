#pragma once
#include "raylib.h"
#include "Hitboxes.h"

struct SpriteStruct {
	const Vector2* graphicPoints;
	const int gLength;
	const Vector2* hitboxPoints;
	const int hLength;
};

enum Sprite
{
	PLAYER = 0,
	ASTEROID_SMALL_1,
	ASTEROID_SMALL_2,
	ASTEROID_MEDIUM_1,
	ASTEROID_MEDIUM_2,
	ASTEROID_MEDIUM_3,
	ASTEROID_BIG_1,
	ASTEROID_BIG_2,
	ASTEROID_BIG_3,
	PROJECTILE,
};

extern const SpriteStruct SPRITES[];