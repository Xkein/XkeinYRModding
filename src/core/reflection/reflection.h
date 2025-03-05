#pragma once

#include "core/reflection/macro.h"
#include "core/reflection/container.h"
#include <entt/meta/resolve.hpp>
#include <vector>

// entt provide basic meta and below classes store more extra meta
struct ArrayMeta {
    entt::type_info element;
    size_t count;
};

struct EnumMeta {
    const char* name;
};

struct EnumConstantMeta {
    const char* name;
};

struct ClassMeta {
    const char* name;
};

struct ParameterMeta {
    const char* name;
};

struct FunctionMeta {
    const char* name;
    std::vector<ParameterMeta> parameters;
};

struct FieldMeta {
    const char* name;
};

