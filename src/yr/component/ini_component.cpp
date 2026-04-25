#include "yr/component/ini_component.h"
#include <TechnoTypeClass.h>
#include <TerrainTypeClass.h>
#include <BulletTypeClass.h>
#include <AnimTypeClass.h>
#include <HouseTypeClass.h>
#include <SuperWeaponTypeClass.h>
#include <WeaponTypeClass.h>
#include <WarheadTypeClass.h>
#include <boost/algorithm/string.hpp>
struct ThemeControl;

static thread_local CCINIClass* gCurrentLoadingIni = nullptr;
static std::map<void*, std::function<void(IniReader&)>> gLoadAllCallbacks;
static std::map<void*, std::function<void()>> gClearCallbacks;
static std::map<void*, std::function<void(IniReader&)>> gGlobalLoadCallbacks;
static std::map<void*, std::function<void()>> gGlobalClearCallbacks;
static std::map<entt::id_type, std::map<std::string, std::function<void*(const char*)>>> gPolymorphicAutoLoadFactories;

CCINIClass* IniComponentLoader::SetCurrentLoadingIni(CCINIClass* pIni)
{
    CCINIClass* previous = gCurrentLoadingIni;
    gCurrentLoadingIni = pIni;
    return previous;
}

void IniComponentLoader::RegisterPolymorphicAutoLoadFactory(
    entt::id_type baseType,
    std::string_view derivedTypeName,
    std::function<void*(const char* name)> factory)
{
    gPolymorphicAutoLoadFactories[baseType][std::string(derivedTypeName)] = std::move(factory);
}

void* detail::TryFindPolymorphicAutoLoad(const entt::type_info& baseType, const char* sectionName)
{
    if (!gCurrentLoadingIni || !sectionName || !*sectionName)
    {
        return nullptr;
    }

    IniReader reader { gCurrentLoadingIni };
    if (!reader.ReadString(sectionName, "$Type"))
    {
        return nullptr;
    }
    const std::string typeName = boost::trim_copy(std::string(reader.value()));

    auto factoryGroup = gPolymorphicAutoLoadFactories.find(baseType.hash());
    if (factoryGroup == gPolymorphicAutoLoadFactories.end())
    {
        return nullptr;
    }

    auto factory = factoryGroup->second.find(typeName);
    if (factory == factoryGroup->second.end())
    {
        gLogger->error("could not parse {}[{}]: unsupported $Type {}", baseType.name(), sectionName, typeName);
        return nullptr;
    }

    return factory->second(sectionName);
}

void IniComponentLoader::RegisterLoadAllCallback(void* id, std::function<void(IniReader&)> load, std::function<void()> clear)
{
    if (gLoadAllCallbacks.contains(id))
        return;
    
    gLoadAllCallbacks[id] = load;
    gClearCallbacks[id] = clear;
}

void IniComponentLoader::RegisterGlobalLoadCallback(void* id, std::function<void(IniReader&)> load, std::function<void()> clear)
{
    if (gGlobalLoadCallbacks.contains(id))
        return;

    gGlobalLoadCallbacks[id] = load;
    gGlobalClearCallbacks[id] = clear;
}

template<typename T>
static std::vector<IniComponentLoader::LoadingFunc<T>>& GetLoadingFuncList() {
    static std::vector<IniComponentLoader::LoadingFunc<T>> list;
    return list;
} 

#define IMPL_ON_LOADING(Class) \
template<> \
void IniComponentLoader::OnLoading<Class>(CCINIClass* pIni, Class* loadingObj) { \
    IniReader reader {pIni}; \
    auto& list = GetLoadingFuncList<Class>(); \
    for (auto func : list) { \
        func(reader, loadingObj); \
    } \
}

#define IMPL_REGISTER_LOADING_FUNC(Class) \
template<> \
YREXTCORE_API static void IniComponentLoader::RegisterLoadingFunc<Class>(LoadingFunc<Class> loadingFunc) { \
    auto& list = GetLoadingFuncList<Class>(); \
    list.push_back(loadingFunc); \
}

#define IMPL_ON_LOADING_AND_REGISTER_FUNC(Class) IMPL_ON_LOADING(Class) IMPL_REGISTER_LOADING_FUNC(Class)

IMPL_ON_LOADING_AND_REGISTER_FUNC(TechnoTypeClass);
IMPL_ON_LOADING_AND_REGISTER_FUNC(TerrainTypeClass);
IMPL_ON_LOADING_AND_REGISTER_FUNC(BulletTypeClass);
IMPL_ON_LOADING_AND_REGISTER_FUNC(AnimTypeClass);
IMPL_ON_LOADING_AND_REGISTER_FUNC(HouseTypeClass);
IMPL_ON_LOADING_AND_REGISTER_FUNC(SuperWeaponTypeClass);
IMPL_ON_LOADING_AND_REGISTER_FUNC(WeaponTypeClass);
IMPL_ON_LOADING_AND_REGISTER_FUNC(WarheadTypeClass);
IMPL_ON_LOADING_AND_REGISTER_FUNC(ThemeControl);

YREXTCORE_API void IniComponentLoader::RegisterAbstractTypeLoadingFunc(AbstractType targetType, std::function<void(IniReader* reader, AbstractTypeClass* loadingObj)> loadingFunc)
{
    switch (targetType)
    {
    case AbstractType::UnitType:
    case AbstractType::InfantryType:
    case AbstractType::BuildingType:
    case AbstractType::AircraftType:
        IniComponentLoader::RegisterLoadingFunc<TechnoTypeClass>(
            [loadingFunc = std::move(loadingFunc)](IniReader& reader, auto type) { loadingFunc(&reader, type); });
        break;
    case AbstractType::TerrainType:
        IniComponentLoader::RegisterLoadingFunc<TerrainTypeClass>(
            [loadingFunc = std::move(loadingFunc)](IniReader& reader, auto type) { loadingFunc(&reader, type); });
        break;
    case AbstractType::BulletType:
        IniComponentLoader::RegisterLoadingFunc<BulletTypeClass>(
            [loadingFunc = std::move(loadingFunc)](IniReader& reader, auto type) { loadingFunc(&reader, type); });
        break;
    case AbstractType::AnimType:
        IniComponentLoader::RegisterLoadingFunc<AnimTypeClass>(
            [loadingFunc = std::move(loadingFunc)](IniReader& reader, auto type) { loadingFunc(&reader, type); });
        break;
    case AbstractType::HouseType:
        IniComponentLoader::RegisterLoadingFunc<HouseTypeClass>(
            [loadingFunc = std::move(loadingFunc)](IniReader& reader, auto type) { loadingFunc(&reader, type); });
        break;
    case AbstractType::SuperWeaponType:
        IniComponentLoader::RegisterLoadingFunc<SuperWeaponTypeClass>(
            [loadingFunc = std::move(loadingFunc)](IniReader& reader, auto type) { loadingFunc(&reader, type); });
        break;
    case AbstractType::WeaponType:
        IniComponentLoader::RegisterLoadingFunc<WeaponTypeClass>(
            [loadingFunc = std::move(loadingFunc)](IniReader& reader, auto type) { loadingFunc(&reader, type); });
        break;
    case AbstractType::WarheadType:
        IniComponentLoader::RegisterLoadingFunc<WarheadTypeClass>(
            [loadingFunc = std::move(loadingFunc)](IniReader& reader, auto type) { loadingFunc(&reader, type); });
        break;
    default:
        gLogger->error("cannot register ini loading func for abstract type {}", static_cast<unsigned int>(targetType));
        break;
    }
}

#include "yr/yr_all_events.h"
#include "ini_component.h"
DEFINE_YR_HOOK_EVENT_LISTENER(YrRulesLoadAfterTypeDataEvent)
{
    IniReader reader {E->pIni};
    for (auto&& [id, callback] : gGlobalLoadCallbacks)
    {
        callback(reader);
    }
    for (auto&& [id, callback] : gLoadAllCallbacks)
    {
        callback(reader);
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneExitEvent)
{
    for (auto&& [id, callback] : gClearCallbacks)
    {
        callback();
    }
    for (auto&& [id, callback] : gGlobalClearCallbacks)
    {
        callback();
    }
    gClearCallbacks.clear();
    gLoadAllCallbacks.clear();
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoTypeLoadIniEvent) {
    IniComponentLoader::OnLoading(E->pIni, E->pTechnoType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTerrainTypeLoadIniEvent) {
    IniComponentLoader::OnLoading(E->pIni, E->pTerrainType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletTypeLoadIniEvent) {
    IniComponentLoader::OnLoading(E->pIni, E->pBulletType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrAnimTypeLoadIniEvent) {
    IniComponentLoader::OnLoading(E->pIni, E->pAnimType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseTypeLoadIniEvent) {
    IniComponentLoader::OnLoading(E->pIni, E->pHouseType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperWeaponTypeLoadIniEvent) {
    IniComponentLoader::OnLoading(E->pIni, E->pSuperWeaponType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrWeaponTypeLoadIniEvent) {
    IniComponentLoader::OnLoading(E->pIni, E->pWeaponType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrWarheadTypeLoadIniEvent) {
    IniComponentLoader::OnLoading(E->pIni, E->pWarheadType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrThemeLoadIniEvent) {
    IniComponentLoader::OnLoading(E->pIni, E->themeCtrl);
}
