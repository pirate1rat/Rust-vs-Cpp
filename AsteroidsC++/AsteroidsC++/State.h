#pragma once

class App;

class State {
public:
    virtual ~State() = default;
    virtual void update(App& app, float deltaTime) = 0;
    virtual void draw() = 0;
};