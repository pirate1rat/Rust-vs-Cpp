#include <raylib.h>
#include <time.h>
#include "Player.h"
#include "Asteroid.h"
#include "Constants.h"
#include "Sprites.h"

#include <iostream>

int main() {
    srand(time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HIGHT, "Asteroids C++");
    Vector2 center = Vector2{ WINDOW_WIDTH / 2 , WINDOW_HIGHT / 2 };

    Player player = Player(center, Sprite::PLAYER);
    
    std::vector<Asteroid*> asteroids;
    int numOfAsteroids = (rand() % MAX_ASTEROIDS) + 4;

    for (int i = 0; i < numOfAsteroids; i++) {
        Sprite randomSprite = static_cast<Sprite>((rand() % (Sprite::ENUM_LENGTH - 2)) + 1);
        asteroids.push_back(new Asteroid(randomSprite));
    }
    

    while (!WindowShouldClose()) {
        // event handling
        if (IsKeyDown(KEY_UP)) {
            player.changeVelocity(FORWARD);
        }
        if (IsKeyDown(KEY_DOWN)) {
            player.changeVelocity(BACKWARD);
        }
        if (IsKeyDown(KEY_LEFT)) {
            player.rotate(LEFT);
        }
        if (IsKeyDown(KEY_RIGHT)) {
            player.rotate(RIGHT);
        }

        // updating
        for (int i = 0; i < numOfAsteroids; i++) {
            asteroids[i]->move();
        }
        player.move();

        //////////////
        for (int i = 0; i < numOfAsteroids; i++) {
            if (player.checkCollision(asteroids[i])) {
                std::cout << "kolizja! " << asteroids[i]->getPosition().x <<" "<< asteroids[i]->getPosition().y << std::endl;
                break;
            }
        }

        // drawing
        BeginDrawing();
        ClearBackground(BLACK);
        player.draw();
        for (int i = 0; i < numOfAsteroids; i++) {
            asteroids[i]->draw();
        }
        EndDrawing();
    }

    CloseWindow();
}