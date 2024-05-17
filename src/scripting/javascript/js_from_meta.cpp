#include "js_env.h"
#include <v8-context.h>
#include <v8-exception.h>
#include <v8-initialization.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-script.h>
#include <v8-template.h>

#include <libplatform/libplatform.h>
#include <entt/meta/meta.hpp>
#include <entt/meta/resolve.hpp>
#include <entt/core/hashed_string.hpp>
#include <core/logger/logger.h>
#include <map>

using namespace entt::literals;

std::map<size_t, bool> gRegistered;

bool JsEnv::RegisterFromMeta(size_t enttId)
{
    auto meta = entt::resolve(enttId);
    auto nameProp = meta.prop("name"_hs);
    if (!nameProp)
    {
        gLogger->error("unable to register javascript object template from meta by id={}", enttId);
        return false;
    }


    auto name = nameProp.value().cast<const char*>();

    return true;
}

bool JsEnv::UnregisterFromMeta(size_t enttId)
{
    auto meta = entt::resolve(enttId);

    
    return true;
}

v8::Local<v8::ObjectTemplate> JsEnv::GetCppObjects()
{
    auto localContext = context->Get(isolate);

    auto global = localContext->Global();
    auto cpp    = global->Get(localContext, v8::String::NewFromUtf8(isolate, "Cpp").ToLocalChecked());
    return cpp.ToLocalChecked();
}

v8::Intercepted CppMapGet(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    int id = name->GetIdentityHash();
    if (gRegistered.contains(id))
    {
        return v8::Intercepted::kYes;
    }

    auto nameStr = name.As<v8::String>();
    info.GetReturnValue().;
    gRegistered[id] = true;
}

v8::Local<v8::ObjectTemplate> JsEnv::CreateCppObjects()
{
    v8::Local<v8::ObjectTemplate> cpp = v8::ObjectTemplate::New(isolate);
    auto namedConfig = v8::NamedPropertyHandlerConfiguration(CppMapGet);
    cpp->SetHandler(namedConfig);
}

