#pragma once
#include "core/reflection/reflection.h"
#include "yr/api/yr_entity.h"
#ifndef __HEADER_TOOL__
#include <entt/meta/factory.hpp>
#include <concepts>
using namespace entt::literals;
namespace detail
{
    template<typename Type, typename TargetType>
    concept component_has_creator = requires(entt::registry& reg, entt::entity entity) {
        Type::OnEntityConstruct(reg, entity);
    };

    template<typename Type, typename TargetType>
    concept component_has_creator_target = requires(entt::registry& reg, entt::entity entity, TargetType* pTarget) {
        Type::OnEntityConstruct(reg, entity, pTarget);
    };

    template<typename Type, typename TargetType>
    concept component_has_template_creator = requires(entt::registry& reg, entt::entity entity) {
        Type::template OnEntityConstruct<TargetType>(reg, entity);
    };
}

struct ComponentInstantiation
{

    template<typename Type, typename TargetType>
    static void CreateComponent(entt::registry& reg, entt::entity entity)
    {
        if constexpr (detail::component_has_creator<Type, TargetType>)
        {
            Type::OnEntityConstruct(reg, entity);
        }
        else if constexpr (detail::component_has_creator_target<Type, TargetType>)
        {
            TargetType* pYrObject = reg.get<YrEntityComponent<TargetType>>(entity).yrObject;
            Type::OnEntityConstruct(reg, entity, pYrObject);
        }
        else if constexpr (detail::component_has_template_creator<Type, TargetType>)
        {
            Type::template OnEntityConstruct<TargetType>(reg, entity);
        }
        else
        {
            reg.emplace<Type>(entity);
        }
    }

    template<typename Type, typename... TargetType>
    static void RegisterComponentInstantiation()
    {
        if constexpr (sizeof...(TargetType) == 1u)
        {
            (gEntt->on_construct<YrEntityComponent<TargetType>>().template connect<&CreateComponent<Type, TargetType>>(), ...);
        }
        else
        {
            (RegisterComponentInstantiation<Type, TargetType>(), ...);
        }
    }
};

#endif
