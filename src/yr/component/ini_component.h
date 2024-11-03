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
            entt::meta_func func = type.func("__LoadIniComponent"_hs);
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
    static void RegisterLoader(entt::meta_factory<Type>& factory)
    {
        factory.func<Func>("__LoadIniComponent"_hs).prop("name"_hs, "__LoadIniComponent");
    }

    template<typename Type>
    static void RegisterAutoLoad(entt::meta_factory<Type>& factory)
    {
        static std::map<std::string, std::unique_ptr<Type>> items;
        struct AutoLoad {
            static void LoadAll(IniReader& reader) {
                for (auto&& [name, ptr] : items)
                {
                    IniComponentLoader::Load(reader, name.c_str(), nullptr, *ptr);
                }
            }
            static void Clear() {
                items.clear();
            }
            static Type* FindOrAllocate(const char* name) {
                auto iter = items.find(name);
                if (iter != items.end()) {
                    return iter->second.get();
                }

                IniComponentLoader::RegisterLoadAllCallback(&items, &LoadAll, &Clear);

                auto& ptr = items[name];
                ptr = std::make_unique<Type>();
                return ptr.get();
            }
        };

        factory.func<&AutoLoad::FindOrAllocate>("__FindOrAllocate"_hs).prop("name"_hs, "__FindOrAllocate");
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
private:
    YREXTCORE_API static void RegisterLoadAllCallback(void* id, std::function<void(IniReader&)> load, std::function<void()> clear);
};
#endif
