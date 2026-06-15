#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Player.h"
#include "State.h"
#include "Asteroid.h"
#include "NameEntryState.h"
#include "App.h"

class PlayingState : public State
{
private:
    Player player;
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    float shotTimer = 0.0f;
    float inviolabilityTimer = 0.0f;

    int points = 0;
    int extraLives = 2;

public:
    PlayingState();
    void update(App& app, float deltaTime) override;
    void draw() override;
private:
    void handleInput(float deltaTime);
    void updateEntities(float deltaTime);
    bool checkCollisions();
    void clear();
};

