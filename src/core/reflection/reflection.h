#pragma once

#include "core/reflection/macro.h"
#include "core/reflection/container.h"
#include <entt/meta/resolve.hpp>

static std::pair<entt::meta_type, size_t> get_array_info(entt::meta_type type)
{
    if (!type.is_array())
        return {};

    using namespace entt::literals;
    entt::meta_prop elementTypeFnProp = type.prop("array_element_type_fn"_hs);
    if (elementTypeFnProp)
    {
        auto elementTypeFn = elementTypeFnProp.value().cast<entt::meta_type(*)()>();
        entt::meta_prop sizeProp = type.prop("array_size"_hs);
        return {elementTypeFn(), sizeProp.value().cast<int>()};
    }
    return {};
}

