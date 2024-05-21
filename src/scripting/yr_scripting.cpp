#include <yr/yr_all_events.h>
#include "javascript/js_env.h"
#include <imgui.h>
static void Update()
{
    if (gJsEnv)
    {
        gJsEnv->InspectorTick();
        gJsEnv->LogicTick();
    }
}

REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, Update)
REGISTER_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent, Update)

REGISTER_YR_HOOK_EVENT_LISTENER(YrTerminateEvent, []() {
    gJsEnv.reset();
})
