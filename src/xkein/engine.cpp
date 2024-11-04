#include "engine.h"
#include "runtime/logger/logger.h"
#include "runtime/ecs/entt.h"
#include "yr/yr_all_events.h"
#include "yr/extcore_config.h"
#include "scripting/components/script_component.h"
#include "scripting/javascript/js_env.h"
#include "audio/audio.h"
#include "physics/physics.h"
#include "ui/yr_uiext.h"
#include "input/input.h"
#include <GameClasses.h>

Engine* gEngine;

DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneEnterEvent) { if(gEngine) gEngine->OnSceneStart(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneExitEvent) { if(gEngine) gEngine->OnSceneClear(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneLoadEvent) { if(gEngine) gEngine->OnSceneLoad(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent) { if(gEngine) gEngine->OnBeginUpdate(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent) { if(gEngine) gEngine->OnEndUpdate(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent) { if(gEngine) gEngine->OnUIUpdate(); }

DEFINE_YR_HOOK_EVENT_LISTENER(YrBeginRenderEvent) { if(gEngine) gEngine->OnBeginRender(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrEndRenderEvent) { if(gEngine) gEngine->OnEndRender(); }

DEFINE_YR_HOOK_EVENT_LISTENER(YrMainWndProcEvent) {
    if (Input::gManager) {
        MSG msg { E->hWnd, E->uMsg, E->wParam, E->lParam };
        Input::gManager->HandleMessage(msg);
    }
}

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

    Physics::Init();
    AudioSystem::Init();
    Input::Init();

    gJsEnv = new JsEnv();
}

void Engine::Exit()
{
    gLogger->info("Engine::Exit()");
    ScriptComponent::OnJsEnvDestroy();
    delete gJsEnv;
    gJsEnv = nullptr;

    Physics::Destroy();
    AudioSystem::Destroy();
    Input::Destroy();
}

void Engine::OnSceneLoad()
{
    gLogger->info("Engine::OnSceneLoad()");
    Physics::LoadWorld();
}

void Engine::OnSceneStart()
{
    gLogger->info("Engine::OnSceneStart()");
    Physics::EnterWorld();
    AudioSystem::InitWorld();
}

void Engine::OnSceneClear()
{
    gLogger->info("Engine::OnSceneClear()");
    Physics::ExitWorld();
    AudioSystem::DestroyWorld();
}

static void JsUpdate()
{
    if (gJsEnv)
    {
        gJsEnv->InspectorTick();
        gJsEnv->LogicTick();
    }
}

void Engine::OnBeginUpdate()
{
    //gConsole->info("Engine::OnBeginUpdate()");
    CalDeltaTime();

    Input::Tick();
    
    if (gJsEnv)
    {
        gJsEnv->mutex.lock();
        for (auto&& [entity, script] : gEntt->view<ScriptComponent>().each())
        {
            script.Invoke(script.OnBeginUpdate);
        }
    }

    Physics::BeginTick();
}

void Engine::OnEndUpdate()
{
    JsUpdate();

    if (gJsEnv)
    {
        for (auto&& [entity, script] : gEntt->view<ScriptComponent>().each())
        {
            script.Invoke(script.OnEndUpdate);
        }
        gJsEnv->mutex.unlock();
    }

    Physics::EndTick();
    AudioSystem::Tick();

    YrExtUIModule::UIMainThread();
}

void Engine::OnUIUpdate()
{
    Input::Tick();

    JsUpdate();
    AudioSystem::Tick();
    
    YrExtUIModule::UIMainThread();
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
