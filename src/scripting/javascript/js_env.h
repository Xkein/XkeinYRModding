#pragma once

#include "runtime/platform/platform.h"
#include "js_module_loader.h"
#include <CppObjectMapper.h>
#include <DataTransfer.h>
#include <memory>

namespace PUERTS_NAMESPACE
{
    class FBackendEnv;
    class V8Inspector;
    class V8InspectorChannel;
}
class AbstractClass;

struct JsResultInfo
{
    v8::Isolate* Isolate;

    v8::UniquePersistent<v8::Context> Context;

    v8::UniquePersistent<v8::Value> Result;
};

class JsEnv
{
public:
    JsEnv();
    ~JsEnv();

    bool Eval(const char* Code, const char* Path, v8::Global<v8::Value>* result = nullptr);

    void ExecuteModule(const char* ModuleName);

    void SetLastException(v8::Local<v8::Value> Exception);

    void LowMemoryNotification();

    bool IdleNotificationDeadline(double DeadlineInSeconds);

    void RequestMinorGarbageCollectionForTesting();

    void RequestFullGarbageCollectionForTesting();

    void CreateInspector(int32_t Port);
    
    void WaitDebugger(double Timeout = 0);

    void DestroyInspector();

    bool InspectorTick();

    void LogicTick();

    bool ClearModuleCache(const char* Path);

    void InitExtensionMethodsMap();

    void ReloadModule(const char* ModuleName, const char* JsSource);

    std::function<void(const char*)> OnSourceLoadedCallback;

    void OnSourceLoaded(std::function<void(const char*)> Callback);

    std::string GetJSStackTrace();

    std::string ObjectToString(v8::Local<v8::Value> value);
    std::string ObjectToString(const v8::PersistentBase<v8::Value>& value);

    v8::Local<v8::Value> FindOrAdd(v8::Isolate* Isolate, v8::Local<v8::Context>& Context, AbstractClass* YrObject, bool SkipTypeScriptInitial);

    static std::string TryCatchToString(v8::Isolate* Isolate, v8::TryCatch* TryCatch);

    static v8::Local<v8::String> ToV8String(v8::Isolate* Isolate, const char* String);

    std::unique_ptr<PUERTS_NAMESPACE::FBackendEnv> BackendEnv;
    PUERTS_NAMESPACE::FCppObjectMapper             CppObjectMapper;

    JsResultInfo                       ResultInfo;
    v8::Global<v8::Context>            DefaultContext;
    std::vector<char>                  StrBuffer;
    v8::UniquePersistent<v8::Value>    LastException;
    std::string                        LastExceptionInfo;

    v8::Isolate* MainIsolate;

private:
    bool LoadFile(const char* RequiringDir, const char* ModuleName, std::string& OutPath, std::string& OutDebugPath, std::vector<uint8>& Data, std::string& ErrInfo);

    void EvalScript(const v8::FunctionCallbackInfo<v8::Value>& Info);

    void Log(const v8::FunctionCallbackInfo<v8::Value>& Info);

    void SearchModule(const v8::FunctionCallbackInfo<v8::Value>& Info);

    void LoadModule(const v8::FunctionCallbackInfo<v8::Value>& Info);

    void FindModule(const v8::FunctionCallbackInfo<v8::Value>& Info);

    void JsHotReload(const char* ModuleName, const char* JsSource);

    void ReloadSource(const char* Path, const char* JsSource);

    void SetInspectorCallback(const v8::FunctionCallbackInfo<v8::Value>& Info);

    void DispatchProtocolMessage(const v8::FunctionCallbackInfo<v8::Value>& Info);

    void LoadCppType(const v8::FunctionCallbackInfo<v8::Value>& Info);

#ifndef WITH_QUICKJS
    struct FModuleInfo
    {
        v8::Global<v8::Module>                        Module;
        std::map<std::string, v8::Global<v8::Module>> ResolveCache;
        v8::Global<v8::Value>                         CJSValue;
    };


    v8::MaybeLocal<v8::Module> FetchESModuleTree(v8::Local<v8::Context> Context, const char* FileName);

    v8::MaybeLocal<v8::Module> FetchCJSModuleAsESModule(v8::Local<v8::Context> Context, const char* ModuleName);

    std::unordered_multimap<int, FModuleInfo*>::iterator FindModuleInfo(v8::Local<v8::Module> Module);

    static v8::MaybeLocal<v8::Module> ResolveModuleCallback(v8::Local<v8::Context> Context, v8::Local<v8::String> Specifier, v8::Local<v8::Module> Referrer);

    PUERTS_NAMESPACE::V8Inspector* Inspector;

    PUERTS_NAMESPACE::V8InspectorChannel* InspectorChannel;

    v8::Global<v8::Function> InspectorMessageHandler;

    std::map<std::string, v8::Global<v8::Module>> PathToModule;

    std::unordered_multimap<int, FModuleInfo*> HashToModuleInfo;

    v8::Global<v8::Function> Require;

    v8::Global<v8::Function> GetESMMain;

    v8::Global<v8::Function> ReloadJs;
#endif
    
    std::unordered_map<AbstractClass*, v8::UniquePersistent<v8::Value>> ObjectMap;

    std::shared_ptr<IJSModuleLoader> ModuleLoader;

    bool ExtensionMethodsMapInited;
};

extern XKEINEXT_API JsEnv* gJsEnv;
