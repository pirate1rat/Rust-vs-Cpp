#include <raylib.h>
#include <time.h>
#include "App.h"
#include "Constants.h"

int main() {
    srand(time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "AsteroidsC++");
    SetTargetFPS(120);

    App app;
    app.run();

    CloseWindow();
}