#pragma once
#include "Entity.h"
#include "Constants.h"

class Asteroid : public Entity
{
public:
	Asteroid();
	float randFloat(float min, float max);
};

