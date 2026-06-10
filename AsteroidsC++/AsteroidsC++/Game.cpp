#include "Game.h"

Game::Game() : player(Vector2{ WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 }, Sprite::PLAYER) {
    int numOfAsteroids = (rand() % MAX_ASTEROIDS) + 4;

    for (int i = 0; i < numOfAsteroids; i++) {
        Sprite randomSprite = static_cast<Sprite>((rand() % (Sprite::PROJECTILE - 2)) + 1);
        asteroids.push_back(std::make_unique<Asteroid>(randomSprite));
    }
}

void Game::run() {
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        handleInput(deltaTime);
        update(deltaTime);
        clear();
        checkCollisions();
        draw();
    }
}

void Game::handleInput(float deltaTime) {
    shotTimer -= deltaTime;

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
        std::cout << "piuu!\n";
        projectiles.push_back(player.shootProjectile());
    }
}

void Game::update(float deltaTime) {
    for (auto& asteroid : asteroids) {
        asteroid->move(deltaTime);
    }
    for (auto& projectile : projectiles) {
        projectile->move(deltaTime);
    }
    player.move(deltaTime);
}

void Game::checkCollisions() {
    for (auto& asteroid : asteroids) {
        if (player.checkCollision(*asteroid)) {
            std::cout << "kolizja! " << asteroid->getPosition().x << " " << asteroid->getPosition().y << std::endl;
            break;
        }
    }

    std::vector<std::unique_ptr<Asteroid>> newAsteroids; // a valuable lesson - do not modify vector during iteration
    for (auto& projectile : projectiles) {
        for (auto& asteroid : asteroids) {
            if (!asteroid) continue;

            if (projectile->checkCollision(*asteroid)) {
                projectile->alive = false;

                auto splitAst = asteroid->split();
                if (splitAst)
                    newAsteroids.push_back(std::move(splitAst));
            }
        }
    }
    for (auto& a : newAsteroids)
        asteroids.push_back(std::move(a));
}

void Game::clear() {
    std::erase_if(asteroids, [](const auto& asteroid) {
        return asteroid == nullptr || !asteroid->alive;
        });
    std::erase_if(projectiles, [](const auto& p) {
        return !p->alive;
        });
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    player.draw();
    for (auto& asteroid : asteroids) {
        asteroid->draw();
    }
    for (auto& projectile : projectiles) {
        projectile->draw();
    }
    EndDrawing();
}
