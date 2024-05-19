#include "js_env.h"
#include <v8-context.h>
#include <v8-exception.h>
#include <v8-initialization.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-script.h>
#include <v8-template.h>
#include <v8-external.h>

#include <libplatform/libplatform.h>
#include <entt/meta/meta.hpp>
#include <entt/meta/resolve.hpp>
#include <entt/core/hashed_string.hpp>
#include <core/logger/logger.h>
#include <map>
#include <string>

using namespace entt::literals;

std::map<size_t, bool> gRegistered;



bool GetReturnValue(const entt::meta_any& any, v8::ReturnValue<v8::Value> returnVal)
{
    any.type();
    if (any.type())
    returnVal.Set(, );
}

bool SetReturnValue() {

}

bool JsEnv::RegisterFromMeta(size_t enttId)
{
    entt::meta_type meta = entt::resolve(enttId);
    auto nameProp = meta.prop("name"_hs);
    if (!nameProp)
    {
        gLogger->error("unable to register javascript object template from meta by id={}", enttId);
        return false;
    }

    auto name     = nameProp.value().cast<const char*>();
    auto cppLocal = cpp.Get(isolate);

    v8::Local<v8::ObjectTemplate> objTemplate = v8::ObjectTemplate::New(isolate);
    objTemplate->SetInternalFieldCount(1);

    for (auto&& [id, field] : meta.data())
    {
        auto fieldName = meta.prop("name"_hs).value().cast<const char*>();
        objTemplate->SetAccessor(
            v8::String::NewFromUtf8(isolate, fieldName).ToLocalChecked(),
            [](v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
            v8::Local<v8::Object>   self  = info.Holder();
            v8::Local<v8::External> wrap  = v8::Local<v8::External>::Cast(self->GetInternalField(0));
            void*                   ptr   = wrap->Value();
            entt::meta_any val = field.get(ptr);
            GetReturnValue(val, info.GetReturnValue(), v8::External::New(isolate, ));
        },
        [](v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info) {

        });
    }


    return true;
}

bool JsEnv::UnregisterFromMeta(size_t enttId)
{
    auto meta = entt::resolve(enttId);
    gLogger->error("JsEnv::UnregisterFromMeta not implement!");
    
    return true;
}

// Convert a JavaScript string to a std::string.  To not bother too
// much with string encodings we just use ascii.
std::string ObjectToString(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    v8::String::Utf8Value utf8_value(isolate, value);
    return std::string(*utf8_value);
}

v8::Intercepted CppMapGet(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    if (name->IsSymbol())
        return v8::Intercepted::kNo;

    v8::Isolate* isolate = gJsEnv->isolate;

    int  id      = name->GetIdentityHash();
    if (!gRegistered.contains(id))
    {
        std::string utf8Name = ObjectToString(isolate, name);
        auto        enttId   = entt::hashed_string(utf8Name.c_str());
        bool success = gJsEnv->RegisterFromMeta(enttId);
        if (success)
        {
            gRegistered[id] = true;
        }
        else
        {
            return v8::Intercepted::kNo;
        }
    }

    auto cpp = gJsEnv->cpp.Get(isolate);
    auto val = cpp->Get(gJsEnv->context.Get(isolate), name);
    if (val.IsEmpty())
    {
        return v8::Intercepted::kNo;
    }
    info.GetReturnValue().Set(val.ToLocalChecked());

    return v8::Intercepted::kYes;
}

v8::Local<v8::ObjectTemplate> JsEnv::CreateCppObjects()
{
    v8::Local<v8::ObjectTemplate> cpp = v8::ObjectTemplate::New(isolate);

    auto namedConfig = v8::NamedPropertyHandlerConfiguration(CppMapGet);
    cpp->SetHandler(namedConfig);

    this->cpp = v8::Global<v8::Object>(isolate, cpp);
    return cpp;
}

