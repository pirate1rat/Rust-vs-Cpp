#include "Sprites.h"

static const Vector2 player[] = {
	Vector2{0.0f, -16.0f},
	Vector2{-8.0f, 14.0f},
	Vector2{0.0f, 9.5f},
	Vector2{8.0f, 14.0f}
};

static const Vector2 small1[] = {
	Vector2{9.0f, -1.0f},
	Vector2{4.0f, 8.5f},
	Vector2{-6.0f, 7.0f},
	Vector2{-9.5f, 1.5f},
	Vector2{-7.0f, -6.5f},
	Vector2{0.5f, -9.0f},
	Vector2{7.0f, -6.0f}
};

static const Vector2 small2[] = {
	Vector2{8.5f, 2.0f},
	Vector2{5.0f, 8.0f},
	Vector2{-3.0f, 9.0f},
	Vector2{-8.5f, 4.5f},
	Vector2{-7.5f, -4.0f},
	Vector2{-2.0f, -8.5f},
	Vector2{4.5f, -7.5f},
	Vector2{9.5f, -3.0f}
};

static const Vector2 medium1[] = {
	Vector2{18.5f, 0.0f},
	Vector2{8.0f, 15.5f},
	Vector2{-9.5f, 14.0f},
	Vector2{-19.0f, 3.0f},
	Vector2{-12.0f, -11.0f},
	Vector2{0.0f, -17.5f},
	Vector2{11.5f, -12.0f}
};

static const Vector2 medium2[] = {
	Vector2{16.0f, 4.0f},
	Vector2{10.0f, 16.5f},
	Vector2{-5.0f, 18.0f},
	Vector2{-17.5f, 9.0f},
	Vector2{-15.0f, -7.0f},
	Vector2{-4.0f, -16.0f},
	Vector2{8.0f, -14.5f},
	Vector2{19.5f, -5.0f}
};

static const Vector2 medium3[] = {
	Vector2{17.0f, 2.0f},
	Vector2{13.0f, 11.0f},
	Vector2{4.0f, 19.0f},
	Vector2{-9.0f, 15.5f},
	Vector2{-18.5f, 6.0f},
	Vector2{-16.0f, -8.0f},
	Vector2{-7.0f, -17.0f},
	Vector2{3.0f, -19.5f},
	Vector2{12.0f, -13.0f},
	Vector2{19.0f, -6.0f}
};

static const Vector2 big1[] = {
	Vector2{38.0f, 5.0f},
	Vector2{22.0f, 33.0f},
	Vector2{-15.0f, 36.0f},
	Vector2{-39.0f, 12.0f},
	Vector2{-31.0f, -22.0f},
	Vector2{-8.0f, -37.0f},
	Vector2{25.0f, -29.0f},
	Vector2{39.5f, -12.0f}
};

static const Vector2 big2[] = {
	Vector2{28.0f, 10.0f},
	Vector2{18.0f, 32.0f},
	Vector2{-5.0f, 39.0f},
	Vector2{-26.0f, 25.0f},
	Vector2{-35.0f, -5.0f},
	Vector2{-21.0f, -31.0f},
	Vector2{2.0f, -38.5f},
	Vector2{24.0f, -26.0f},
	Vector2{33.0f, -11.0f}
};

static const Vector2 big3[] = {
	Vector2{35.0f, 3.0f},
	Vector2{26.0f, 24.0f},
	Vector2{9.0f, 37.0f},
	Vector2{-18.0f, 31.0f},
	Vector2{-36.0f, 14.0f},
	Vector2{-33.0f, -17.0f},
	Vector2{-14.0f, -35.0f},
	Vector2{8.0f, -38.0f},
	Vector2{27.0f, -25.0f},
	Vector2{37.0f, -13.0f}
};

static const Vector2 projectile[] = {
	Vector2{0.0f, -2.5f},
	Vector2{-2.5f, 0.0f},
	Vector2{0.0f, 2.5f},
	Vector2{2.5f, 0.0f},
};

const SpriteStruct static_sprites[] = {
	SpriteStruct{ player, 4, hPlayer, 3, AsteroidSize::NONE },
	SpriteStruct{ small1, 7, hSmallAsteroid, 4, AsteroidSize::SMALL },
	SpriteStruct{ small2, 8, hSmallAsteroid, 4, AsteroidSize::SMALL },
	SpriteStruct{ medium1, 7, hMediumAsteroid, 4, AsteroidSize::MEDIUM },
	SpriteStruct{ medium2, 7, hMediumAsteroid, 4, AsteroidSize::MEDIUM },
	SpriteStruct{ medium3, 10, hMediumAsteroid, 4, AsteroidSize::MEDIUM },
	SpriteStruct{ big1, 8, hBigAsteroid, 4, AsteroidSize::BIG },
	SpriteStruct{ big2, 9, hBigAsteroid, 4, AsteroidSize::BIG },
	SpriteStruct{ big3, 10, hBigAsteroid, 4, AsteroidSize::BIG },
	SpriteStruct{ projectile, 4, hProjectile, 4, AsteroidSize::NONE },
};