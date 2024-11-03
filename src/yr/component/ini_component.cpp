#include "yr/component/ini_component.h"

static std::map<void*, std::function<void(IniReader&)>> gLoadAllCallbacks;
static std::map<void*, std::function<void()>> gClearCallbacks;
void IniComponentLoader::RegisterLoadAllCallback(void* id, std::function<void(IniReader&)> load, std::function<void()> clear)
{
    if (gLoadAllCallbacks.contains(id))
        return;
    
    gLoadAllCallbacks[id] = load;
    gClearCallbacks[id] = clear;
}

#include "yr/event/general_event.h"
DEFINE_YR_HOOK_EVENT_LISTENER(YrRulesLoadAfterTypeData)
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
