#pragma once

#include <string>
#include <functional>
#include <Windows.h>

YREXTCORE_API std::string DumpStackTrace(EXCEPTION_POINTERS* info);
YREXTCORE_API std::string FormatSystemErrorCode(DWORD errorCode);
YREXTCORE_API LONG WINAPI ExceptionFilterGetInfo(EXCEPTION_POINTERS* info, std::string*& stackTrace);

YREXTCORE_API void GuardExecute(const std::function<void()>& func, const std::function<void(std::string)>& errorCallBack);
YREXTCORE_API void GuardExecute(const std::function<void()>& func, const std::function<void()>& finallyCallBack);
YREXTCORE_API void GuardExecute(const std::function<void()>& func, const std::function<void(std::string)>& errorCallBack, const std::function<void()>& finallyCallBack);
