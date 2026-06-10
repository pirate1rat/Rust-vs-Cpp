#include <raylib.h>
#include <time.h>
#include "Game.h"

int main() {
    srand(time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Asteroids C++");
    SetTargetFPS(120);

    Game game;
    game.run();

    CloseWindow();
}