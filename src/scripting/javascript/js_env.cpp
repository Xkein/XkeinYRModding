#include "js_env.h"
#include "core/raii_invoker.h"
#include <yr/debug_util.h>
#include <core/logger/logger.h>
#include <sstream>

YRSCRIPTING_API std::shared_ptr<JsEnv> gJsEnv;

GLOBAL_INVOKE_ON_CTOR([]() {
    gJsEnv = std::make_shared<JsEnv>();
})

using namespace PUERTS_NAMESPACE;

typedef void (JsEnv::*V8MethodCallback)(const v8::FunctionCallbackInfo<v8::Value>& Info);

template<V8MethodCallback callback>
struct MethodBindingHelper
{
    static void Bind(v8::Isolate* Isolate, v8::Local<v8::Context> Context, v8::Local<v8::Object> Obj, const char* Key, v8::Local<v8::External> This)
    {
        Obj->Set(Context, FV8Utils::V8String(Isolate, Key),
                 v8::FunctionTemplate::New(Isolate,
                     [](const v8::FunctionCallbackInfo<v8::Value>& Info) {
                        auto Self = static_cast<JsEnv*>((v8::Local<v8::External>::Cast(Info.Data()))->Value());
                        (Self->*callback)(Info);
                     },
                     This)
                     ->GetFunction(Context)
                     .ToLocalChecked())
            .Check();
    }
};


static v8::Local<v8::String> ToV8StringFromFileContent(v8::Isolate* Isolate, const std::vector<uint8_t>& FileContent)
{
    const auto* Buffer = FileContent.data();
    auto        Size   = FileContent.size();

    if (Size >= 2 && !(Size & 1) && ((Buffer[0] == 0xff && Buffer[1] == 0xfe) || (Buffer[0] == 0xfe && Buffer[1] == 0xff)))
    {
        std::string Content;
        gLogger->error("ToV8StringFromFileContent not implement!");
        //FFileHelper::BufferToString(Content, Buffer, Size);
        return FV8Utils::V8String(Isolate, Content.c_str());
    }
    else
    {
        if (Size >= 3 && Buffer[0] == 0xef && Buffer[1] == 0xbb && Buffer[2] == 0xbf)
        {
            // Skip over UTF-8 BOM if there is one
            Buffer += 3;
            Size -= 3;
        }
        return v8::String::NewFromUtf8(Isolate, (const char*)Buffer, v8::NewStringType::kNormal, Size).ToLocalChecked();
    }
}

namespace puerts
{
    void PLog(LogLevel Level, const std::string Fmt, ...) {
        auto& buffer = gJsEnv->StrBuffer;
        va_list argptr;
        va_start(argptr, Fmt);
        vsprintf_s(buffer.data(), buffer.size(), Fmt.c_str(), argptr);
        va_end(argptr);
        switch (Level)
        {
            case puerts::Log:
                gLogger->info(buffer.data());
                break;
            case puerts::Warning:
                gLogger->warn(buffer.data());
                break;
            case puerts::Error:
                gLogger->error(buffer.data());
                break;
        }
    }

} // namespace puerts

JsEnv::JsEnv()
{
    StrBuffer.resize(1024);

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
    DefaultContext.Reset(Isolate, Context);

    v8::Local<v8::Object> Global    = Context->Global();
    v8::Local<v8::Object> PuertsObj = v8::Object::New(Isolate);
    Global->Set(Context, FV8Utils::V8String(Isolate, "puerts"), PuertsObj).Check();
    
    auto This = v8::External::New(Isolate, this);

    MethodBindingHelper<&JsEnv::EvalScript>::Bind(Isolate, Context, Global, "__tgjsEvalScript", This);

    MethodBindingHelper<&JsEnv::Log>::Bind(Isolate, Context, Global, "__tgjsLog", This);

    MethodBindingHelper<&JsEnv::LoadCppType>::Bind(Isolate, Context, PuertsObj, "loadCPPType", This);



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
        auto               Context = DefaultContext.Get(Isolate);
        v8::Context::Scope ContextScope(Context);

        CppObjectMapper.UnInitialize(Isolate);

        BackendEnv.PathToModuleMap.clear();
        BackendEnv.ScriptIdToPathMap.clear();
    }

    DefaultContext.Reset();
    ResultInfo.Context.Reset();
    ResultInfo.Result.Reset();

    GuardExecute(
        [&]() {
        BackendEnv.UnInitialize();
    },
        [](std::string stackTrace) {
        gLogger->error(stackTrace);
    });
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
    v8::Local<v8::Context> Context = DefaultContext.Get(Isolate);
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

void JsEnv::ExecuteModule(const char* ModuleName)
{

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
    BackendEnv.CreateInspector(MainIsolate, &DefaultContext, Port);
}

void JsEnv::DestroyInspector()
{
    BackendEnv.DestroyInspector(MainIsolate, &DefaultContext);
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
    v8::Local<v8::Context> Context = DefaultContext.Get(MainIsolate);
    v8::Context::Scope     ContextScope(Context);

    return BackendEnv.ClearModuleCache(MainIsolate, Context, Path);
}

void JsEnv::InitExtensionMethodsMap() {}

void JsEnv::JsHotReload(const char* ModuleName, const char* JsSource) {}

void JsEnv::ReloadModule(const char* ModuleName, const char* JsSource) {}

void JsEnv::ReloadSource(const char* Path, const std::string& JsSource) {}

void JsEnv::OnSourceLoaded(std::function<void(const char*)> Callback) {}

std::string JsEnv::GetJSStackTrace()
{
    return BackendEnv.GetJSStackTrace();
}

// Convert a JavaScript string to a std::string.  To not bother too
// much with string encodings we just use ascii.
std::string JsEnv::ObjectToString(v8::Local<v8::Value> value)
{
    v8::String::Utf8Value utf8_value(MainIsolate, value);
    return std::string(*utf8_value);
}

std::string JsEnv::ObjectToString(const v8::PersistentBase<v8::Value>& value)
{
    v8::Isolate::Scope     IsolateScope(MainIsolate);
    v8::HandleScope        HandleScope(MainIsolate);
    v8::Local<v8::Context> Context = DefaultContext.Get(MainIsolate);
    v8::Context::Scope     ContextScope(Context);
    
    return ObjectToString(value.Get(MainIsolate));
}

std::string JsEnv::TryCatchToString(v8::Isolate* Isolate, v8::TryCatch* TryCatch)
{
    return FV8Utils::ExceptionToString(Isolate, TryCatch->Exception());
}

bool JsEnv::LoadFile(const char* RequiringDir, const char* ModuleName, std::string& OutPath, std::string& OutDebugPath, std::vector<uint8_t>& Data, std::string& ErrInfo)
{
    return false;
}

void JsEnv::EvalScript(const v8::FunctionCallbackInfo<v8::Value>& Info) {}

void JsEnv::Log(const v8::FunctionCallbackInfo<v8::Value>& Info)
{
    v8::Isolate*           Isolate = Info.GetIsolate();
    v8::Isolate::Scope     IsolateScope(Isolate);
    v8::HandleScope        HandleScope(Isolate);
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    v8::Context::Scope     ContextScope(Context);

    auto Level = Info[0]->Int32Value(Context).ToChecked();

    std::string Msg = ObjectToString(Info[1]);
    switch (Level)
    {
        case 1:
            gLogger->info(Msg);
            break;
        case 2:
            gLogger->warn(Msg);
            break;
        case 3:
            gLogger->error(Msg);
            break;
        default:
            gLogger->info(Msg);
            break;
    }
}

void JsEnv::SearchModule(const v8::FunctionCallbackInfo<v8::Value>& Info) {}

void JsEnv::LoadModule(const v8::FunctionCallbackInfo<v8::Value>& Info)
{
    v8::Isolate*           Isolate = Info.GetIsolate();
    v8::Isolate::Scope     IsolateScope(Isolate);
    v8::HandleScope        HandleScope(Isolate);
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    v8::Context::Scope     ContextScope(Context);

    std::string   Path = ObjectToString(Info[0]);
    std::vector<uint8_t> Data;
    if (!ModuleLoader->Load(Path.c_str(), Data))
    {
        FV8Utils::ThrowException(Isolate, "can not load module");
        return;
    }

    Info.GetReturnValue().Set(ToV8StringFromFileContent(Isolate, Data));
}

void JsEnv::LoadCppType(const v8::FunctionCallbackInfo<v8::Value>& Info)
{
    CppObjectMapper.LoadCppType(Info);
}
