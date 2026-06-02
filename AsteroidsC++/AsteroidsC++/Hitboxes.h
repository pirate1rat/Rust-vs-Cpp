#pragma once
#include "raylib.h"

//enum Hitbox
//{
//	PLAYER_HITBOX = 0,
//	SMALL_ASTEROID,
//	MEDIUM_ASTEROID,
//	BIG_ASTEROID
//};

static const Vector2 hPlayer[] = {
	Vector2{0.0f, -16.0f},
	Vector2{-8.0f, 14.0f},
	Vector2{8.0f, 14.0f}
};

static const Vector2 hSmallAsteroid[] = {
	Vector2{ -10.0f, -10.0f },
	Vector2{ -10.0f, 10.0f },
	Vector2{ 10.0f, 10.0f },
	Vector2{ 10.0f, -10.0f }
};

static const Vector2 hMediumAsteroid[] = {
	Vector2{ -20.0f, -20.0f },
	Vector2{ -20.0f, 20.0f },
	Vector2{ 20.0f, 20.0f },
	Vector2{ 20.0f, -20.0f }
};

static const Vector2 hBigAsteroid[] = {
	Vector2{ -40.0f, -40.0f },
	Vector2{ -40.0f, 40.0f },
	Vector2{ 40.0f, 40.0f },
	Vector2{ 40.0f, -40.0f }
};

static const Vector2 hProjectile[] = {
	Vector2{0.0f, -2.5f},
	Vector2{-2.5f, 0.0f},
	Vector2{0.0f, 2.5f},
	Vector2{2.5f, 0.0f},
};