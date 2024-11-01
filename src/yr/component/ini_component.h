#pragma once
#ifndef __HEADER_TOOL__
#include "core/reflection/reflection.h"
#include "runtime/ecs/entt.h"
#include "yr/api/yr_entity.h"
#include "yr/parse/ini_reader.h"
#include <entt/meta/factory.hpp>
using namespace entt::literals;
namespace detail
{
    template<typename Type>
    concept ini_component_has_after = requires(Type& com, IniReader& parser, const char* pSection, const char* pKey) {
        com.AfterLoadIni(parser, pSection, pKey);
    };

    template<typename Type>
    concept ini_component_has_container = requires() {
        Type::GetIniContainer();
    };
    
    template<typename Type>
    concept ini_has_yr_find = requires() {
        { Type::Find("") } -> std::convertible_to<Type*>;
    };
}

struct IniComponentLoader
{
    template<typename T>
    static bool Load(IniReader& parser, const char* pSection, const char* pKey, T& value)
    {
        bool hasLoader = false;
        bool success = false;
        if constexpr (IsParserImplemented<T>)
        {
            hasLoader = true;
            success = parser.Read(pSection, pKey, value);
        }
        entt::meta_type type = entt::resolve<T>();
        if (type)
        {
            entt::meta_func func = type.func("LoadIniComponent"_hs);
            if (func)
            {
                hasLoader = true;
                success = func.invoke(value, parser, pSection).cast<bool>();
            }
        }
        if (success) {
            if constexpr (detail::ini_component_has_after<T>) {
                value.AfterLoadIni(parser, pSection, pKey);
            }
            return true;
        }
        if (!hasLoader) {
            gLogger->error("could not load {} for [{}]->{}", typeid(T).name(), pSection, pKey);
        }
        return false;
    }

    template<typename Type, bool (*Func)(Type&, IniReader&, const char*)>
    static void Register(entt::meta_factory<Type>& factory)
    {
        factory.func<Func>("LoadIniComponent"_hs).prop("name"_hs, "LoadIniComponent");
    }

    template<typename Type, typename TargetType>
    static void LoadComponent(TargetType* pObject, CCINIClass* pIni)
    {
        const char* pID  = pObject->ID;
        Type* pCom = GetYrComponent<Type>(pObject);
        if (pCom == nullptr)
        {
            gLogger->error("could not get {} for {}[{}]", typeid(Type).name(), typeid(TargetType).name(), pID);
            return;
        }
        IniReader reader {pIni};
        IniComponentLoader::Load(reader, pID, nullptr, *pCom);
    }
    
    template<typename T>
    static bool Load(IniReader& parser, const char* pSection, const char* pKey, const T*& value)
    {
        return Load(parser, pSection, const_cast<T*&>(value));
    }

    template<typename T>
    static bool Load(IniReader& parser, const char* pSection, const char* pKey, T*& value)
    {
        std::string_view name;
        if(!Load(parser, pSection, pKey, name))
            return false;

        if (name.empty())
            return true;

        if constexpr (detail::ini_component_has_container<T>)
        {
            auto& container = T::GetIniContainer();

            bool allocated = false;
            T* ptr = container.FindOrAllocate(name.data(), allocated);
            if (!ptr)
                return false;

            value = ptr;

            if (allocated)
            {
                Load(parser, name.data(), nullptr, *value);
            }

            return true;
        }
        else if constexpr(detail::ini_has_yr_find<T>)
        {
            T* ptr = T::Find(name.data());
            if (!ptr)
                return false;
            value = ptr;
            
            return true;
        }
        else {
            static_assert(false, "could not load this pointer!");
        }
    }
};
#endif
