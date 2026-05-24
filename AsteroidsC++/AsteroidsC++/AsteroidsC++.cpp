#include <raylib.h>
#include "Player.h"
#include "Asteroid.h"
#include "Constants.h"
#include <time.h>

int main() {
    srand(time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HIGHT, "Asteroids C++");
    Vector2 center = Vector2{ WINDOW_WIDTH / 2 , WINDOW_HIGHT / 2 };
    Player player = Player(center);
    std::vector<Asteroid*> asteroids;
    int numOfAsteroids = rand() % MAX_ASTEROIDS + 2;

    for (int i = 0; i < numOfAsteroids; i++) {
        asteroids.push_back(new Asteroid());
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