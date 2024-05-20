#include "js_env.h"
#include "core/raii_invoker.h"

#include <v8-context.h>
#include <v8-exception.h>
#include <v8-initialization.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-script.h>
#include <v8-template.h>
#include <libplatform/libplatform.h>

#include <core/logger/logger.h>
#include <sstream>

YRSCRIPTING_API std::shared_ptr<JsEnv> gJsEnv;

GLOBAL_INVOKE_ON_CTOR([]() {
    gJsEnv = std::make_shared<JsEnv>();
})

// Extracts a C string from a V8 Utf8Value.
static const char* ToCString(const v8::String::Utf8Value& value)
{
    return *value ? *value : "<string conversion failed>";
}

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
static void Print(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    bool              first = true;
    std::stringstream ss;
    for (int i = 0; i < info.Length(); i++)
    {
        v8::HandleScope handle_scope(info.GetIsolate());
        if (first)
        {
            first = false;
        }
        else
        {
            ss << " ";
        }
        v8::String::Utf8Value str(info.GetIsolate(), info[i]);
        const char*           cstr = ToCString(str);
        ss << cstr;
    }
    gLogger->info(ss.str());
}

// Creates a new execution environment containing the built-in
// functions.
v8::Global<v8::Context> JsEnv::CreateContext()
{
    v8::HandleScope handle_scope(isolate);
    // Create a template for the global object.
    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
    // Bind the global 'print' function to the C++ Print callback.
    global->Set(isolate, "print", v8::FunctionTemplate::New(isolate, Print));
    global->Set(isolate, "Cpp", CreateCppObjects());
    // Return the context.
    v8::Local<v8::Context> context = v8::Context::New(isolate, nullptr, global);
    return v8::Global<v8::Context>(isolate, context);
}

JsEnv::JsEnv()
{
    // v8::V8::InitializeICUDefaultLocation(argv[0]);
    // v8::V8::InitializeExternalStartupData(argv[0]);
    platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    // v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
    v8::V8::Initialize();
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();

    isolate       = v8::Isolate::New(create_params);
    isolate_scope = new v8::Isolate::Scope(isolate);
    context       = CreateContext();
    if (context.IsEmpty())
    {
        gLogger->error("Error creating context\n");
        return;
    }

    gLogger->info("v8 engine started.");
}

JsEnv::~JsEnv()
{
    context.Reset();
    delete isolate_scope;
    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::DisposePlatform();
    delete create_params.array_buffer_allocator;
    gLogger->info("v8 engine disposed.");
}

bool JsEnv::ExecuteString(v8::Local<v8::String> source, v8::Local<v8::Value> name, bool print_result, bool report_exceptions)
{
    v8::HandleScope        handle_scope(isolate);
    v8::TryCatch           try_catch(isolate);
    v8::ScriptOrigin       origin(isolate, name);
    v8::Local<v8::Context> context(isolate->GetCurrentContext());
    v8::Local<v8::Script>  script;
    if (!v8::Script::Compile(context, source, &origin).ToLocal(&script))
    {
        // Print errors that happened during compilation.
        if (report_exceptions)
            ReportException(&try_catch);
        return false;
    }
    else
    {
        v8::Local<v8::Value> result;
        if (!script->Run(context).ToLocal(&result))
        {
            assert(try_catch.HasCaught());
            // Print errors that happened during execution.
            if (report_exceptions)
                ReportException(&try_catch);
            return false;
        }
        else
        {
            assert(!try_catch.HasCaught());
            if (print_result && !result->IsUndefined())
            {
                // If all went well and the result wasn't undefined then print
                // the returned value.
                v8::String::Utf8Value str(isolate, result);
                const char*           cstr = ToCString(str);
                gLogger->info(cstr);
            }
            return true;
        }
    }
}

bool JsEnv::ExecuteString(const char* source, const char* name, bool print_result, bool report_exceptions)
{
    v8::HandleScope       handle_scope(isolate);
    v8::Context::Scope    context_scope(context.Get(isolate));
    v8::Local<v8::String> run_name = v8::String::NewFromUtf8(isolate, name).ToLocalChecked();
    return ExecuteString(v8::String::NewFromUtf8(isolate, source).ToLocalChecked(), run_name, print_result, report_exceptions);
}

void JsEnv::ReportException(v8::TryCatch* try_catch)
{
    v8::HandleScope        handle_scope(isolate);
    v8::String::Utf8Value  exception(isolate, try_catch->Exception());
    const char*            exception_string = ToCString(exception);
    v8::Local<v8::Message> message          = try_catch->Message();
    if (message.IsEmpty())
    {
        // V8 didn't provide any extra information about this error; just
        // print the exception.
        gLogger->error(exception_string);
    }
    else
    {
        // Print (filename):(line number): (message).
        v8::String::Utf8Value  filename(isolate, message->GetScriptOrigin().ResourceName());
        v8::Local<v8::Context> context(isolate->GetCurrentContext());
        const char*            filename_string = ToCString(filename);
        int                    linenum         = message->GetLineNumber(context).FromJust();
        gLogger->error("{}:{}: {}", filename_string, linenum, exception_string);
        // Print line of source code.
        v8::String::Utf8Value sourceline(isolate, message->GetSourceLine(context).ToLocalChecked());
        const char*           sourceline_string = ToCString(sourceline);
        gLogger->error(sourceline_string);
        // Print wavy underline (GetUnderline is deprecated).
        int start = message->GetStartColumn(context).FromJust();
        for (int i = 0; i < start; i++)
        {
            fprintf(stderr, " ");
        }
        int end = message->GetEndColumn(context).FromJust();
        for (int i = start; i < end; i++)
        {
            fprintf(stderr, "^");
        }
        fprintf(stderr, "\n");
        v8::Local<v8::Value> stack_trace_string;
        if (try_catch->StackTrace(context).ToLocal(&stack_trace_string) && stack_trace_string->IsString() && stack_trace_string.As<v8::String>()->Length() > 0)
        {
            v8::String::Utf8Value stack_trace(isolate, stack_trace_string);
            const char*           err = ToCString(stack_trace);
            gLogger->error(err);
        }
    }
}
