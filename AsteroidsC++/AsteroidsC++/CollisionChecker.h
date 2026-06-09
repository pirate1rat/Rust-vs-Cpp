#pragma once
#include "Sprites.h"
#include "Entity.h"
#include "Utils.h"

bool checkCollision(const SpriteStruct& prefabA, Vector2 posA, float rotA,
                    const SpriteStruct& prefabB, Vector2 posB, float rotB); // true if collides with other

