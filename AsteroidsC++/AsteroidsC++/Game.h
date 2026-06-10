#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Player.h"
#include "Asteroid.h"


class Game
{
private:
    Player player;
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    float shotTimer = 0.0f;
public:
    Game();
    void run();
private:
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void checkCollisions();
    void clear();
    void draw();
};

