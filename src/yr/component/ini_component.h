#pragma once
#include "core/reflection/reflection.h"
#include "core/tool/type_traits.hpp"
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
    inline static bool Load(IniReader& parser, const char* pSection, const char* pKey, T& value);

    template<typename Type, bool (*Func)(Type&, IniReader&, const char*, const char*)>
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

    // 非指针且无 Parser 时走 __LoadIniComponent（递归加载子属性）
    // 支持两种 INI 配置方式：
    //   方式1（点分键展开）：Container.SubField = Value（在当前 section 下用 pKey 作为前缀读取）
    //   方式2（section 引用）：Container = SectionName，然后去 [SectionName] 节下读取子属性
    // 指针类型只走 Parser，不递归进入指针指向对象的子属性
    if constexpr (!std::is_pointer_v<T> && !IsParserImplemented<T>)
    {
        entt::meta_type type = entt::resolve<T>();

        // 加载基类和自身的 INI 属性，section/key 可指定
        auto doLoadIniComponent = [&](const char* section, const char* key) {
            if (!type) return;

            // Recursively load base classes' INI first (from root to derived)
            // This ensures inherited INI properties are loaded for each level in the hierarchy.
            auto loadBases = [&](auto& self, entt::meta_type metaType) -> void {
                for (auto&& [_, baseType] : metaType.base())
                {
                    // Recurse into grandparent first
                    self(self, baseType);

                    // Load this base type's own INI properties
                    entt::meta_func baseFunc = baseType.func("__LoadIniComponent"_hs);
                    if (baseFunc)
                    {
                        hasLoader = true;
                        // Cast the derived reference to the base type via entt meta system
                        entt::meta_any ref = entt::meta_any{std::ref(value)};
                        if (entt::meta_any baseRef = ref.allow_cast(baseType); baseRef)
                        {
                            success |= baseFunc.invoke(std::move(baseRef), parser, section, key).template cast<bool>();
                        }
                    }
                }
            };
            loadBases(loadBases, type);

            entt::meta_func func = type.func("__LoadIniComponent"_hs);
            if (func)
            {
                hasLoader = true;
                success |= func.invoke(value, parser, section, key).cast<bool>();
            }
        };

        // 方式1：点分键展开（pKey 作为前缀，在当前 section 下读取）
        doLoadIniComponent(pSection, pKey);

        // 方式2：如果方式1未读到数据，尝试将 pKey 的值作为 section 名引用
        if (!success && pKey && *pKey)
        {
            if (parser.ReadString(pSection, pKey))
            {
                // 拷贝 section 名，因为后续 ReadString 会覆盖共享 buffer
                std::string sectionName = parser.value();
                if (!sectionName.empty())
                {
                    doLoadIniComponent(sectionName.c_str(), nullptr);
                }
            }
        }
    }

    // std::vector<T> 特殊处理：当元素类型 T 无 Parser 且非指针时，走 section 引用路径
    // INI 写法：FieldName = Section1, Section2, ...
    // 然后对每个 Section 递归加载元素（元素类型需要有 IniComponent）
    if constexpr (is_std_vector_v<T>)
    {
        using ElementType = typename T::value_type;
        if constexpr (!std::is_pointer_v<ElementType> && !IsParserImplemented<ElementType>)
        {
            hasLoader = true;
            if (pKey && *pKey)
            {
                std::string sectionList;
                if (parser.Read(pSection, pKey, sectionList))
                {
                    value.clear();
                    detail::ParserHelper::ReadArray(sectionList, [&](std::string_view token) -> bool {
                        ElementType element{};
                        if (Load(parser, std::string(token).c_str(), nullptr, element))
                        {
                            value.push_back(std::move(element));
                        }
                        return true;
                    });
                    if (!value.empty())
                    {
                        success = true;
                    }
                }
            }
        }
    }

    if constexpr (IsParserImplemented<T>)
    {
        hasLoader = true;
        success |= parser.Read(pSection, pKey, value);
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

template<typename Type, bool (*Func)(Type&, IniReader&, const char*, const char*)>
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
