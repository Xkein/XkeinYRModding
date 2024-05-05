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