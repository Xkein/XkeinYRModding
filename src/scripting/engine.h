#pragma once

#include <chrono>
#include <mutex>

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
    void OnUIUpdate();

    void OnBeginRender();
    void OnEndRender();

public:
    float                                 deltaTime;
    std::chrono::steady_clock::time_point lastTickTimePoint {std::chrono::steady_clock::now()};
    std::mutex                            mutex;

private:
    void CalDeltaTime();

};

extern Engine* gEngine;
