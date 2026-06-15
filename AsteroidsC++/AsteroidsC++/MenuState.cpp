#include "MenuState.h"
#include "PlayingState.h"
#include "App.h"
#include "ScoresState.h"
#include "Constants.h"
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
    DrawText("ASTEROIDS", WINDOW_WIDTH / 2 - MeasureText("ASTEROIDS", 40) / 2, 150, 40, RAYWHITE);

    Color playColor = (selectedOption == 0) ? YELLOW : RAYWHITE;
    Color scoreColor = (selectedOption == 1) ? YELLOW : RAYWHITE;

    DrawText("Play", WINDOW_WIDTH / 2 - MeasureText("Play", 20) / 2, 300, 20, playColor);
    DrawText("Scores", WINDOW_WIDTH / 2 - MeasureText("Scores", 20) / 2, 350, 20, scoreColor);
}