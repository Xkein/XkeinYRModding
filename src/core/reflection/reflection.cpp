#include "core/reflection/reflection.h"
#include "runtime/logger/logger.h"

entt::meta_any Reflection::GetEnumValueInternal(entt::meta_type type, std::string_view str)
{
    if (!type || !static_cast<EnumMeta*>(type.custom()))
    {
        gLogger->error("could not parse enum {}: no meta!", type.info().name());
        return {};
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

void* Reflection::CastPtr(const entt::type_info& from, const entt::type_info& to, void* ptr)
{
    entt::meta_type fromType = entt::resolve(from);
    entt::meta_type toType = entt::resolve(to);
    ClassMeta* classMeta = fromType.custom();
    if (!classMeta) {
        gLogger->error("could not cast pointer: {} have no class meta!", from.name());
        return nullptr;
    }
    ConvFunc conv = classMeta->refConv[to.hash()];
    void* result = nullptr;
    if (conv) {
        entt::meta_any any = conv(ptr);
        if (any) {
            result = const_cast<void*>(any.base().data());
        }
    }
    else {
        for (auto &&[_, baseType] : toType.base())
        {
            result = Reflection::CastPtr(from, baseType.info(), ptr);
            if (result) {
                result = Reflection::CastPtr(baseType.info(), to, result);
                break;
            }
        }
    }
    return result;
}