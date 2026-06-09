#pragma once
#include <cstdlib>
#include <algorithm>
#include "raylib.h"
#include "raymath.h"
#include "Constants.h"

Vector2 transform(Vector2 p, Vector2 position, float rotation);
float randFloat(float min, float max);
float cross(Vector2 a, Vector2 b, Vector2 c);
bool onSegment(Vector2 a, Vector2 b, Vector2 p);