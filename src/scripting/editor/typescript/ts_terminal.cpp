
#include <assert.h>
#include <fcntl.h>
#include <libplatform/libplatform.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <v8-context.h>
#include <v8-exception.h>
#include <v8-initialization.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-script.h>
#include <v8-template.h>

#include <ui/imgui/yr_imgui.h>
#include <core/logger/logger.h>
#include "yr/event/general_event.h"
#include <sstream>

/**
 * This sample program shows how to implement a simple javascript shell
 * based on V8.  This includes initializing V8 with command line options,
 * creating global functions, compiling and executing strings.
 *
 * For a more sophisticated shell, consider using the debug shell D8.
 */

static v8::Global<v8::Context>*   CreateShellContext(v8::Isolate* isolate);
static void                       RunShell(v8::Isolate* isolate, const v8::Global<v8::Context>& context, v8::Platform* platform);
static int                        RunMain(v8::Isolate* isolate, const v8::Global<v8::Context>& context, v8::Platform* platform, int argc, char* argv[]);
static bool                       ExecuteString(v8::Isolate* isolate, v8::Local<v8::String> source, v8::Local<v8::Value> name, bool print_result, bool report_exceptions);
static void                       Print(const v8::FunctionCallbackInfo<v8::Value>& info);
static void                       ReportException(v8::Isolate* isolate, v8::TryCatch* handler);

class TerminalWindow : public YrImGuiWindow
{
public:
    virtual void OnOpen() override
    {
        //v8::V8::InitializeICUDefaultLocation(argv[0]);
        //v8::V8::InitializeExternalStartupData(argv[0]);
        platform = v8::platform::NewDefaultPlatform();
        v8::V8::InitializePlatform(platform.get());
        //v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
        v8::V8::Initialize();
        create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();

        isolate       = v8::Isolate::New(create_params);
        isolate_scope = std::make_unique<v8::Isolate::Scope>(isolate);
        context       = std::unique_ptr<v8::Global<v8::Context>>(CreateShellContext(isolate));
        if (context->IsEmpty())
        {
            gLogger->error("Error creating context\n");
            return;
        }
    }
    virtual void OnFrame() override
    {
        ImGui::Begin("JavaScript Terminal");

        ImGui::Text("terminal");
        ImGui::Checkbox("EnterToRun", &isEnterToRun);
        ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
        if (isEnterToRun)
        {
            flags |= ImGuiInputTextFlags_EnterReturnsTrue;
        }
        bool isEnter = ImGui::InputTextMultiline("##command", buffer, IM_ARRAYSIZE(buffer), ImVec2(800, ImGui::GetTextLineHeight() * 16), flags);
        if (isEnterToRun ? isEnter : ImGui::Button("Run"))
        {
            if (!context->IsEmpty())
            {
                {
                    // Enter the execution environment before evaluating any code.
                    v8::HandleScope       handle_scope(isolate);
                    v8::Context::Scope    context_scope(context->Get(isolate));
                    v8::Local<v8::String> name(v8::String::NewFromUtf8Literal(isolate, "(shell)"));
                    ExecuteString(isolate, v8::String::NewFromUtf8(isolate, buffer).ToLocalChecked(), name, true, true);
                }
                // It is important not to pump the message loop when there are v8::Local
                // handles on the stack, as this may trigger a stackless GC.
                while (v8::platform::PumpMessageLoop(platform.get(), isolate))
                    continue;
            }
            if (isEnter)
            {
                buffer[0] = '/0';
            }
        }
        
        ImGui::End();
    }
    virtual void OnClose() override
    {
        isolate_scope.reset();
        isolate->Dispose();
        v8::V8::Dispose();
        v8::V8::DisposePlatform();
        delete create_params.array_buffer_allocator;
    }

    std::unique_ptr<v8::Platform> platform;
    v8::Isolate::CreateParams create_params;
    v8::Isolate* isolate;
    std::unique_ptr<v8::Isolate::Scope> isolate_scope;
    std::unique_ptr<v8::Global<v8::Context>> context;

    char buffer[1024 * 16];
    bool isEnterToRun {true};
};


std::shared_ptr<TerminalWindow> terminal;

REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, []() {
    if (ImGui::IsKeyReleased(ImGuiKey_GraveAccent))
    {
        if (terminal)
        {
            terminal->Close();
            terminal.reset();
        }
        else
        {
            terminal = std::make_shared<TerminalWindow>();
            terminal->Open();
        }
    }
})



// Extracts a C string from a V8 Utf8Value.
static const char* ToCString(const v8::String::Utf8Value& value)
{
    return *value ? *value : "<string conversion failed>";
}

// Creates a new execution environment containing the built-in
// functions.
v8::Global<v8::Context>* CreateShellContext(v8::Isolate* isolate)
{
    v8::HandleScope handle_scope(isolate);
    // Create a template for the global object.
    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
    // Bind the global 'print' function to the C++ Print callback.
    global->Set(isolate, "print", v8::FunctionTemplate::New(isolate, Print));
    // Return the context.
    v8::Local<v8::Context> context = v8::Context::New(isolate, nullptr, global);
    return new v8::Global<v8::Context>(isolate, context);
}

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
void Print(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    bool first = true;
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

// Executes a string within the current v8 context.
bool ExecuteString(v8::Isolate* isolate, v8::Local<v8::String> source, v8::Local<v8::Value> name, bool print_result, bool report_exceptions)
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
            ReportException(isolate, &try_catch);
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
                ReportException(isolate, &try_catch);
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

void ReportException(v8::Isolate* isolate, v8::TryCatch* try_catch)
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
