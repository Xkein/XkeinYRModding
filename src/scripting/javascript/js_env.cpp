#include "js_env.h"
#include "core/raii_invoker.h"

#include <core/logger/logger.h>
#include <sstream>

YRSCRIPTING_API std::shared_ptr<JsEnv> gJsEnv;

GLOBAL_INVOKE_ON_CTOR([]() {
    gJsEnv = std::make_shared<JsEnv>();
})

using namespace PUERTS_NAMESPACE;

JsEnv::JsEnv()
{
    FBackendEnv::GlobalPrepare();
    BackendEnv.Initialize(nullptr, nullptr);
    MainIsolate = BackendEnv.MainIsolate;

    auto Isolate = MainIsolate;
#ifdef MULT_BACKENDS
    ResultInfo.PuertsPlugin = InPuertsPlugin;
#endif
    ResultInfo.Isolate = Isolate;
    Isolate->SetData(0, this);
    Isolate->SetData(1, &BackendEnv);

    v8::Isolate::Scope Isolatescope(Isolate);
    v8::HandleScope    HandleScope(Isolate);

    v8::Local<v8::Context> Context = BackendEnv.MainContext.Get(Isolate);
    v8::Context::Scope     ContextScope(Context);
    ResultInfo.Context.Reset(Isolate, Context);
    v8::Local<v8::Object> Global = Context->Global();

    CppObjectMapper.Initialize(Isolate, Context);
    Isolate->SetData(MAPPER_ISOLATE_DATA_POS, static_cast<PUERTS_NAMESPACE::ICppObjectMapper*>(&CppObjectMapper));


    BackendEnv.StartPolling();

    gLogger->info("JsEnv started.");
}

JsEnv::~JsEnv()
{
    LogicTick();
    BackendEnv.StopPolling();
    DestroyInspector();

    BackendEnv.JsPromiseRejectCallback.Reset();
    LastException.Reset();

    {
        auto Isolate = MainIsolate;
#ifdef THREAD_SAFE
        v8::Locker Locker(Isolate);
#endif
        v8::Isolate::Scope IsolateScope(Isolate);
        v8::HandleScope    HandleScope(Isolate);
        auto               Context = ResultInfo.Context.Get(Isolate);
        v8::Context::Scope ContextScope(Context);

        CppObjectMapper.UnInitialize(Isolate);

        BackendEnv.PathToModuleMap.clear();
        BackendEnv.ScriptIdToPathMap.clear();
    }

    ResultInfo.Context.Reset();
    ResultInfo.Result.Reset();

    BackendEnv.UnInitialize();
    gLogger->info("JsEnv disposed.");
}

bool JsEnv::Eval(const char* Code, const char* Path)
{
    v8::Isolate* Isolate = MainIsolate;
#ifdef THREAD_SAFE
    v8::Locker Locker(Isolate);
#endif
    v8::Isolate::Scope     IsolateScope(Isolate);
    v8::HandleScope        HandleScope(Isolate);
    v8::Local<v8::Context> Context = ResultInfo.Context.Get(Isolate);
    v8::Context::Scope     ContextScope(Context);

    v8::Local<v8::String> Url    = FV8Utils::V8String(Isolate, Path == nullptr ? "" : Path);
    v8::Local<v8::String> Source = FV8Utils::V8String(Isolate, Code);
#if defined(V8_94_OR_NEWER) && !defined(WITH_QUICKJS)
    v8::ScriptOrigin Origin(Isolate, Url);
#else
    v8::ScriptOrigin Origin(Url);
#endif
    v8::TryCatch TryCatch(Isolate);

    auto CompiledScript = v8::Script::Compile(Context, Source, &Origin);
    if (CompiledScript.IsEmpty())
    {
        SetLastException(TryCatch.Exception());
        return false;
    }
    auto maybeValue = CompiledScript.ToLocalChecked()->Run(Context); // error info output
    if (TryCatch.HasCaught())
    {
        SetLastException(TryCatch.Exception());
        return false;
    }

    if (!maybeValue.IsEmpty())
    {
        ResultInfo.Result.Reset(Isolate, maybeValue.ToLocalChecked());
    }

    return true;
}

void JsEnv::SetLastException(v8::Local<v8::Value> Exception)
{
    LastException.Reset(MainIsolate, Exception);
    LastExceptionInfo = FV8Utils::ExceptionToString(MainIsolate, Exception);
}

void JsEnv::LowMemoryNotification()
{
    MainIsolate->LowMemoryNotification();
}

bool JsEnv::IdleNotificationDeadline(double DeadlineInSeconds)
{
#ifndef WITH_QUICKJS
    return MainIsolate->IdleNotificationDeadline(DeadlineInSeconds);
#else
    return true;
#endif
}

void JsEnv::RequestMinorGarbageCollectionForTesting()
{
#ifndef WITH_QUICKJS
    MainIsolate->RequestGarbageCollectionForTesting(v8::Isolate::kMinorGarbageCollection);
#endif
}

void JsEnv::RequestFullGarbageCollectionForTesting()
{
#ifndef WITH_QUICKJS
    MainIsolate->RequestGarbageCollectionForTesting(v8::Isolate::kFullGarbageCollection);
#endif
}

void JsEnv::CreateInspector(int32_t Port)
{
    BackendEnv.CreateInspector(MainIsolate, &ResultInfo.Context, Port);
}

void JsEnv::DestroyInspector()
{
    BackendEnv.DestroyInspector(MainIsolate, &ResultInfo.Context);
}

void JsEnv::LogicTick()
{
    BackendEnv.LogicTick();
}

bool JsEnv::InspectorTick()
{
    return BackendEnv.InspectorTick() ? 1 : 0;
}

bool JsEnv::ClearModuleCache(const char* Path)
{
    v8::Isolate::Scope     IsolateScope(MainIsolate);
    v8::HandleScope        HandleScope(MainIsolate);
    v8::Local<v8::Context> Context = ResultInfo.Context.Get(MainIsolate);
    v8::Context::Scope     ContextScope(Context);

    return BackendEnv.ClearModuleCache(MainIsolate, Context, Path);
}

std::string JsEnv::GetJSStackTrace()
{
    return BackendEnv.GetJSStackTrace();
}
