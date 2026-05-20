#include <raylib.h>

int main()
{
    InitWindow(800, 600, "raylib 6");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("dziala", 300, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
}