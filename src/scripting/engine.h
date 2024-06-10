#pragma once

#include <chrono>

class Engine
{
public:
    Engine();
    ~Engine();

    void Start();
    void Exit();

    void OnScenarioStart();
    void OnScenarioClear();

    void OnBeginUpdate();
    void OnEndUpdate();

    void OnBeginRender();
    void OnEndRender();

public:
    float                                 deltaTime;
    std::chrono::steady_clock::time_point lastTickTimePoint {std::chrono::steady_clock::now()};

private:
    void CalDeltaTime();

};

extern Engine* gEngine;
