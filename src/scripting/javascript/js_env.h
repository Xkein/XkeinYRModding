#pragma once

#include <BackendEnv.h>
#include <JSFunction.h>
#include <CppObjectMapper.h>
#include <DataTransfer.h>
#include <memory>

class JsEnv
{
public:
    JsEnv();
    ~JsEnv();

    bool Eval(const char* Code, const char* Path);

    void SetLastException(v8::Local<v8::Value> Exception);

    void LowMemoryNotification();

    bool IdleNotificationDeadline(double DeadlineInSeconds);

    void RequestMinorGarbageCollectionForTesting();

    void RequestFullGarbageCollectionForTesting();

    void CreateInspector(int32_t Port);

    void DestroyInspector();

    bool InspectorTick();

    void LogicTick();

    bool ClearModuleCache(const char* Path);

    std::string GetJSStackTrace();

    std::string ObjectToString(v8::Local<v8::Value> value);
    std::string ObjectToString(const v8::PersistentBase<v8::Value>& value);

    PUERTS_NAMESPACE::FBackendEnv      BackendEnv;
    PUERTS_NAMESPACE::FResultInfo      ResultInfo;
    PUERTS_NAMESPACE::FCppObjectMapper CppObjectMapper;

    std::vector<char>               StrBuffer;
    v8::UniquePersistent<v8::Value> LastException;
    std::string                     LastExceptionInfo;
    v8::UniquePersistent<v8::Function> JsPromiseRejectCallback;

    v8::Isolate* MainIsolate;
};

extern YRSCRIPTING_API std::shared_ptr<JsEnv> gJsEnv;
