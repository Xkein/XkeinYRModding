#include "debug_util.h"
#include "runtime/logger/logger.h"
#include <filesystem>
#include <sstream>
#include <string_view>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <Windows.h>
#include <dbghelp.h>
#include <stddef.h>

namespace fs = std::filesystem;

// https://github.com/chromium/chromium/blob/main/base/debug/stack_trace_win.cc
// Copyright 2012 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

bool  g_initialized_symbols = false;
DWORD g_init_error          = ERROR_SUCCESS;
// STATUS_INFO_LENGTH_MISMATCH is declared in <ntstatus.h>, but including that
// header creates a conflict with base/win/windows_types.h, so re-declaring it
// here.
DWORD g_status_info_length_mismatch = 0xC0000004;

class StackTrace
{
public:
    // For other platforms, use 250. This seems reasonable without
    // being huge.
    static constexpr size_t kMaxTraces = 250;
    // LINT.ThenChange(dwarf_line_no.cc:max_stack_frames)

    // Creates a stacktrace for an exception.
    // Note: this function will throw an import not found (StackWalk64) exception
    // on system without dbghelp 5.1.
    StackTrace(EXCEPTION_POINTERS* exception_pointers);
    StackTrace(const CONTEXT* context);

public:
    void OutputToStreamWithPrefixImpl(std::ostream* os, std::string_view prefix_string) const;

    void InitTrace(const CONTEXT* context_record);

    const void* trace_[kMaxTraces];

    // The number of valid frames in |trace_|, or 0 if collection was suppressed.
    size_t count_ = 0;
};

// Prints the exception call stack.
// This is the unit tests exception filter.
void StackDumpExceptionFilter(std::ostream* os, EXCEPTION_POINTERS* info)
{
    DWORD exc_code = info->ExceptionRecord->ExceptionCode;
    (*os) << "Received fatal exception ";
    switch (exc_code)
    {
        case EXCEPTION_ACCESS_VIOLATION:
            (*os) << "EXCEPTION_ACCESS_VIOLATION";
            break;
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            (*os) << "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
            break;
        case EXCEPTION_BREAKPOINT:
            (*os) << "EXCEPTION_BREAKPOINT";
            break;
        case EXCEPTION_DATATYPE_MISALIGNMENT:
            (*os) << "EXCEPTION_DATATYPE_MISALIGNMENT";
            break;
        case EXCEPTION_FLT_DENORMAL_OPERAND:
            (*os) << "EXCEPTION_FLT_DENORMAL_OPERAND";
            break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
            (*os) << "EXCEPTION_FLT_DIVIDE_BY_ZERO";
            break;
        case EXCEPTION_FLT_INEXACT_RESULT:
            (*os) << "EXCEPTION_FLT_INEXACT_RESULT";
            break;
        case EXCEPTION_FLT_INVALID_OPERATION:
            (*os) << "EXCEPTION_FLT_INVALID_OPERATION";
            break;
        case EXCEPTION_FLT_OVERFLOW:
            (*os) << "EXCEPTION_FLT_OVERFLOW";
            break;
        case EXCEPTION_FLT_STACK_CHECK:
            (*os) << "EXCEPTION_FLT_STACK_CHECK";
            break;
        case EXCEPTION_FLT_UNDERFLOW:
            (*os) << "EXCEPTION_FLT_UNDERFLOW";
            break;
        case EXCEPTION_ILLEGAL_INSTRUCTION:
            (*os) << "EXCEPTION_ILLEGAL_INSTRUCTION";
            break;
        case EXCEPTION_IN_PAGE_ERROR:
            (*os) << "EXCEPTION_IN_PAGE_ERROR";
            break;
        case EXCEPTION_INT_DIVIDE_BY_ZERO:
            (*os) << "EXCEPTION_INT_DIVIDE_BY_ZERO";
            break;
        case EXCEPTION_INT_OVERFLOW:
            (*os) << "EXCEPTION_INT_OVERFLOW";
            break;
        case EXCEPTION_INVALID_DISPOSITION:
            (*os) << "EXCEPTION_INVALID_DISPOSITION";
            break;
        case EXCEPTION_NONCONTINUABLE_EXCEPTION:
            (*os) << "EXCEPTION_NONCONTINUABLE_EXCEPTION";
            break;
        case EXCEPTION_PRIV_INSTRUCTION:
            (*os) << "EXCEPTION_PRIV_INSTRUCTION";
            break;
        case EXCEPTION_SINGLE_STEP:
            (*os) << "EXCEPTION_SINGLE_STEP";
            break;
        case EXCEPTION_STACK_OVERFLOW:
            (*os) << "EXCEPTION_STACK_OVERFLOW";
            break;
        default:
            (*os) << "0x" << std::hex << exc_code;
            break;
    }
    (*os) << "\n";

    StackTrace(info).OutputToStreamWithPrefixImpl(os, "");
}

fs::path GetExePath()
{
    wchar_t system_buffer[MAX_PATH];
    GetModuleFileNameW(NULL, system_buffer, MAX_PATH);
    system_buffer[MAX_PATH - 1] = L'\0';
    return fs::path(system_buffer);
}

constexpr size_t kSymInitializeRetryCount = 3;

// A wrapper for SymInitialize. SymInitialize seems to occasionally fail
// because of an internal race condition. So  wrap it and retry a finite
// number of times.
// See crbug.com/1339753
bool SymInitializeWrapper(HANDLE handle, BOOL invade_process)
{
    for (size_t i = 0; i < kSymInitializeRetryCount; ++i)
    {
        if (SymInitialize(handle, nullptr, invade_process))
            return true;

        g_init_error = GetLastError();
        if (g_init_error != g_status_info_length_mismatch)
            return false;
    }
    gLogger->error("SymInitialize failed repeatedly.");
    return false;
}

bool SymInitializeCurrentProc()
{
    const HANDLE current_process = GetCurrentProcess();
    if (SymInitializeWrapper(current_process, TRUE))
        return true;

    // g_init_error is updated by SymInitializeWrapper.
    // No need to do "g_init_error = GetLastError()" here.
    if (g_init_error != ERROR_INVALID_PARAMETER)
        return false;

    // SymInitialize() can fail with ERROR_INVALID_PARAMETER when something has
    // already called SymInitialize() in this process. For example, when absl
    // support for gtest is enabled, it results in absl calling SymInitialize()
    // almost immediately after startup. In such a case, try to reinit to see if
    // that succeeds.
    SymCleanup(current_process);
    if (SymInitializeWrapper(current_process, TRUE))
        return true;

    return false;
}

bool InitializeSymbols()
{
    if (g_initialized_symbols)
    {
        // Force a reinitialization. Will ensure any modules loaded after process
        // startup also get symbolized.
        SymCleanup(GetCurrentProcess());
        g_initialized_symbols = false;
    }
    g_initialized_symbols = true;
    // Defer symbol load until they're needed, use undecorated names, and get line
    // numbers.
    SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);
    if (!SymInitializeCurrentProc())
    {
        // When it fails, we should not call debugbreak since it kills the current
        // process (prevents future tests from running or kills the browser
        // process).
        gLogger->error("SymInitialize failed: {}", g_init_error);
        return false;
    }

    // When transferring the binaries e.g. between bots, path put
    // into the executable will get off. To still retrieve symbols correctly,
    // add the directory of the executable to symbol search path.
    // All following errors are non-fatal.
    static constexpr size_t kSymbolsArraySize = 1024;
    wchar_t                 symbols_path[kSymbolsArraySize];

    // Note: The below function takes buffer size as number of characters,
    // not number of bytes!
    if (!SymGetSearchPathW(GetCurrentProcess(), symbols_path, kSymbolsArraySize))
    {
        g_init_error = GetLastError();
        gLogger->warn("SymGetSearchPath failed: {}", g_init_error);
        return false;
    }

    std::wstring new_path = std::wstring(symbols_path) + L";" + GetExePath().wstring();
    if (!SymSetSearchPathW(GetCurrentProcess(), new_path.c_str()))
    {
        g_init_error = GetLastError();
        gLogger->warn("SymSetSearchPath failed: {}", g_init_error);
        return false;
    }

    g_init_error = ERROR_SUCCESS;
    return true;
}

// SymbolContext is a threadsafe singleton that wraps the DbgHelp Sym* family
// of functions.  The Sym* family of functions may only be invoked by one
// thread at a time.  SymbolContext code may access a symbol server over the
// network while holding the lock for this singleton.  In the case of high
// latency, this code will adversely affect performance.
//
// There is also a known issue where this backtrace code can interact
// badly with breakpad if breakpad is invoked in a separate thread while
// we are using the Sym* functions.  This is because breakpad does now
// share a lock with this function.  See this related bug:
//
//   https://crbug.com/google-breakpad/311
//
// This is a very unlikely edge case, and the current solution is to
// just ignore it.
class SymbolContext
{
public:
    static SymbolContext* GetInstance()
    {
        static SymbolContext context;
        return &context;
    }

    SymbolContext(const SymbolContext&)            = delete;
    SymbolContext& operator=(const SymbolContext&) = delete;

    // For the given trace, attempts to resolve the symbols, and output a trace
    // to the ostream os.  The format for each line of the backtrace is:
    //
    //    <tab>SymbolName[0xAddress+Offset] (FileName:LineNo)
    //
    // This function should only be called if Init() has been called.  We do not
    // LOG(FATAL) here because this code is called might be triggered by a
    // LOG(FATAL) itself. Also, it should not be calling complex code that is
    // extensible like PathService since that can in turn fire CHECKs.
    void OutputTraceToStream(const void* const* trace, size_t count, std::ostream* os, std::string_view prefix_string)
    {
        for (size_t i = 0; (i < count) && os->good(); ++i)
        {
            const int kMaxNameLength = 256;
            DWORD_PTR frame          = reinterpret_cast<DWORD_PTR>(trace[i]);

            // Code adapted from MSDN example:
            // http://msdn.microsoft.com/en-us/library/ms680578(VS.85).aspx
            ULONG64 buffer[(sizeof(SYMBOL_INFO) + kMaxNameLength * sizeof(wchar_t) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
            memset(buffer, 0, sizeof(buffer));

            // Initialize symbol information retrieval structures.
            DWORD64      sym_displacement = 0;
            PSYMBOL_INFO symbol           = reinterpret_cast<PSYMBOL_INFO>(&buffer[0]);
            symbol->SizeOfStruct          = sizeof(SYMBOL_INFO);
            symbol->MaxNameLen            = kMaxNameLength - 1;
            BOOL has_symbol               = SymFromAddr(GetCurrentProcess(), frame, &sym_displacement, symbol);

            // Attempt to retrieve line number information.
            DWORD           line_displacement = 0;
            IMAGEHLP_LINE64 line              = {};
            line.SizeOfStruct                 = sizeof(IMAGEHLP_LINE64);
            BOOL has_line                     = SymGetLineFromAddr64(GetCurrentProcess(), frame, &line_displacement, &line);

            // Output the backtrace line.
            (*os) << prefix_string << "\t";
            if (has_symbol)
            {
                (*os) << symbol->Name << " [0x" << trace[i] << "+" << sym_displacement << "]";
            }
            else
            {
                // If there is no symbol information, add a spacer.
                (*os) << "(No symbol) [0x" << trace[i] << "]";
            }
            if (has_line)
            {
                (*os) << " (" << line.FileName << ":" << line.LineNumber << ")";
            }
            (*os) << "\n";
        }
    }

private:
    SymbolContext()
    {
        InitializeSymbols();
    }
};

size_t CollectStackTrace(const void** trace, size_t count)
{
    // When walking our own stack, use CaptureStackBackTrace().
    return CaptureStackBackTrace(0, count, const_cast<void**>(trace), NULL);
}

StackTrace::StackTrace(EXCEPTION_POINTERS* exception_pointers)
{
    InitTrace(exception_pointers->ContextRecord);
}

StackTrace::StackTrace(const CONTEXT* context)
{
    InitTrace(context);
}

void StackTrace::InitTrace(const CONTEXT* context_record)
{
    // StackWalk64 modifies the register context in place, so we have to copy it
    // so that downstream exception handlers get the right context.  The incoming
    // context may have had more register state (YMM, etc) than we need to unwind
    // the stack. Typically StackWalk64 only needs integer and control registers.
    CONTEXT context_copy;
    memcpy(&context_copy, context_record, sizeof(context_copy));
    context_copy.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;

    // When walking an exception stack, we need to use StackWalk64().
    count_ = 0;
    // Initialize stack walking.
    STACKFRAME64 stack_frame;
    memset(&stack_frame, 0, sizeof(stack_frame));
    
#if defined(ARCH_CPU_X86_64)
    DWORD machine_type           = IMAGE_FILE_MACHINE_AMD64;
    stack_frame.AddrPC.Offset    = context_record->Rip;
    stack_frame.AddrFrame.Offset = context_record->Rbp;
    stack_frame.AddrStack.Offset = context_record->Rsp;
#elif defined(ARCH_CPU_ARM64)
    DWORD machine_type           = IMAGE_FILE_MACHINE_ARM64;
    stack_frame.AddrPC.Offset    = context_record->Pc;
    stack_frame.AddrFrame.Offset = context_record->Fp;
    stack_frame.AddrStack.Offset = context_record->Sp;
#elif defined(_X86_)
    DWORD machine_type           = IMAGE_FILE_MACHINE_I386;
    stack_frame.AddrPC.Offset    = context_record->Eip;
    stack_frame.AddrFrame.Offset = context_record->Ebp;
    stack_frame.AddrStack.Offset = context_record->Esp;
#else
#error Unsupported Windows Arch
#endif
    stack_frame.AddrPC.Mode    = AddrModeFlat;
    stack_frame.AddrFrame.Mode = AddrModeFlat;
    stack_frame.AddrStack.Mode = AddrModeFlat;
    while (StackWalk64(machine_type, GetCurrentProcess(), GetCurrentThread(), &stack_frame, &context_copy, NULL, &SymFunctionTableAccess64, &SymGetModuleBase64, NULL) && count_ < std::size(trace_))
    {
        trace_[count_++] = reinterpret_cast<void*>(stack_frame.AddrPC.Offset);
    }

    for (size_t i = count_; i < std::size(trace_); ++i)
        trace_[i] = NULL;
}

void StackTrace::OutputToStreamWithPrefixImpl(std::ostream* os, std::string_view prefix_string) const
{
    SymbolContext* context = SymbolContext::GetInstance();
    if (g_init_error != ERROR_SUCCESS)
    {
        (*os) << "Error initializing symbols (" << g_init_error << ").  Dumping unresolved backtrace:\n";
        for (size_t i = 0; (i < count_) && os->good(); ++i)
        {
            (*os) << prefix_string << "\t" << trace_[i] << "\n";
        }
    }
    else
    {
        context->OutputTraceToStream(trace_, count_, os, prefix_string);
    }
}

std::string DumpStackTrace(EXCEPTION_POINTERS* info)
{
    if (info == nullptr)
        return "exception pointer is nullptr!!";
    std::stringstream ss;
    StackDumpExceptionFilter(&ss, info);
    return ss.str();
}