#pragma once
#include "core/reflection/reflection.h"
#include "runtime/ecs/entt.h"
#include "yr/api/yr_entity.h"
#include "yr/parse/ini_reader.h"
#include <entt/core/type_info.hpp>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <entt/meta/factory.hpp>

class AbstractTypeClass;

using namespace entt::literals;
namespace detail
{
    template<typename Type>
    concept ini_component_has_after = requires(Type& com, IniReader& parser, const char* pSection, const char* pKey) {
        com.AfterLoadIni(parser, pSection, pKey);
    };
}

CLASS(BindJs)
class IniComponentLoader
{
public:
    template<typename T>
    using LoadingFunc = std::function<void(IniReader& reader, T* loadingObj)>;

    /// @brief Called when loading game types or loading a savegame.
    /// @note To reduce the size of savegames, we load components again when loading a savegame.
    template<typename T>
    static void OnLoading(CCINIClass* pIni, T* loadingObj);

    template<typename T>
    FORCEINLINE static T* GetGlobalIniComponent();

    template<typename T, typename TCom>
    static void RegisterLoadingComponent();
    template<typename T>
    YREXTCORE_API static void RegisterLoadingFunc(LoadingFunc<T> loadingFunc);
    
    FUNCTION()
    YREXTCORE_API static void RegisterAbstractTypeLoadingFunc(AbstractType targetType, std::function<void(IniReader* reader, AbstractTypeClass* loadingObj)> loadingFunc);

    template<typename T>
    static bool Load(IniReader& parser, const char* pSection, const char* pKey, T& value);

    template<typename Type, bool (*Func)(Type&, IniReader&, const char*)>
    static void RegisterLoader(entt::meta_factory<Type>& factory);

    template<typename Type>
    static void RegisterGlobalIniComponent(entt::meta_factory<Type>& factory, std::string_view pSection);

    template<typename Type>
    static void RegisterAutoLoad(entt::meta_factory<Type>& factory);

    template<typename BaseType, typename DerivedType>
    static void RegisterPolymorphicAutoLoad();

    template<typename Type, typename TargetType>
    static void LoadComponent(IniReader& reader, TargetType* pObject);
private:
    YREXTCORE_API static CCINIClass* SetCurrentLoadingIni(CCINIClass* pIni);
    YREXTCORE_API static void RegisterPolymorphicAutoLoadFactory(
        entt::id_type baseType,
        std::string_view derivedTypeName,
        std::function<void*(const char* name)> factory);
    YREXTCORE_API static void RegisterLoadAllCallback(void* id, std::function<void(IniReader&)> load, std::function<void()> clear);
    YREXTCORE_API static void RegisterGlobalLoadCallback(void* id, std::function<void(IniReader&)> load, std::function<void()> clear);
};

namespace detail
{
    template<typename Type>
    struct GlobalIniComponentLoader
    {
        inline static std::unique_ptr<Type> Instance;
        inline static Type* CurrentInstance = nullptr;
        inline static std::string SectionName;
        inline static bool Registered = false;

        static Type* Get()
        {
            if (!Instance)
            {
                Instance = std::make_unique<Type>();
                CurrentInstance = Instance.get();
            }
            return CurrentInstance;
        }

        static void LoadAll(IniReader& reader)
        {
            if (SectionName.empty())
            {
                return;
            }

            Type* ptr = Get();
            IniComponentLoader::Load(reader, SectionName.c_str(), nullptr, *ptr);
        }

        static void Clear()
        {
            Instance.reset();
            CurrentInstance = nullptr;
        }
    };
}

template<typename T, typename TCom>
void IniComponentLoader::RegisterLoadingComponent()
{
    RegisterLoadingFunc<T>(&LoadComponent<TCom, T>);
}

template<typename T>
bool IniComponentLoader::Load(IniReader& parser, const char* pSection, const char* pKey, T& value)
{
    const auto previousIni = SetCurrentLoadingIni(parser.GetIni());

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
        SetCurrentLoadingIni(previousIni);
        return true;
    }
    if (!hasLoader) {
        gLogger->error("could not load {} for [{}]->{}", typeid(T).name(), pSection, pKey);
    }
    SetCurrentLoadingIni(previousIni);
    return false;
}

template<typename Type, bool (*Func)(Type&, IniReader&, const char*)>
void IniComponentLoader::RegisterLoader(entt::meta_factory<Type>& factory)
{
    factory.func<Func>("__LoadIniComponent"_hs);
}

template<typename Type>
void IniComponentLoader::RegisterGlobalIniComponent(entt::meta_factory<Type>& factory, std::string_view pSection)
{
    detail::GlobalIniComponentLoader<Type>::SectionName = pSection;
    detail::GlobalIniComponentLoader<Type>::Registered = true;
    RegisterGlobalLoadCallback(&detail::GlobalIniComponentLoader<Type>::CurrentInstance,
        &detail::GlobalIniComponentLoader<Type>::LoadAll,
        &detail::GlobalIniComponentLoader<Type>::Clear);
    factory.func<&detail::GlobalIniComponentLoader<Type>::Get>("__GetGlobalIniComponent"_hs);
}

template<typename Type>
void IniComponentLoader::RegisterAutoLoad(entt::meta_factory<Type>& factory)
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

    factory.func<&AutoLoad::FindOrAllocate>("__FindOrAllocate"_hs);
}

template<typename BaseType, typename DerivedType>
void IniComponentLoader::RegisterPolymorphicAutoLoad()
{
    entt::meta_type derivedType = entt::resolve<DerivedType>();
    ClassMeta* classMeta = derivedType.custom();
    const char* typeName = classMeta ? classMeta->name : derivedType.info().name().data();

    RegisterPolymorphicAutoLoadFactory(
        entt::type_id<BaseType>().hash(),
        typeName,
        [](const char* name) -> void* {
            entt::meta_func func = entt::resolve<DerivedType>().func("__FindOrAllocate"_hs);
            if (!func)
            {
                return nullptr;
            }

            entt::meta_any any = func.invoke({}, name);
            if (!any)
            {
                return nullptr;
            }

            DerivedType* ptr = any.cast<DerivedType*>();
            return static_cast<BaseType*>(ptr);
        });
}

template<typename Type, typename TargetType>
void IniComponentLoader::LoadComponent(IniReader& reader, TargetType* pObject)
{
    const char* pID  = pObject->ID;
    Type* pCom = GetYrComponent<Type>(pObject);
    if (pCom == nullptr)
    {
        gLogger->error("could not get {} for {}[{}]", entt::type_id<Type>().name(), entt::type_id<TargetType>().name(), pID);
        return;
    }
    IniComponentLoader::Load(reader, pID, nullptr, *pCom);
}

template<typename T>
T* IniComponentLoader::GetGlobalIniComponent()
{
    if (!detail::GlobalIniComponentLoader<T>::Registered)
    {
        gLogger->error("could not get global ini component {}: not registered with IniSection", typeid(T).name());
        return nullptr;
    }
    return detail::GlobalIniComponentLoader<T>::Get();
}
