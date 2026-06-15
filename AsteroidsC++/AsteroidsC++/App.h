#pragma once
#include <memory>

class State;

class App
{
private:
    std::unique_ptr<State> currentState;
    bool shouldExit = false;

public:
    App();
    ~App();

    void run();
    void changeState(std::unique_ptr<State> newState);
    void exitGame();
};

