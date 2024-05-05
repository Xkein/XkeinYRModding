#pragma once

#include <spdlog/spdlog.h>
#include <memory>

extern CORE_API std::shared_ptr<spdlog::logger> gLogger;
extern CORE_API std::shared_ptr<spdlog::logger> gConsole;
