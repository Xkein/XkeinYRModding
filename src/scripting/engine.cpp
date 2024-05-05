#include "engine.h"

#include "yr/event/general_event.h"
#include "core/logger/logger.h"

Engine* gEngine = new Engine();

REGISTER_YR_HOOK_EVENT_LISTENER(YrBootEvent, std::bind(&Engine::Start, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrTerminateEvent, std::bind(&Engine::Exit, gEngine));

REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioStartEvent, std::bind(&Engine::OnScenarioStart, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioClearEvent, std::bind(&Engine::OnScenarioClear, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, std::bind(&Engine::OnBeginUpdate, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, std::bind(&Engine::OnEndUpdate, gEngine));

REGISTER_YR_HOOK_EVENT_LISTENER(YrBeginRenderEvent, std::bind(&Engine::OnBeginRender, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrEndRenderEvent, std::bind(&Engine::OnEndRender, gEngine));

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Start()
{
    gLogger->info("Engine::Start()");
}

void Engine::Exit()
{
    gLogger->info("Engine::Exit()");
}

void Engine::OnScenarioStart()
{
    gLogger->info("Engine::OnScenarioStart()");
}

void Engine::OnScenarioClear()
{
    gLogger->info("Engine::OnScenarioClear()");
}

#include "editor/graph_editor.h"
std::shared_ptr<GraphEditor> editor;
void Engine::OnBeginUpdate()
{
    //gConsole->info("Engine::OnBeginUpdate()");
    CalDeltaTime();

    if (ImGui::IsKeyReleased(ImGuiKey_F12))
    {
        if (editor)
        {
            editor.reset();
        }
        else
        {
            editor = std::make_shared<GraphEditor>();
        }
    }
}

void Engine::OnEndUpdate()
{
}

void Engine::OnBeginRender()
{
    //gConsole->info("Engine::OnBeginRender()");

}

void Engine::OnEndRender()
{

}

void Engine::CalDeltaTime()
{
    using namespace std::chrono;
    steady_clock::time_point tickTimePoint = steady_clock::now();

    duration<float> timeSpan = duration_cast<duration<float>>(tickTimePoint - lastTickTimePoint);

    deltaTime         = timeSpan.count();
    lastTickTimePoint = tickTimePoint;
}
