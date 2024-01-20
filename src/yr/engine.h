#pragma once

#include <chrono>

class Level;
class ComponentGroupMap;
class EnttContext;

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

    Level* GetCurLevel();

    EnttContext* GetEnttContext();

public:
    float                                 deltaTime;
    std::chrono::steady_clock::time_point lastTickTimePoint {std::chrono::steady_clock::now()};

private:
    void CalDeltaTime();

    EnttContext* _enttContext;
};

extern Engine* gEngine;
