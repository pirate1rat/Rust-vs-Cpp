#include "PlayingState.h"

PlayingState::PlayingState() : player(Vector2{ WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 }, Sprite::PLAYER) {
    int numOfAsteroids = (rand() % MAX_ASTEROIDS) + 4;

    for (int i = 0; i < numOfAsteroids; i++) {
        Sprite randomSprite = static_cast<Sprite>((rand() % (Sprite::PROJECTILE - 2)) + 1);
        asteroids.push_back(std::make_unique<Asteroid>(randomSprite));
    }
}

void PlayingState::update(App& app, float deltaTime) {
    handleInput(deltaTime);
    updateEntities(deltaTime);
    if (checkCollisions()) {
        app.changeState(std::make_unique<NameEntryState>(points));
        return;
    }
    clear();
}

void PlayingState::handleInput(float deltaTime) {
    shotTimer -= deltaTime;
    inviolabilityTimer -= deltaTime;

    if (IsKeyDown(KEY_UP)) {
        player.changeVelocity(FORWARD, deltaTime);
    }
    if (IsKeyDown(KEY_DOWN)) {
        player.changeVelocity(BACKWARD, deltaTime);
    }
    if (IsKeyDown(KEY_LEFT)) {
        player.rotate(LEFT, deltaTime);
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player.rotate(RIGHT, deltaTime);
    }
    if (IsKeyPressed(KEY_SPACE) && shotTimer <= 0) {
        shotTimer = PLAYER_SHOT_TIMER;
        projectiles.push_back(player.shootProjectile());
    }
}

void PlayingState::updateEntities(float deltaTime) {
    for (auto& asteroid : asteroids) {
        asteroid->move(deltaTime);
    }
    for (auto& projectile : projectiles) {
        projectile->move(deltaTime);
    }
    player.move(deltaTime);
}

bool PlayingState::checkCollisions() {
    for (auto& asteroid : asteroids) {
        if (player.checkCollision(*asteroid) && inviolabilityTimer <= 0) {
            if (extraLives == 0) {
                return true;
            }
            else {
                extraLives -= 1;
                inviolabilityTimer = PLAYER_INVIOLABILITY_TIMER;
                player.respawn();
            }
        }
    }

    std::vector<std::unique_ptr<Asteroid>> newAsteroids; // a valuable lesson - do not modify vector during iteration
    for (auto& projectile : projectiles) {
        for (auto& asteroid : asteroids) {
            if (!asteroid) continue;

            if (projectile->checkCollision(*asteroid)) {
                switch (asteroid->size) {
                case AsteroidSize::BIG:
                    points += 10;
                    break;
                case AsteroidSize::MEDIUM:
                    points += 15;
                    break;
                case AsteroidSize::SMALL:
                    points += 20;
                    break;
                }

                projectile->alive = false;

                auto splitAst = asteroid->split();
                if (splitAst)
                    newAsteroids.push_back(std::move(splitAst));
            }
        }
    }
    for (auto& a : newAsteroids)
        asteroids.push_back(std::move(a));

    return false;
}

void PlayingState::clear() {
    std::erase_if(asteroids, [](const auto& asteroid) {
        return asteroid == nullptr || !asteroid->alive;
        });
    std::erase_if(projectiles, [](const auto& p) {
        return !p->alive;
        });

    if (asteroids.empty()) {
        reset();
    }
}

void PlayingState::reset() {
    int numOfAsteroids = (rand() % MAX_ASTEROIDS) + 4;

    for (int i = 0; i < numOfAsteroids; i++) {
        Sprite randomSprite = static_cast<Sprite>((rand() % (Sprite::PROJECTILE - 2)) + 1);
        asteroids.push_back(std::make_unique<Asteroid>(randomSprite));
    }

    player.respawn();
}

void PlayingState::draw() {
    player.draw();
    for (auto& asteroid : asteroids) {
        asteroid->draw();
    }
    for (auto& projectile : projectiles) {
        projectile->draw();
    }

    std::string livesText = std::format("extra lives: {}", extraLives);
    std::string pointsText = std::format("points: {}", points);

    DrawText(livesText.c_str(), 20, 20, 20, RAYWHITE);
    DrawText(pointsText.c_str(), 
        WINDOW_WIDTH - MeasureText(pointsText.c_str(), 20) - 20,
        20, 20, RAYWHITE);
}
