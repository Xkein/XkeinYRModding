#pragma once
#include "runtime/platform/platform.h"
#include <string>
#include <string_view>

void buffer_to_string(std::string& result, const uint8* buffer, uint32 size);

CORE_API std::string_view get_pool_string_view(std::string_view str_view);
