#pragma once

#include <string>
#include <Windows.h>

std::string DumpStackTrace(EXCEPTION_POINTERS* info);

