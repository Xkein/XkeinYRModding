#include "engine.h"

#include "yr/event/general_event.h"

Engine* gEngine = new Engine();

REGISTER_YR_HOOK_EVENT_LISTENER(YrBootEvent, std::bind(&Engine::Start, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrTerminateEvent, std::bind(&Engine::Exit, gEngine));

REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioStartEvent, std::bind(&Engine::OnScenarioStart, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioClearEvent, std::bind(&Engine::OnScenarioClear, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, std::bind(&Engine::OnBeginUpdate, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, std::bind(&Engine::OnEndUpdate, gEngine));

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Start() {

}

void Engine::Exit()
{

}

void Engine::OnScenarioStart()
{

}

void Engine::OnScenarioClear()
{

}
#include <MessageListClass.h>
void Engine::OnBeginUpdate()
{
    CalDeltaTime();

    MessageListClass::Instance->PrintMessage(L"Engine::OnBeginUpdate");
}

void Engine::OnEndUpdate()
{
    
}

void Engine::OnBeginRender()
{

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
