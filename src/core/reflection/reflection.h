#pragma once

#include "core/reflection/macro.h"
#include "core/reflection/container.h"
#include <entt/meta/resolve.hpp>
#include <vector>
#include <string_view>

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

class Reflection
{
    static entt::meta_any GetEnumValueInternal(entt::meta_type type, std::string_view str);
    static std::string_view GetEnumValueNameInternal(entt::meta_type type, entt::meta_any value);
public:
    template<typename T>
    static bool TryGetEnumValue(std::string_view str, T& value) {
        static_assert(std::is_enum_v<T>, "not enum type!");
        entt::meta_any result = GetEnumValueInternal(entt::resolve<T>(), str);
        if (result) {
            value = result.cast<T>();
            return true;
        }
        return false;
    }

    template<typename T>
    static std::string_view GetEnumValueName(T value) {
        static_assert(std::is_enum_v<T>, "not enum type!");
        return GetEnumValueNameInternal(entt::resolve<T>(), value);
    }

};
