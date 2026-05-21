#include <raylib.h>
#include "Player.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HIGHT = 600;

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HIGHT, "Asteroids C++");
    Vector2 center = Vector2{ WINDOW_WIDTH / 2 , WINDOW_HIGHT / 2 };
    Player player = Player(center);
    

    while (!WindowShouldClose()) {
        // event handling
        if (IsKeyDown(KEY_UP)) {
            player.Move();
        }
        else if (IsKeyDown(KEY_LEFT)) {
            player.Rotate(-1);
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            player.Rotate(1);
        }

        // updating

        // drawing
        BeginDrawing();
        ClearBackground(BLACK);
        player.Draw();
        EndDrawing();
    }

    CloseWindow();
}