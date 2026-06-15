#pragma once
#include "State.h"
#include <vector>
#include <string>

struct PlayerScore {
    std::string name;
    int score;
};

class ScoresState : public State {
private:
    std::vector<PlayerScore> highScores;
    void loadScores();

public:
    ScoresState();
    //void handleInput(App& app, float deltaTime) override;
    void update(App& app, float deltaTime) override;
    void draw() override;
};