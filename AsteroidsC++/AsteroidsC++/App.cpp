#include "App.h"
#include "State.h"
#include "MenuState.h"
#include <raylib.h>

App::App() {
    currentState = std::make_unique<MenuState>();
}

App::~App() {
}

void App::run() {
    while (!shouldExit && !WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        currentState->update(*this, deltaTime);

        BeginDrawing();
        ClearBackground(BLACK);
        currentState->draw();
        EndDrawing();
    }
}

void App::changeState(std::unique_ptr<State> newState) {
    if (newState) {
        currentState = std::move(newState);
    }
}

void App::exitGame() {
    shouldExit = true;
}