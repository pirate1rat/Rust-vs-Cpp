#pragma once
#include "Entity.h"
#include "Constants.h"
#include "Sprites.h"

enum AsteroidSize
{
	NONE,
	SMALL,
	MEDIUM,
	BIG
};

struct AsteroidType {
	Sprite sprite;
	AsteroidSize size;
	const int* splitInto;
	const int splitCount;
};

inline const int bigSplitInto[] = { 3, 4, 5 }; // indexes for medium
inline const int mediumSplitInto[] = { 6, 7 }; // indexes for small

inline const AsteroidType ASTEROID_TYPES[] = {
	{ Sprite::ASTEROID_BIG_1, AsteroidSize::BIG,    bigSplitInto,    3 },
	{ Sprite::ASTEROID_BIG_2, AsteroidSize::BIG,    bigSplitInto,    3 },
	{ Sprite::ASTEROID_BIG_3, AsteroidSize::BIG,    bigSplitInto,    3 },
	{ Sprite::ASTEROID_MEDIUM_1, AsteroidSize::MEDIUM, mediumSplitInto, 2 },
	{ Sprite::ASTEROID_MEDIUM_2, AsteroidSize::MEDIUM, mediumSplitInto, 2 },
	{ Sprite::ASTEROID_MEDIUM_3, AsteroidSize::MEDIUM, mediumSplitInto, 2 },
	{ Sprite::ASTEROID_SMALL_1, AsteroidSize::SMALL,  nullptr,         0 },
	{ Sprite::ASTEROID_SMALL_2, AsteroidSize::SMALL,  nullptr,         0 },
};


class Asteroid : public Entity
{
private:
	int typeIdx;

public:
	Asteroid(int typeIdx);
	std::unique_ptr<Asteroid> split();
};