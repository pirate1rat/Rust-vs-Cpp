#include <raylib.h>
#include <time.h>
#include <memory>
#include "Player.h"
#include "Asteroid.h"
#include "Constants.h"
#include "Sprites.h"

#include <iostream>

int main() {
    srand(time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Asteroids C++");
    SetTargetFPS(60);

    Vector2 center = Vector2{ WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 };

    Player player = Player(center, Sprite::PLAYER);
    
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    int numOfAsteroids = (rand() % MAX_ASTEROIDS) + 4;

    for (int i = 0; i < numOfAsteroids; i++) {
        Sprite randomSprite = static_cast<Sprite>((rand() % (Sprite::ENUM_LENGTH - 2)) + 1);
        asteroids.push_back(std::make_unique<Asteroid>(randomSprite));
    }
    

    while (!WindowShouldClose()) {
        // event handling
        float deltaTime = GetFrameTime();

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

        // updating
        for (auto& asteroid : asteroids) {
            asteroid->move(deltaTime);
        }
        player.move(deltaTime);

        //////////////
        for (auto& asteroid : asteroids) {
            if (player.checkCollision(*asteroid)) {
                std::cout << "kolizja! " << asteroid->getPosition().x <<" "<< asteroid->getPosition().y << std::endl;
                break;
            }
        }

        // drawing
        BeginDrawing();
        ClearBackground(BLACK);
        player.draw();
        for (auto& asteroid : asteroids) {
            asteroid->draw();
        }
        EndDrawing();
    }

    CloseWindow();
}