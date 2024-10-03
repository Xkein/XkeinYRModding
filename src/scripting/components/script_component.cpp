#include "scripting/components/script_component.h"
#include "scripting/javascript/yr_binding.h"
#include "scripting/javascript/js_env.h"

struct V8ObjectWrapper {
    V8ObjectWrapper() = default;
    V8ObjectWrapper(v8::Local<v8::Context> context, v8::Local<v8::Value> object)
    {
        auto Isolate = context->GetIsolate();
        v8Object.Reset(Isolate, object.As<v8::Object>());
    }

    v8::Global<v8::Object> v8Object;
};

namespace PUERTS_NAMESPACE
{
    namespace v8_impl
    {
        template <>
        struct Converter<V8ObjectWrapper>
        {
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, V8ObjectWrapper const& value)
            {
                return value.v8Object.Get(context->GetIsolate());
            }

            static V8ObjectWrapper toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return V8ObjectWrapper(context, value.As<v8::Object>());
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return value->IsObject();
            }
        };
    }
}


struct JsScriptTemplate
{
    JsScriptTemplate(std::string_view scriptName) : ScriptName(scriptName)
    {
        if (!gJsEnv->Eval(std::format("yr.createScriptTemplate(\"{}\")", scriptName).c_str(), "game script", &ScriptTemplate))
        {
            gLogger->error(gJsEnv->LastExceptionInfo);
            return;
        }

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

        V8ObjectWrapper wrapper = std::move(ScriptCtor(scriptCom, pYrObject));
        // scriptCom->jsObject = std::move(wrapper.v8Object);
    }

private:
    std::function<V8ObjectWrapper(ScriptComponent* scriptCom, AbstractClass* pYrObject)> ScriptCtor;

    v8::Global<v8::Value> ScriptTemplate;
    std::string_view      ScriptName;
};

std::map<std::string, JsScriptTemplate> gJsScripts;

void ScriptComponent::CreateScriptComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType) {
    if (!pYrType)
        return;
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
        script.pYrObject = pYrObject;
    }
}

void ScriptComponent::OnJsEnvDestroy()
{
    gJsScripts.clear();
}

ScriptComponent::~ScriptComponent()
{
    Invoke(OnDtor);
    if (gJsEnv)
    {
        gJsEnv->Unbind(pYrObject);
    }
}

#include "yr/yr_all_events.h"
#include "yr/api/yr_entity.h"
#include <SuperClass.h>

DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletConstructEvent)
{
    ScriptComponent::OnEntityConstruct(*gEntt, GetYrEntity(E->pBullet), E->pBullet);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectReceiveDamageEvent) {
    ScriptComponent* script = GetYrComponent<ScriptComponent>(E->pObject);
    if (script) {
        std::optional<DamageState> damageState = script->Invoke(script->OnReceiveDamage, E->pDamage, E->DistanceFromEpicenter, E->pWH, E->Attacker, E->IgnoreDefenses, E-> PreventPassengerEscape, E->pAttackingHouse);
        if (damageState) {
            E->OverrideReturn(damageState.value());
        }
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoFireEvent) {
    ScriptComponent* script = GetYrComponent<ScriptComponent>(E->pTechno);
    if (script) {
        std::optional<BulletClass*> pBullet = script->Invoke(script->OnFire, E->pTarget, E->nWeaponIndex);
        if (pBullet) {
            E->OverrideReturn(pBullet.value());
        }
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletDetonateEvent) {
    ScriptComponent* script = GetYrComponent<ScriptComponent>(E->pBullet);
    if (script) {
        script->Invoke(script->OnDetonate, *E->pCoords);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperLaunchEvent) {
    ScriptComponent* script = GetYrComponent<ScriptComponent>(E->pSuper);
    if (script) {
        script->Invoke(script->OnLaunch, *E->pCell, E->isPlayer);
    }
}