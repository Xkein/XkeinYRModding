#pragma once

#include <v8-isolate.h>
#include <v8-initialization.h>
#include <v8-exception.h>
#include <memory>

class JsEnv final
{
public:
    JsEnv();
    ~JsEnv();

    bool ExecuteString(v8::Local<v8::String> source, v8::Local<v8::Value> name, bool print_result = true, bool report_exceptions = true);
    bool ExecuteString(const char* source, const char* name, bool print_result = true, bool report_exceptions = true);
    void ReportException(v8::TryCatch* try_catch);

    v8::Isolate*                  isolate;
    std::unique_ptr<v8::Platform> platform;
    v8::Isolate::CreateParams     create_params;
    v8::Isolate::Scope*           isolate_scope;
    v8::Global<v8::Context>*      context;
};

extern YRSCRIPTING_API std::shared_ptr<JsEnv> gJsEnv;