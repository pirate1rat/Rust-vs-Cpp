#include "MenuState.h"
#include "PlayingState.h"
#include "App.h"
#include "ScoresState.h"
#include "Constants.h"
#include "Renderer.h"
#include <raylib.h>

MenuState::MenuState() {
}

void MenuState::update(App& app, float deltaTime) {
    if (IsKeyPressed(KEY_UP)) {
        selectedOption = (selectedOption - 1 + optionCount) % optionCount;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        selectedOption = (selectedOption + 1) % optionCount;
    }

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
        if (selectedOption == 0) {
            app.changeState(std::make_unique<PlayingState>());
        }
        else if (selectedOption == 1) {
            app.changeState(std::make_unique<ScoresState>());
        }
    }
}

void MenuState::draw() {
    DrawText("ASTEROIDS", WINDOW_WIDTH / 2 - MeasureText("ASTEROIDS", 72) / 2, WINDOW_HEIGHT / 4, 72, RAYWHITE);
    DrawOption("Play", WINDOW_HEIGHT / 2 - 20, selectedOption == 0);
    DrawOption("Scores", WINDOW_HEIGHT / 2 + 60, selectedOption == 1);
}