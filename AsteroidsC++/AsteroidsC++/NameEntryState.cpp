#include "NameEntryState.h"
#include "App.h"
#include "ScoresState.h"
#include "Constants.h"
#include <raylib.h>
#include <fstream>

NameEntryState::NameEntryState(int score) {
    playerName = "";
    finalScore = score;
}

void NameEntryState::update(App& app, float deltaTime) {
    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (playerName.length() < maxChars)) {
            playerName += static_cast<char>(key);
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (!playerName.empty()) {
            playerName.pop_back();
        }
    }

    if (IsKeyPressed(KEY_ENTER) && !playerName.empty()) {
        std::ofstream file("scores.txt", std::ios::app);
        if (file.is_open()) {
            file << playerName << ";" << finalScore << "\n";
            file.close();
        }
        app.changeState(std::make_unique<ScoresState>());
    }
}

void NameEntryState::draw() {
    DrawText("GAME OVER", WINDOW_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, 100, 40, RED);

    DrawText(TextFormat("Your score: %d", finalScore), WINDOW_WIDTH / 2 - MeasureText(TextFormat("Your score: %d", finalScore), 24) / 2, 180, 24, RAYWHITE);
    DrawText("Enter your name:", WINDOW_WIDTH / 2 - MeasureText("Enter your name:", 20) / 2, 260, 20, GRAY);

    std::string displayName = playerName;
    if ((int)(GetTime() * 2) % 2 == 0 && playerName.length() < maxChars) {
        displayName += "|";
    }
    else {
        displayName += " ";
    }

    DrawText(displayName.c_str(), WINDOW_WIDTH / 2 - MeasureText(displayName.c_str(), 30) / 2, 330, 30, YELLOW);
    DrawText("Press ENTER to save", WINDOW_WIDTH / 2 - MeasureText("Press ENTER to save", 16) / 2, 450, 16, DARKGRAY);
}