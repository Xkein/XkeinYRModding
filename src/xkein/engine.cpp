#include "engine.h"
#include "scripting/javascript/js_events.h"
#include "runtime/logger/logger.h"
#include "runtime/ecs/entt.h"
#include "yr/yr_all_events.h"
#include "yr/extcore_config.h"
#include "scripting/javascript/js_env.h"
#include "audio/audio.h"
#include "physics/physics.h"
#include "ui/yr_uiext.h"
#include "input/input.h"
#include "xkein/fog/fog_data.h"
#include <GameClasses.h>

Engine* gEngine = nullptr;

DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneEnterEvent) { if(gEngine) gEngine->OnSceneStart(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneExitEvent) { if(gEngine) gEngine->OnSceneClear(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneLoadEvent) { if(gEngine) gEngine->OnSceneLoad(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent) { if(gEngine) gEngine->OnBeginUpdate(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent) { if(gEngine) gEngine->OnEndUpdate(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent) { if(gEngine && gEngine->started) gEngine->OnUIUpdate(); }

DEFINE_YR_HOOK_EVENT_LISTENER(YrBeginRenderEvent) { if(gEngine) gEngine->OnBeginRender(); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrEndRenderEvent) { if(gEngine) gEngine->OnEndRender(); }

DEFINE_YR_HOOK_EVENT_LISTENER(YrMainWndProcEvent) {
    if (Input::gManager) {
        MSG msg { E->hWnd, E->uMsg, E->wParam, E->lParam };
        Input::gManager->HandleMessage(msg);
    }
}

Engine::Engine() : started(false)
{

}

Engine::~Engine()
{
    this->Exit();
}

void Engine::Start()
{
    if (started)
        return;
    started = true;
    gLogger->info("Engine::Start()");

    Physics::Init();
    AudioSystem::Init();
    Input::Init();
    YrExtUIModule::InitUIModule();
    if (gYrExtConfig->rawData.value("enable_js_module", true))
    {
        gJsEnv = new JsEnv();
    }
}

void Engine::Exit()
{
    if (!started)
        return;
    started = false;
    gLogger->info("Engine::Exit()");

    if (gJsEnv) {
        // INVOKE_JS_EVENT(JsEvents::game.onApplicationQuit);
        delete gJsEnv;
        gJsEnv = nullptr;
    }

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

    FogSystem::Init();
}

void Engine::OnSceneClear()
{
    gLogger->info("Engine::OnSceneClear()");
    
    FogSystem::Clear();

    if (gJsEnv) {
        gJsEnv->UnbindAllYrObjects();
    }
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
        INVOKE_JS_EVENT(JsEvents::game.onBeginUpdate);
    }

    Physics::BeginTick();
}

void Engine::OnEndUpdate()
{
    JsUpdate();

    if (gJsEnv)
    {
        INVOKE_JS_EVENT(JsEvents::game.onEndUpdate);
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
