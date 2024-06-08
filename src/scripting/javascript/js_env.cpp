#include "js_env.h"
#include "core/raii_invoker.h"
#include <yr/debug_util.h>
#include <core/logger/logger.h>
#include <core/string/string_tool.h>
#include <core/platform/path.h>
#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include <filesystem>

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

JsEnv::JsEnv()
{
    StrBuffer.resize(1024);

    ModuleLoader = std::make_shared<DefaultJSModuleLoader>("assets/js");

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

    ExecuteModule("setup.js");
    ExecuteModule("main.js");

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

bool JsEnv::LoadFile(const char* RequiringDir, const char* ModuleName, std::string& OutPath, std::string& OutDebugPath, std::vector<uint8>& Data, std::string& ErrInfo)
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
    std::vector<uint8> Data;
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

    auto DirName = Paths::GetPath(FileName).string();

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
                        if (ModuleLoader->Search(Paths::GetPath(OutPath).string().c_str(), ESMMain.c_str(), ESMMainOutPath, ESMMainOutDebugPath))
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
    return v8::MaybeLocal<v8::Module>();
}

std::unordered_multimap<int, JsEnv::FModuleInfo*>::iterator JsEnv::FindModuleInfo(v8::Local<v8::Module> Module)
{
    return std::unordered_multimap<int, FModuleInfo*>::iterator();
}

v8::MaybeLocal<v8::Module> JsEnv::ResolveModuleCallback(v8::Local<v8::Context> Context, v8::Local<v8::String> Specifier, v8::Local<v8::Module> Referrer)
{
    return v8::MaybeLocal<v8::Module>();
}
