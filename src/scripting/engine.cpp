#include "engine.h"
#ifdef IS_EDITOR
#include "scripting/editor/editor.h"
#endif
#include "runtime/logger/logger.h"
#include "runtime/ecs/entt.h"
#include "yr/yr_all_events.h"
#include "yr/extcore_config.h"
#include "scripting/components/script_component.h"
#include "scripting/javascript/js_env.h"
#include <GameClasses.h>

Engine* gEngine = new Engine();

REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioStartEvent, std::bind(&Engine::OnScenarioStart, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioClearEvent, std::bind(&Engine::OnScenarioClear, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, std::bind(&Engine::OnBeginUpdate, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, std::bind(&Engine::OnEndUpdate, gEngine));

REGISTER_YR_HOOK_EVENT_LISTENER(YrBeginRenderEvent, std::bind(&Engine::OnBeginRender, gEngine));
REGISTER_YR_HOOK_EVENT_LISTENER(YrEndRenderEvent, std::bind(&Engine::OnEndRender, gEngine));

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
}

void Engine::Start()
{
    gLogger->info("Engine::Start()");
    gJsEnv = std::make_shared<JsEnv>();
#ifdef IS_EDITOR
    EngineEditor::Start();
#endif
}

void Engine::Exit()
{
    gLogger->info("Engine::Exit()");
#ifdef IS_EDITOR
    EngineEditor::End();
#endif
    gJsEnv.reset();
}

void Engine::OnScenarioStart()
{
    gLogger->info("Engine::OnScenarioStart()");
}

void Engine::OnScenarioClear()
{
    gLogger->info("Engine::OnScenarioClear()");
}

#include "scripting/editor/editor.h"
void Engine::OnBeginUpdate()
{
    //gConsole->info("Engine::OnBeginUpdate()");
    mutex.lock();
    CalDeltaTime();
#ifdef IS_EDITOR
    EngineEditor::Tick();
#endif
    for (auto&& [entity, script] : gEntt->view<ScriptComponent>().each())
    {
        script.BeginUpdate();
    }
}

void Engine::OnEndUpdate()
{
    JsUpdate();

    for (auto&& [entity, script] : gEntt->view<ScriptComponent>().each())
    {
        script.EndUpdate();
    }
    mutex.unlock();
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
