#include "yr/component/ini_component.h"

class TerrainTypeClass;
class BulletTypeClass;
class AnimTypeClass;
class HouseTypeClass;
class SuperWeaponTypeClass;
class WeaponTypeClass;
class WarheadTypeClass;
struct ThemeControl;

static std::map<void*, std::function<void(IniReader&)>> gLoadAllCallbacks;
static std::map<void*, std::function<void()>> gClearCallbacks;
void IniComponentLoader::RegisterLoadAllCallback(void* id, std::function<void(IniReader&)> load, std::function<void()> clear)
{
    if (gLoadAllCallbacks.contains(id))
        return;
    
    gLoadAllCallbacks[id] = load;
    gClearCallbacks[id] = clear;
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

#include "yr/yr_all_events.h"
DEFINE_YR_HOOK_EVENT_LISTENER(YrRulesLoadAfterTypeDataEvent)
{
    IniReader reader {E->pIni};
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