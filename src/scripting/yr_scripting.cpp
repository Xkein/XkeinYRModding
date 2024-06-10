#include <yr/yr_all_events.h>
#include "scripting/yr_scripting.h"
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

void YrScriptingModule::Startup()
{
    gJsEnv = std::make_shared<JsEnv>();
}

void YrScriptingModule::Shutdown()
{
    gJsEnv.reset();
}
