#include "ScoresState.h"
#include "App.h"
#include "MenuState.h"
#include "Constants.h"
#include <raylib.h>
#include <fstream>
#include <sstream>
#include <algorithm>

ScoresState::ScoresState() {
    loadScores();
}

void ScoresState::loadScores() {
    highScores.clear();
    std::ifstream file("scores.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        std::string scoreStr;

        if (std::getline(ss, name, ';') && std::getline(ss, scoreStr)) {
            try {
                int score = std::stoi(scoreStr);
                highScores.push_back({ name, score });
            }
            catch (...) {
                // Ignoruj błędnie sformatowane linie
            }
        }
    }
    file.close();

    // Sortowanie wyników malejąco
    std::sort(highScores.begin(), highScores.end(), [](const PlayerScore& a, const PlayerScore& b) {
        return a.score > b.score;
        });

    // Zostawiamy tylko top 5
    if (highScores.size() > 5) {
        highScores.resize(5);
    }
}

void ScoresState::update(App& app, float deltaTime) {
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
        app.changeState(std::make_unique<MenuState>());
    }
}

void ScoresState::draw() {
    DrawText("HIGH SCORES", WINDOW_WIDTH / 2 - MeasureText("HIGH SCORES", 36) / 2, 80, 36, GOLD);

    int startY = 180;
    for (size_t i = 0; i < highScores.size(); ++i) {
        std::string rankText = std::to_string(i + 1) + ". " + highScores[i].name;
        std::string scoreText = std::to_string(highScores[i].score);

        DrawText(rankText.c_str(), WINDOW_WIDTH / 2 - 150, startY + (i * 40), 20, RAYWHITE);
        DrawText(scoreText.c_str(), WINDOW_WIDTH / 2 + 80, startY + (i * 40), 20, YELLOW);
    }

    if (highScores.empty()) {
        DrawText("No scores yet!", WINDOW_WIDTH / 2 - MeasureText("No scores yet!", 20) / 2, 250, 20, GRAY);
    }

    DrawText("Press ESC / SPACE to return to Menu", WINDOW_WIDTH / 2 - MeasureText("Press ESC / SPACE to return to Menu", 16) / 2, 500, 16, GRAY);
}