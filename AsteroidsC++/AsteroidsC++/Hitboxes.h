#pragma once
#include "raylib.h"

inline const Vector2 hitboxPlayer[] = {
	Vector2{0.0f, -16.0f},
	Vector2{-8.0f, 14.0f},
	Vector2{8.0f, 14.0f}
};

inline const Vector2 hitboxSmallAsteroid[] = {
	Vector2{ -10.0f, -10.0f },
	Vector2{ -10.0f, 10.0f },
	Vector2{ 10.0f, 10.0f },
	Vector2{ 10.0f, -10.0f }
};

inline const Vector2 hitboxMediumAsteroid[] = {
	Vector2{ -20.0f, -20.0f },
	Vector2{ -20.0f, 20.0f },
	Vector2{ 20.0f, 20.0f },
	Vector2{ 20.0f, -20.0f }
};

inline const Vector2 hitboxBigAsteroid[] = {
	Vector2{ -40.0f, -40.0f },
	Vector2{ -40.0f, 40.0f },
	Vector2{ 40.0f, 40.0f },
	Vector2{ 40.0f, -40.0f }
};

inline const Vector2 hitboxProjectile[] = {
	Vector2{0.0f, -2.5f},
	Vector2{-2.5f, 0.0f},
	Vector2{0.0f, 2.5f},
	Vector2{2.5f, 0.0f},
};