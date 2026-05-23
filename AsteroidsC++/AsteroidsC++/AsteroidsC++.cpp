#include <raylib.h>
#include "Player.h"

#define FORWARD 1.0f
#define BACKWARD -1.0f
#define LEFT -1.0f
#define RIGHT 1.0f

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HIGHT = 600;

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HIGHT, "Asteroids C++");
    Vector2 center = Vector2{ WINDOW_WIDTH / 2 , WINDOW_HIGHT / 2 };
    Player player = Player(center);
    

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
        player.move();

        // drawing
        BeginDrawing();
        ClearBackground(BLACK);
        player.draw();
        EndDrawing();
    }

    CloseWindow();
}