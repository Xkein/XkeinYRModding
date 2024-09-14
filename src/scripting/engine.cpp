#include "engine.h"
#include "runtime/logger/logger.h"
#include "runtime/ecs/entt.h"
#include "yr/yr_all_events.h"
#include "yr/extcore_config.h"
#include "scripting/components/script_component.h"
#include "scripting/javascript/js_env.h"
#include <GameClasses.h>

Engine* gEngine;

DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneEnterEvent) { if(gEngine) gEngine->OnScenarioStart(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneExitEvent) { if(gEngine) gEngine->OnScenarioClear(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent) { if(gEngine) gEngine->OnBeginUpdate(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent) { if(gEngine) gEngine->OnEndUpdate(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent) { if(gEngine) gEngine->OnUIUpdate(); }

DEFINE_YR_HOOK_EVENT_LISTENER(YrBeginRenderEvent) { if(gEngine) gEngine->OnBeginRender(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrEndRenderEvent) { if(gEngine) gEngine->OnEndRender(); }

static void JsUpdate()
{
    if (gJsEnv)
    {
        gJsEnv->InspectorTick();
        gJsEnv->LogicTick();
    }
}

REGISTER_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent, JsUpdate)

Engine::Engine()
{

}

Engine::~Engine()
{
    this->Exit();
}

void Engine::Start()
{
    gLogger->info("Engine::Start()");
    gJsEnv = new JsEnv();
}

void Engine::Exit()
{
    gLogger->info("Engine::Exit()");
    delete gJsEnv;
    gJsEnv = nullptr;
}

void Engine::OnScenarioStart()
{
    gLogger->info("Engine::OnScenarioStart()");
}

void Engine::OnScenarioClear()
{
    gLogger->info("Engine::OnScenarioClear()");
}

void Engine::OnBeginUpdate()
{
    //gConsole->info("Engine::OnBeginUpdate()");
    mutex.lock();
    CalDeltaTime();
    for (auto&& [entity, script] : gEntt->view<ScriptComponent>().each())
    {
        script.Invoke(script.OnBeginUpdate);
    }
}

void Engine::OnEndUpdate()
{
    JsUpdate();

    for (auto&& [entity, script] : gEntt->view<ScriptComponent>().each())
    {
        script.Invoke(script.OnEndUpdate);
    }
    mutex.unlock();
}

void Engine::OnUIUpdate()
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
