#include "core/reflection/reflection.h"
#include "runtime/logger/logger.h"

entt::meta_any Reflection::GetEnumValueInternal(entt::meta_type type, std::string_view str)
{
    if (!type || !static_cast<EnumMeta*>(type.custom()))
    {
        gLogger->error("could not parse enum {}: no meta!", type.info().name());
        return false;
    }
    for (auto&& [id, data] : type.data())
    {
        EnumConstantMeta* enumConstMeta = data.custom();
        if (str == enumConstMeta->name)
        {
            return data.get({});
        }
    }
    return {};
}

std::string_view Reflection::GetEnumValueNameInternal(entt::meta_type type, entt::meta_any value)
{
    if (!type || !static_cast<EnumMeta*>(type.custom()))
    {
        gLogger->error("could not parse enum {}: no meta!", type.info().name());
        return "<unknown enum>";
    }
    for (auto&& [id, data] : type.data())
    {
        EnumConstantMeta* enumConstMeta = data.custom();
        if (value == data.get({})) {
            return enumConstMeta->name;
        }
    }
    return "<unknown enum value>";
}
