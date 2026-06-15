#pragma once
#include "State.h"

class MenuState : public State {
private:
    int selectedOption = 0;
    const int optionCount = 2; // 0: Start Game, 1: Scores

public:
    MenuState();
    void update(App& app, float deltaTime) override;
    void draw() override;
};