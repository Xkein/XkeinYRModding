#include "engine.h"

#include "core/logger/logger.h"
#include "runtime/ecs/entt.h"
#include "yr/yr_all_events.h"
#include "yr/extcore_config.h"
#include "scripting/components/script_component.h"
#include "scripting/javascript/js_env.h"
#include "scripting/javascript/yr_binding.h"
#include "yr/api/yr_entity.h"
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

struct JsScriptTemplate
{
    JsScriptTemplate(std::string_view scriptName) : ScriptName(scriptName)
    {
        if (!gJsEnv->Eval(std::format("yr.createScriptTemplate(\"{}\")", scriptName).c_str(), "game script", &ScriptTemplate))
            return;

        auto Isolate = gJsEnv->MainIsolate;
#ifdef THREAD_SAFE
        v8::Locker Locker(Isolate);
#endif
        v8::Isolate::Scope IsolateScope(Isolate);
        v8::HandleScope    HandleScope(Isolate);
        auto               Context = v8::Local<v8::Context>::New(Isolate, gJsEnv->DefaultContext);
        v8::Context::Scope ContextScope(Context);

        auto GameScript = ScriptTemplate.Get(Isolate)->ToObject(Context).ToLocalChecked();
        auto MaybeCtor  = GameScript->Get(Context, JsEnv::ToV8String(Isolate, "__constructor__"));
        if (MaybeCtor.IsEmpty() || !MaybeCtor.ToLocalChecked()->IsFunction())
        {
            gLogger->error("{}.__constructor__ not found!", ScriptName);
            return;
        }

        auto Ctor = MaybeCtor.ToLocalChecked().As<v8::Function>();
        ScriptCtor = PUERTS_NAMESPACE::v8_impl::Converter<decltype(ScriptCtor)>::toCpp(Context, Ctor);
        if (!ScriptCtor)
        {
            gLogger->error("{}.__constructor__ could not convert to std::function!", ScriptName);
        }
    }

    void Instantiate(ScriptComponent* scriptCom, AbstractClass* pYrObject)
    {
        if (!ScriptCtor)
            return;

        ScriptCtor(scriptCom, pYrObject);
    }

private:
    std::function<void(ScriptComponent* scriptCom, AbstractClass* pYrObject)> ScriptCtor;

    v8::Global<v8::Value> ScriptTemplate;
    std::string_view      ScriptName;
};

std::map<std::string, JsScriptTemplate> gJsScripts;

void ScriptComponent::CreateScriptComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType) {
    ScriptTypeComponent const* const pScriptType = GetYrComponent<ScriptTypeComponent>(pYrType);
    if (pScriptType && !pScriptType->jsScript.empty())
    {
        auto& name = pScriptType->jsScript;
        auto  iter = gJsScripts.find(name);
        if (iter == gJsScripts.end())
        {
            iter = gJsScripts.insert_or_assign(name, JsScriptTemplate(name)).first;
        }

        ScriptComponent& script = reg.emplace<ScriptComponent>(entity);
        iter->second.Instantiate(&script, pYrObject);
    }
}

void Engine::Start()
{
    gLogger->info("Engine::Start()");
    gJsEnv = std::make_shared<JsEnv>();
#ifndef NDEBUG
    int32 port = gYrExtConfig->rawData.value("js_debug_port", 9229);
    gJsEnv->CreateInspector(port);
#endif // DEBUG
}

void Engine::Exit()
{
    gLogger->info("Engine::Exit()");
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
    CalDeltaTime();

    EngineEditor::Tick();

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
