#pragma once

#include <string>
#include <Windows.h>

YREXTCORE_API std::string DumpStackTrace(EXCEPTION_POINTERS* info);
YREXTCORE_API std::string FormatSystemErrorCode(DWORD errorCode);
YREXTCORE_API LONG WINAPI ExceptionFilterGetInfo(EXCEPTION_POINTERS* info, std::string*& stackTrace);
