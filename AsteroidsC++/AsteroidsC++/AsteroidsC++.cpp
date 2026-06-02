#include <raylib.h>
#include <time.h>
#include <memory>
#include <iostream>
#include "Player.h"
#include "Asteroid.h"
#include "Constants.h"
#include "Sprites.h"

int main() {
    srand(time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Asteroids C++");
    SetTargetFPS(120);

    Vector2 center = Vector2{ WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 };
    std::vector<std::unique_ptr<Entity>> entities;

    Player player = Player(center, Sprite::PLAYER);

    float shotTimer = 0.0f;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    int numOfAsteroids = (rand() % MAX_ASTEROIDS) + 4;

    for (int i = 0; i < numOfAsteroids; i++) {
        Sprite randomSprite = static_cast<Sprite>((rand() % (Sprite::PROJECTILE - 2)) + 1);
        asteroids.push_back(std::make_unique<Asteroid>(randomSprite));
    }
    

    while (!WindowShouldClose()) {
        // event handling
        float deltaTime = GetFrameTime();
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
            projectiles.push_back(player.createProjectile());
        }

        // updating
        for (auto& asteroid : asteroids) {
            asteroid->move(deltaTime);
        }
        for (auto& projectile : projectiles) {
            projectile->move(deltaTime);
        }
        player.move(deltaTime);

        // collisions
        for (auto& asteroid : asteroids) {
            if (player.checkCollision(*asteroid)) {
                std::cout << "kolizja! " << asteroid->getPosition().x <<" "<< asteroid->getPosition().y << std::endl;
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

        // clearing
        std::erase_if(asteroids, [](const auto& asteroid) {
            return asteroid == nullptr || !asteroid->alive;
        });
        std::erase_if(projectiles, [](const auto& p) {
            return !p->alive;
        });


        // drawing
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

    CloseWindow();
}