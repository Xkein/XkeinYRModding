#include "debug_util.h"


std::string FormatSystemErrorCode(DWORD errorCode)
{
    // Get the error message ID, if any.
    DWORD errorMessageID = errorCode;
    if (errorMessageID == 0)
    {
        return "no error message"; // No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    // Ask Win32 to give us the string version of that message ID.
    // The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorMessageID, 0, (LPSTR)&messageBuffer, 0, NULL);

    // Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    // Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    return message;
}


LONG WINAPI ExceptionFilterGetInfo(EXCEPTION_POINTERS* info, std::string*& stackTrace)
{
    stackTrace = new std::string(DumpStackTrace(info));
    return EXCEPTION_EXECUTE_HANDLER;
}

static LONG WINAPI ExceptionFilterGetInfo(EXCEPTION_POINTERS* info, EXCEPTION_POINTERS*& refInfo, std::string*& stackTrace)
{
    refInfo    = info;
    stackTrace = new std::string(DumpStackTrace(info));
    return EXCEPTION_EXECUTE_HANDLER;
}

static inline void InvokeErrorCallback(const std::function<void(std::string)>& errorCallBack, std::string* stackTrace)
{
    std::string tmp = std::move(*stackTrace);
    delete stackTrace;
    stackTrace = nullptr;
    errorCallBack(tmp);
}

YREXTCORE_API void GuardExecute(const std::function<void()>& func, const std::function<void(std::string)>& errorCallBack)
{
    EXCEPTION_POINTERS* info;
    std::string*        stackTrace;
    __try
    {
        func();
    }
    __except (ExceptionFilterGetInfo(GetExceptionInformation(), info, stackTrace))
    {
        InvokeErrorCallback(errorCallBack, stackTrace);
    }
}

YREXTCORE_API void GuardExecute(const std::function<void()>& func, const std::function<void()>& finallyCallBack)
{
    __try
    {
        func();
    }
    __finally
    {
        finallyCallBack();
    }
}

YREXTCORE_API void GuardExecute(const std::function<void()>& func, const std::function<void(std::string)>& errorCallBack, const std::function<void()>& finallyCallBack)
{
    __try
    {
        GuardExecute(func, errorCallBack);
    }
    __finally
    {
        finallyCallBack();
    }
}
