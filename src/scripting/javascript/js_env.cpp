#include "js_env.h"
#include <BackendEnv.h>
#include <V8Utils.h>
#include "core/raii_invoker.h"
#include <yr/debug_util.h>
#include <core/logger/logger.h>
#include <core/string/string_tool.h>
#include <core/platform/path.h>
#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include <filesystem>
#include <core/assertion_macro.h>

#define CHECK_V8_ARGS(...)

YRSCRIPTING_API std::shared_ptr<JsEnv> gJsEnv;

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


static v8::Local<v8::String> ToV8StringFromFileContent(v8::Isolate* Isolate, const std::vector<uint8>& FileContent)
{
    const auto* Buffer = FileContent.data();
    auto        Size   = FileContent.size();

    if (Size >= 2 && !(Size & 1) && ((Buffer[0] == 0xff && Buffer[1] == 0xfe) || (Buffer[0] == 0xfe && Buffer[1] == 0xff)))
    {
        std::string Content;
        buffer_to_string(Content, Buffer, Size);
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

JsEnv::JsEnv() : ExtensionMethodsMapInited(false)
{
    StrBuffer.resize(1024);

    ModuleLoader = std::make_shared<DefaultJSModuleLoader>("assets/JavaScript");
    BackendEnv   = std::make_unique<PUERTS_NAMESPACE::FBackendEnv>();

    FBackendEnv::GlobalPrepare();
    BackendEnv->Initialize(nullptr, nullptr);
    MainIsolate = BackendEnv->MainIsolate;

    auto Isolate = MainIsolate;
#ifdef MULT_BACKENDS
    ResultInfo.PuertsPlugin = InPuertsPlugin;
#endif
    ResultInfo.Isolate = Isolate;
    Isolate->SetData(0, this);
    Isolate->SetData(1, BackendEnv.get());

    v8::Isolate::Scope Isolatescope(Isolate);
    v8::HandleScope    HandleScope(Isolate);

    v8::Local<v8::Context> Context = BackendEnv->MainContext.Get(Isolate);
    v8::Context::Scope     ContextScope(Context);
    DefaultContext.Reset(Isolate, Context);

    v8::Local<v8::Object> Global    = Context->Global();
    v8::Local<v8::Object> PuertsObj = v8::Object::New(Isolate);
    Global->Set(Context, FV8Utils::V8String(Isolate, "puerts"), PuertsObj).Check();
    
    auto This = v8::External::New(Isolate, this);

    MethodBindingHelper<&JsEnv::EvalScript>::Bind(Isolate, Context, Global, "__tgjsEvalScript", This);

    MethodBindingHelper<&JsEnv::SearchModule>::Bind(Isolate, Context, Global, "__tgjsSearchModule", This);

    MethodBindingHelper<&JsEnv::LoadModule>::Bind(Isolate, Context, Global, "__tgjsLoadModule", This);

    MethodBindingHelper<&JsEnv::FindModule>::Bind(Isolate, Context, Global, "__tgjsFindModule", This);

    MethodBindingHelper<&JsEnv::Log>::Bind(Isolate, Context, Global, "__tgjsLog", This);

    MethodBindingHelper<&JsEnv::LoadCppType>::Bind(Isolate, Context, PuertsObj, "loadCPPType", This);

    ExecuteModule("setup.js");
    ExecuteModule("log.js");
    ExecuteModule("modular.js");
    ExecuteModule("yrlazyload.js");
    ExecuteModule("hot_reload.js");
    ExecuteModule("main.js");

    Require.Reset(Isolate, PuertsObj->Get(Context, FV8Utils::V8String(Isolate, "__require")).ToLocalChecked().As<v8::Function>());

    GetESMMain.Reset(Isolate, PuertsObj->Get(Context, FV8Utils::V8String(Isolate, "getESMMain")).ToLocalChecked().As<v8::Function>());

    ReloadJs.Reset(Isolate, PuertsObj->Get(Context, FV8Utils::V8String(Isolate, "__reload")).ToLocalChecked().As<v8::Function>());

    CppObjectMapper.Initialize(Isolate, Context);
    Isolate->SetData(MAPPER_ISOLATE_DATA_POS, static_cast<PUERTS_NAMESPACE::ICppObjectMapper*>(&CppObjectMapper));

    BackendEnv->StartPolling();

    gLogger->info("JsEnv started.");
}

JsEnv::~JsEnv()
{
    LogicTick();
    BackendEnv->StopPolling();
    DestroyInspector();

    BackendEnv->JsPromiseRejectCallback.Reset();
    LastException.Reset();
    Require.Reset();
    GetESMMain.Reset();
    ReloadJs.Reset();
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

        BackendEnv->PathToModuleMap.clear();
        BackendEnv->ScriptIdToPathMap.clear();
    }

    DefaultContext.Reset();
    ResultInfo.Context.Reset();
    ResultInfo.Result.Reset();

    GuardExecute(
        [&]() {
        BackendEnv->UnInitialize();
    },
        [](std::string stackTrace) {
        gLogger->error(stackTrace);
    });
    gLogger->info("JsEnv disposed.");
}

bool JsEnv::Eval(const char* Code, const char* Path, v8::Global<v8::Value>* result)
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
        if (result)
            result->Reset(Isolate, maybeValue.ToLocalChecked());
        ResultInfo.Result.Reset(Isolate, maybeValue.ToLocalChecked());
    }

    return true;
}

//void JsEnv::Execute(const char* ModuleNameOrScript, const std::vector<std::pair<std::string, v8::Local<v8::Value>>>& Arguments, bool IsScript)
//{
//#ifdef SINGLE_THREAD_VERIFY
//    ensureMsgf(BoundThreadId == FPlatformTLS::GetCurrentThreadId(), TEXT("Access by illegal thread!"));
//#endif
//
//    auto Isolate = MainIsolate;
//#ifdef THREAD_SAFE
//    v8::Locker Locker(Isolate);
//#endif
//    v8::Isolate::Scope IsolateScope(Isolate);
//    v8::HandleScope    HandleScope(Isolate);
//    auto               Context = v8::Local<v8::Context>::New(Isolate, DefaultContext);
//    v8::Context::Scope ContextScope(Context);
//
//    auto MaybeTGameTGJS = Context->Global()->Get(Context, FV8Utils::V8String(Isolate, "puerts"));
//
//    if (MaybeTGameTGJS.IsEmpty() || !MaybeTGameTGJS.ToLocalChecked()->IsObject())
//    {
//        gLogger->error("global.puerts not found!");
//        return;
//    }
//
//    auto TGJS = MaybeTGameTGJS.ToLocalChecked()->ToObject(Context).ToLocalChecked();
//
//    auto MaybeArgv = TGJS->Get(Context, FV8Utils::V8String(Isolate, "argv"));
//
//    if (MaybeArgv.IsEmpty() || !MaybeArgv.ToLocalChecked()->IsObject())
//    {
//        gLogger->error("global.puerts.argv not found!");
//        return;
//    }
//
//    auto Argv = MaybeArgv.ToLocalChecked()->ToObject(Context).ToLocalChecked();
//
//    auto MaybeArgvAdd = Argv->Get(Context, FV8Utils::V8String(Isolate, "add"));
//
//    if (MaybeArgvAdd.IsEmpty() || !MaybeArgvAdd.ToLocalChecked()->IsFunction())
//    {
//        gLogger->error("global.puerts.argv.add not found!");
//        return;
//    }
//
//    auto ArgvAdd = MaybeArgvAdd.ToLocalChecked().As<v8::Function>();
//
//    for (int i = 0; i < Arguments.size(); i++)
//    {
//        auto                 Object  = Arguments[i].second;
//        v8::Local<v8::Value> Args[2] = {FV8Utils::V8String(Isolate, Arguments[i].first.c_str()), Object};
//        (void)(ArgvAdd->Call(Context, Argv, 2, Args));
//    }
//
//    if (IsScript)
//    {
//#if V8_MAJOR_VERSION > 8
//        v8::ScriptOrigin Origin(Isolate, FV8Utils::V8String(Isolate, "chunk"));
//#else
//        v8::ScriptOrigin Origin(FV8Utils::V8String(Isolate, "chunk"));
//#endif
//        v8::Local<v8::String> Source = FV8Utils::V8String(Isolate, ModuleNameOrScript);
//        v8::TryCatch          TryCatch(Isolate);
//
//        auto CompiledScript = v8::Script::Compile(Context, Source, &Origin);
//        if (CompiledScript.IsEmpty())
//        {
//            gLogger->error(TryCatchToString(Isolate, &TryCatch));
//            return;
//        }
//        (void)(CompiledScript.ToLocalChecked()->Run(Context));
//        if (TryCatch.HasCaught())
//        {
//            gLogger->error(TryCatchToString(Isolate, &TryCatch));
//        }
//    }
//    else
//    {
//        v8::TryCatch         TryCatch(Isolate);
//        v8::Local<v8::Value> Args[] = {FV8Utils::V8String(Isolate, ModuleNameOrScript)};
//        Require.Get(Isolate)->Call(Context, v8::Undefined(Isolate), 1, Args);
//        if (TryCatch.HasCaught())
//        {
//            gLogger->error(TryCatchToString(Isolate, &TryCatch));
//        }
//    }
//}

void JsEnv::ExecuteModule(const char* ModuleName)
{
    std::string          OutPath;
    std::string          DebugPath;
    std::vector<uint8> Data;

    std::string ErrInfo;
    if (!LoadFile("", ModuleName, OutPath, DebugPath, Data, ErrInfo))
    {
        gLogger->error(ErrInfo);
        return;
    }

    // #if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
    //     if (!DebugPath.IsEmpty())
    //         OutPath = DebugPath;
    // #endif

    auto               Isolate = MainIsolate;
    v8::Isolate::Scope IsolateScope(Isolate);
    v8::HandleScope    HandleScope(Isolate);
    auto               Context = v8::Local<v8::Context>::New(Isolate, DefaultContext);
    v8::Context::Scope ContextScope(Context);
#ifndef WITH_QUICKJS
    if (OutPath.ends_with(".mjs"))
    {
        v8::TryCatch          TryCatch(Isolate);
        v8::Local<v8::Module> RootModule;

        if (!FetchESModuleTree(Context, OutPath.c_str()).ToLocal(&RootModule))
        {
            assert(TryCatch.HasCaught());
            gLogger->error(TryCatchToString(Isolate, &TryCatch));
            return;
        }

        if (RootModule->InstantiateModule(Context, ResolveModuleCallback).FromMaybe(false))
        {
            RootModule->Evaluate(Context);
        }

        if (TryCatch.HasCaught())
        {
            gLogger->error(TryCatchToString(Isolate, &TryCatch));
            return;
        }
    }
    else
#endif
    {
        v8::Local<v8::String> Source = ToV8StringFromFileContent(Isolate, Data);

#if PLATFORM_WINDOWS
        // 修改URL分隔符格式，否则无法匹配Inspector协议在打断点时发送的正则表达式，导致断点失败
        std::string FormattedScriptUrl = DebugPath;
        boost::replace_all(FormattedScriptUrl, "/", "\\");
#else
        std::string FormattedScriptUrl = DebugPath;
#endif
        v8::Local<v8::String> Name = FV8Utils::V8String(Isolate, FormattedScriptUrl.c_str());
#if V8_MAJOR_VERSION > 8
        v8::ScriptOrigin Origin(Isolate, Name);
#else
        v8::ScriptOrigin Origin(Name);
#endif
        v8::TryCatch TryCatch(Isolate);

        auto CompiledScript = v8::Script::Compile(Context, Source, &Origin);
        if (CompiledScript.IsEmpty())
        {
            gLogger->error(TryCatchToString(Isolate, &TryCatch));
            return;
        }
        (void)(CompiledScript.ToLocalChecked()->Run(Context));
        if (TryCatch.HasCaught())
        {
            gLogger->error(TryCatchToString(Isolate, &TryCatch));
            return;
        }
    }
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
    BackendEnv->CreateInspector(MainIsolate, &DefaultContext, Port);
}

void JsEnv::DestroyInspector()
{
    BackendEnv->DestroyInspector(MainIsolate, &DefaultContext);
}

void JsEnv::LogicTick()
{
    BackendEnv->LogicTick();
}

bool JsEnv::InspectorTick()
{
    return BackendEnv->InspectorTick() ? 1 : 0;
}

bool JsEnv::ClearModuleCache(const char* Path)
{
    v8::Isolate::Scope     IsolateScope(MainIsolate);
    v8::HandleScope        HandleScope(MainIsolate);
    v8::Local<v8::Context> Context = DefaultContext.Get(MainIsolate);
    v8::Context::Scope     ContextScope(Context);

    return BackendEnv->ClearModuleCache(MainIsolate, Context, Path);
}

void JsEnv::InitExtensionMethodsMap()
{

    ExtensionMethodsMapInited = true;
}

void JsEnv::JsHotReload(const char* ModuleName, const char* JsSource)
{
#ifdef SINGLE_THREAD_VERIFY
    ensureMsgf(BoundThreadId == FPlatformTLS::GetCurrentThreadId(), TEXT("Access by illegal thread!"));
#endif
    auto               Isolate = MainIsolate;
    v8::Isolate::Scope IsolateScope(Isolate);
    v8::HandleScope    HandleScope(Isolate);
    auto               Context = DefaultContext.Get(Isolate);
    v8::Context::Scope ContextScope(Context);
    auto               LocalReloadJs = ReloadJs.Get(Isolate);

    std::string OutPath, OutDebugPath;
    if (ModuleLoader->Search("", ModuleName, OutPath, OutDebugPath))
    {
        OutPath = Paths::Absolute(OutPath);
        gLogger->info("reload js module [{}]", OutPath);
        v8::TryCatch          TryCatch(Isolate);
        v8::Handle<v8::Value> Args[] = {FV8Utils::V8String(Isolate, ModuleName), FV8Utils::V8String(Isolate, OutPath.c_str()), FV8Utils::V8String(Isolate, JsSource)};

        (void)(LocalReloadJs->Call(Context, v8::Undefined(Isolate), 3, Args));

        if (TryCatch.HasCaught())
        {
            gLogger->error("reload module exception {}", TryCatchToString(Isolate, &TryCatch));
        }
    }
    else
    {
        gLogger->warn("not find js module [{}]", ModuleName);
        return;
    }
}

void JsEnv::ReloadModule(const char* ModuleName, const char* JsSource)
{
#ifdef SINGLE_THREAD_VERIFY
    ensureMsgf(BoundThreadId == FPlatformTLS::GetCurrentThreadId(), TEXT("Access by illegal thread!"));
#endif
#ifdef THREAD_SAFE
    v8::Locker Locker(MainIsolate);
#endif
    // Logger->Info(FString::Printf(TEXT("start reload js module [%s]"), *ModuleName.ToString()));
    JsHotReload(ModuleName, JsSource);
}

void JsEnv::ReloadSource(const char* Path, const std::string& JsSource)
{
#ifdef SINGLE_THREAD_VERIFY
    ensureMsgf(BoundThreadId == FPlatformTLS::GetCurrentThreadId(), TEXT("Access by illegal thread!"));
#endif
#ifdef THREAD_SAFE
    v8::Locker Locker(MainIsolate);
#endif
    auto               Isolate = MainIsolate;
    v8::Isolate::Scope IsolateScope(Isolate);
    v8::HandleScope    HandleScope(Isolate);
    auto               Context = DefaultContext.Get(Isolate);
    v8::Context::Scope ContextScope(Context);
    auto               LocalReloadJs = ReloadJs.Get(Isolate);

    gLogger->info("reload js [%s]", Path);
    v8::TryCatch          TryCatch(Isolate);
    v8::Handle<v8::Value> Args[] = {v8::Undefined(Isolate), FV8Utils::V8String(Isolate, Path), FV8Utils::V8String(Isolate, JsSource.c_str())};

    (void)(LocalReloadJs->Call(Context, v8::Undefined(Isolate), 3, Args));

    if (TryCatch.HasCaught())
    {
        gLogger->error("reload module exception %s", TryCatchToString(Isolate, &TryCatch));
    }
}

void JsEnv::OnSourceLoaded(std::function<void(const char*)> Callback)
{
    OnSourceLoadedCallback = Callback;
}

std::string JsEnv::GetJSStackTrace()
{
    return BackendEnv->GetJSStackTrace();
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

v8::Local<v8::String> JsEnv::ToV8String(v8::Isolate* Isolate, const char* String)
{
    return FV8Utils::V8String(Isolate, String);
}

bool JsEnv::LoadFile(const char* RequiringDir, const char* ModuleName, std::string& OutPath, std::string& OutDebugPath, std::vector<uint8>& Data, std::string& ErrInfo)
{
    if (ModuleLoader->Search(RequiringDir, ModuleName, OutPath, OutDebugPath))
    {
        if (!ModuleLoader->Load(OutPath.c_str(), Data))
        {
            ErrInfo = std::format("can not load [{}]", ModuleName);
            return false;
        }
    }
    else
    {
        ErrInfo = std::format("can not find [{}]", ModuleName);
        return false;
    }
    return true;
}

void JsEnv::EvalScript(const v8::FunctionCallbackInfo<v8::Value>& Info)
{
    v8::Isolate*           Isolate = Info.GetIsolate();
    v8::Isolate::Scope     IsolateScope(Isolate);
    v8::HandleScope        HandleScope(Isolate);
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    v8::Context::Scope     ContextScope(Context);

    CHECK_V8_ARGS(EArgString, EArgString);

    v8::Local<v8::String> Source = Info[0]->ToString(Context).ToLocalChecked();

#ifndef WITH_QUICKJS
    bool IsESM = Info[2]->BooleanValue(Isolate);

    if (IsESM)
    {
        std::string           FullPath = ObjectToString(Info[3]);
        v8::Local<v8::Module> RootModule;

        if (!FetchESModuleTree(Context, FullPath.c_str()).ToLocal(&RootModule))
        {
            return;
        }

        if (RootModule->InstantiateModule(Context, ResolveModuleCallback).FromMaybe(false))
        {
            auto                 MaybeResult = RootModule->Evaluate(Context);
            v8::Local<v8::Value> Result;
            if (MaybeResult.ToLocal(&Result))
            {
                if (Result->IsPromise())
                {
                    v8::Local<v8::Promise> ResultPromise(Result.As<v8::Promise>());
                    while (ResultPromise->State() == v8::Promise::kPending)
                    {
                        Isolate->PerformMicrotaskCheckpoint();
                    }

                    if (ResultPromise->State() == v8::Promise::kRejected)
                    {
                        ResultPromise->MarkAsHandled();
                        Isolate->ThrowException(ResultPromise->Result());
                        return;
                    }
                }
                Info.GetReturnValue().Set(RootModule->GetModuleNamespace());
            }
        }

        return;
    }
#endif

    v8::String::Utf8Value UrlArg(Isolate, Info[1]);
    std::string           ScriptUrl = *UrlArg;
#if PLATFORM_WINDOWS
    // 修改URL分隔符格式，否则无法匹配Inspector协议在打断点时发送的正则表达式，导致断点失败
    std::string FormattedScriptUrl = ScriptUrl;
    boost::replace_all(FormattedScriptUrl, "/", "\\");
#else
    FString FormattedScriptUrl = ScriptUrl;
#endif
    v8::Local<v8::String> Name = FV8Utils::V8String(Isolate, FormattedScriptUrl.c_str());
#if V8_MAJOR_VERSION > 8
    v8::ScriptOrigin Origin(Isolate, Name);
#else
    v8::ScriptOrigin Origin(Name);
#endif
    auto Script = v8::Script::Compile(Context, Source, &Origin);
    if (Script.IsEmpty())
    {
        return;
    }
    auto Result = Script.ToLocalChecked()->Run(Context);
    if (Result.IsEmpty())
    {
        return;
    }
    Info.GetReturnValue().Set(Result.ToLocalChecked());

    if (OnSourceLoadedCallback)
    {
        OnSourceLoadedCallback(FormattedScriptUrl.c_str());
    }
}

void JsEnv::Log(const v8::FunctionCallbackInfo<v8::Value>& Info)
{
    v8::Isolate*           Isolate = Info.GetIsolate();
    v8::Isolate::Scope     IsolateScope(Isolate);
    v8::HandleScope        HandleScope(Isolate);
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    v8::Context::Scope     ContextScope(Context);

    CHECK_V8_ARGS(EArgInt32, EArgString);

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

void JsEnv::SearchModule(const v8::FunctionCallbackInfo<v8::Value>& Info)
{
    v8::Isolate*           Isolate = Info.GetIsolate();
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();

    CHECK_V8_ARGS(EArgString, EArgString);

    std::string ModuleName   = ObjectToString(Info[0]);
    std::string RequiringDir = ObjectToString(Info[1]);
    std::string OutPath;
    std::string OutDebugPath;
    if (ModuleLoader->Search(RequiringDir, ModuleName, OutPath, OutDebugPath))
    {
        auto Result = v8::Array::New(Isolate);
        Result->Set(Context, 0, FV8Utils::V8String(Isolate, OutPath.c_str())).Check();
        Result->Set(Context, 1, FV8Utils::V8String(Isolate, OutDebugPath.c_str())).Check();
        Info.GetReturnValue().Set(Result);
    }
}

void JsEnv::LoadModule(const v8::FunctionCallbackInfo<v8::Value>& Info)
{
    v8::Isolate*           Isolate = Info.GetIsolate();
    v8::Isolate::Scope     IsolateScope(Isolate);
    v8::HandleScope        HandleScope(Isolate);
    v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    v8::Context::Scope     ContextScope(Context);

    CHECK_V8_ARGS(EArgString);

    std::string   Path = ObjectToString(Info[0]);
    std::vector<uint8> Data;
    if (!ModuleLoader->Load(Path.c_str(), Data))
    {
        FV8Utils::ThrowException(Isolate, "can not load module");
        return;
    }

    Info.GetReturnValue().Set(ToV8StringFromFileContent(Isolate, Data));
}

void JsEnv::FindModule(const v8::FunctionCallbackInfo<v8::Value>& Info)
{
    //v8::Isolate*           Isolate = Info.GetIsolate();
    //v8::Isolate::Scope     Isolatescope(Isolate);
    //v8::HandleScope        HandleScope(Isolate);
    //v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
    //v8::Context::Scope     ContextScope(Context);

    //CHECK_V8_ARGS(EArgString);

    //std::string Name = *(v8::String::Utf8Value(Isolate, Info[0]));

    //auto Func = FindAddonRegisterFunc(Name);

    //if (Func)
    //{
    //    auto Exports = v8::Object::New(Isolate);
    //    Func(Context, Exports);
    //    Info.GetReturnValue().Set(Exports);
    //}
}

void JsEnv::LoadCppType(const v8::FunctionCallbackInfo<v8::Value>& Info)
{
    CppObjectMapper.LoadCppType(Info);
}

v8::MaybeLocal<v8::Module> JsEnv::FetchESModuleTree(v8::Local<v8::Context> Context, const char* FileName)
{
    const auto Isolate = Context->GetIsolate();
    if (PathToModule.contains(FileName))
    {
        return PathToModule[FileName].Get(Isolate);
    }

    gLogger->info("Fetch ES Module: {}", FileName);
    std::vector<uint8> Data;
    if (!ModuleLoader->Load(FileName, Data))
    {
        FV8Utils::ThrowException(MainIsolate, std::format("can not load [{}]", FileName).c_str());
        return v8::MaybeLocal<v8::Module>();
    }

    std::string Script;
    buffer_to_string(Script, Data.data(), Data.size());

    v8::ScriptOrigin Origin(Isolate, FV8Utils::V8String(Isolate, FileName), 0, 0, false, -1, v8::Local<v8::Value>(), false, false, true);
    v8::ScriptCompiler::Source Source(FV8Utils::V8String(Isolate, Script.c_str()), Origin);

    v8::Local<v8::Module> Module;
    if (!v8::ScriptCompiler::CompileModule(Isolate, &Source).ToLocal(&Module))
    {
        return v8::MaybeLocal<v8::Module>();
    }

    PathToModule[FileName] = v8::Global<v8::Module>(Isolate, Module);
    FModuleInfo* Info = new FModuleInfo;
    Info->Module.Reset(Isolate, Module);
    HashToModuleInfo.emplace(Module->GetIdentityHash(), Info);

    auto DirName = Paths::GetPath(FileName);

    for (int i = 0, Length = Module->GetModuleRequestsLength(); i < Length; ++i)
    {
        auto RefModuleName = ObjectToString(Module->GetModuleRequest(i));

        std::string OutPath;
        std::string OutDebugPath;
        if (ModuleLoader->Search(DirName.c_str(), RefModuleName.c_str(), OutPath, OutDebugPath))
        {
            if (OutPath.ends_with("package.json"))
            {
                std::vector<uint8> PackageData;
                if (ModuleLoader->Load(OutPath.c_str(), PackageData))
                {
                    std::string PackageScript;
                    buffer_to_string(PackageScript, PackageData.data(), PackageData.size());
                    v8::Local<v8::Value> Args[] = {FV8Utils::V8String(Isolate, PackageScript.c_str())};

                    auto MaybeRet = GetESMMain.Get(Isolate)->Call(Context, v8::Undefined(Isolate), 1, Args);

                    v8::Local<v8::Value> ESMMainValue;
                    if (MaybeRet.ToLocal(&ESMMainValue) && ESMMainValue->IsString())
                    {
                        std::string ESMMain = ObjectToString(ESMMainValue);
                        std::string ESMMainOutPath;
                        std::string ESMMainOutDebugPath;
                        if (ModuleLoader->Search(Paths::GetPath(OutPath).c_str(), ESMMain.c_str(), ESMMainOutPath, ESMMainOutDebugPath))
                        {
                            OutPath = ESMMainOutPath;
                        }
                    }
                }
            }
            if (OutPath.ends_with(".mjs") || OutPath.ends_with(".js"))
            {
                auto RefModule = FetchESModuleTree(Context, OutPath.c_str());
                if (RefModule.IsEmpty())
                {
                    return v8::MaybeLocal<v8::Module>();
                }
                Info->ResolveCache[RefModuleName] = v8::Global<v8::Module>(Isolate, RefModule.ToLocalChecked());
                continue;
            }
        }

        auto RefModule = FetchCJSModuleAsESModule(Context, (OutPath.ends_with(".cjs") ? OutPath : RefModuleName).c_str());

        if (RefModule.IsEmpty())
        {
            FV8Utils::ThrowException(MainIsolate, std::format("can not resolve [{}], import by [{}]", RefModuleName, FileName).c_str());
            return v8::MaybeLocal<v8::Module>();
        }

        Info->ResolveCache[RefModuleName] = v8::Global<v8::Module>(Isolate, RefModule.ToLocalChecked());
    }

    return Module;
}

v8::MaybeLocal<v8::Module> JsEnv::FetchCJSModuleAsESModule(v8::Local<v8::Context> Context, const char* ModuleName)
{
#if V8_MAJOR_VERSION < 8
    FV8Utils::ThrowException(MainIsolate, FString::Printf(TEXT("V8_MAJOR_VERSION < 8 not support fetch CJS module [%s] from ESM"), *ModuleName));
    return v8::MaybeLocal<v8::Module>();
#else
    const auto Isolate = Context->GetIsolate();

    gLogger->info("ESM Fetch CJS Module: %s", ModuleName);

    v8::Local<v8::Value> Args[] = {FV8Utils::V8String(Isolate, ModuleName)};

    auto MaybeRet = Require.Get(Isolate)->Call(Context, v8::Undefined(Isolate), 1, Args);

    if (MaybeRet.IsEmpty())
    {
        return v8::MaybeLocal<v8::Module>();
    }

    auto                               CJSValue    = MaybeRet.ToLocalChecked();
    std::vector<v8::Local<v8::String>> ExportNames = {v8::String::NewFromUtf8(Isolate, "default", v8::NewStringType::kNormal).ToLocalChecked()};

    if (CJSValue->IsObject())
    {
        auto JsObject = CJSValue->ToObject(Context).ToLocalChecked();
        auto Keys     = JsObject->GetOwnPropertyNames(Context).ToLocalChecked();
        for (decltype(Keys->Length()) i = 0; i < Keys->Length(); ++i)
        {
            v8::Local<v8::Value> Key;
            if (Keys->Get(Context, i).ToLocal(&Key))
            {
                // UE_LOG(LogTemp, Warning, TEXT("---'%s' '%s'"), *ModuleName, *FV8Utils::ToFString(Isolate, Key));
                ExportNames.push_back(Key->ToString(Context).ToLocalChecked());
            }
        }
    }

    v8::Local<v8::Module> SyntheticModule = v8::Module::CreateSyntheticModule(
        Isolate, FV8Utils::V8String(Isolate, ModuleName), ExportNames, [](v8::Local<v8::Context> ContextInner, v8::Local<v8::Module> Module) -> v8::MaybeLocal<v8::Value> {
        const auto IsolateInner = ContextInner->GetIsolate();
        auto       Self         = FV8Utils::IsolateData<JsEnv>(IsolateInner);

        const auto ModuleInfoIt = Self->FindModuleInfo(Module);
        check(ModuleInfoIt != Self->HashToModuleInfo.end());
        auto CJSValueInner = ModuleInfoIt->second->CJSValue.Get(IsolateInner);

        Module->SetSyntheticModuleExport(IsolateInner, v8::String::NewFromUtf8(IsolateInner, "default", v8::NewStringType::kNormal).ToLocalChecked(), CJSValueInner);

        if (CJSValueInner->IsObject())
        {
            auto JsObjectInner = CJSValueInner->ToObject(ContextInner).ToLocalChecked();
            auto KeysInner     = JsObjectInner->GetOwnPropertyNames(ContextInner).ToLocalChecked();
            for (decltype(KeysInner->Length()) ii = 0; ii < KeysInner->Length(); ++ii)
            {
                v8::Local<v8::Value> KeyInner;
                v8::Local<v8::Value> ValueInner;
                if (KeysInner->Get(ContextInner, ii).ToLocal(&KeyInner) && JsObjectInner->Get(ContextInner, KeyInner).ToLocal(&ValueInner))
                {
                    // UE_LOG(LogTemp, Warning, TEXT("-----set '%s'"), *FV8Utils::ToFString(IsolateInner, KeyInner));
                    Module->SetSyntheticModuleExport(IsolateInner, KeyInner->ToString(ContextInner).ToLocalChecked(), ValueInner);
                }
            }
        }

        return v8::MaybeLocal<v8::Value>(v8::True(IsolateInner));
    });

    FModuleInfo* Info = new FModuleInfo;
    Info->Module.Reset(Isolate, SyntheticModule);
    Info->CJSValue.Reset(Isolate, CJSValue);
    HashToModuleInfo.emplace(SyntheticModule->GetIdentityHash(), Info);

    return SyntheticModule;
#endif
}

std::unordered_multimap<int, JsEnv::FModuleInfo*>::iterator JsEnv::FindModuleInfo(v8::Local<v8::Module> Module)
{
    auto Range = HashToModuleInfo.equal_range(Module->GetIdentityHash());
    for (auto It = Range.first; It != Range.second; ++It)
    {
        if (It->second->Module == Module)
        {
            return It;
        }
    }
    return HashToModuleInfo.end();
}

v8::MaybeLocal<v8::Module> JsEnv::ResolveModuleCallback(v8::Local<v8::Context> Context, v8::Local<v8::String> Specifier, v8::Local<v8::Module> Referrer)
{
    auto       Self         = FV8Utils::IsolateData<JsEnv>(Context->GetIsolate());
    const auto ItModuleInfo = Self->FindModuleInfo(Referrer);
    check(ItModuleInfo != Self->HashToModuleInfo.end());
    const auto RefModuleName = Self->ObjectToString(Specifier);
    auto       ItRefModule   = ItModuleInfo->second->ResolveCache.find(RefModuleName);
    check(ItRefModule != ItModuleInfo->second->ResolveCache.end());
    return (ItRefModule->second).Get(Context->GetIsolate());
}


namespace PUERTS_NAMESPACE
{
    namespace v8_impl
    {
        v8::Local<v8::Value> FindOrAddYrObject(v8::Isolate* InIsolate, v8::Local<v8::Context>& Context, AbstractClass* YrObject, bool SkipTypeScriptInitial)
        {
            return gJsEnv->FindOrAdd(InIsolate, Context, YrObject, SkipTypeScriptInitial);
        }
    } // namespace v8_impl
} // namespace PUERTS_NAMESPACE

#include <AbstractClass.h>
#include "yr/api/yr_entity.h"
using namespace entt::literals;

static const void* gYrJsTypeID[static_cast<size_t>(AbstractType::DiskLaser) + 1] {};

v8::Local<v8::Value> JsEnv::FindOrAdd(v8::Isolate* Isolate, v8::Local<v8::Context>& Context, AbstractClass* YrObject, bool SkipTypeScriptInitial)
{
    // create and link
    if (!YrObject)
    {
        return v8::Undefined(Isolate);
    }

    auto PersistentValuePtr = ObjectMap.find(YrObject);
    if (PersistentValuePtr == ObjectMap.end()) // create and link
    {
        size_t WhatAmI = static_cast<size_t>(YrObject->WhatAmI());
        const void* TypeId  = gYrJsTypeID[WhatAmI];
        if (!TypeId)
        {
            auto        meta     = GetYrClassMeta(YrObject);
            const char* TypeName = meta.prop("name"_hs).value().cast<const char*>();

            auto JsRegistration  = FindCppTypeClassByName(TypeName);
            gYrJsTypeID[WhatAmI] = TypeId = JsRegistration->TypeId;
        }
        
        v8::Local<v8::Value> Result = DataTransfer::FindOrAddCData(Isolate, Context, TypeId, YrObject, true);
        return Result;
    }
    else
    {
        return v8::Local<v8::Value>::New(Isolate, PersistentValuePtr->second);
    }
}
