#pragma once
#include "State.h"
#include <string>

class NameEntryState : public State {
private:
    int finalScore;
    std::string playerName;
    const size_t maxChars = 8;

public:
    NameEntryState(int score);
    //void handleInput(App& app, float deltaTime) override;
    void update(App& app, float deltaTime) override;
    void draw() override;
};

