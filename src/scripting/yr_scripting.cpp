#include "scripting/yr_scripting.h"
#include "scripting/engine.h"
#include <imgui.h>
#include <yr/yr_all_events.h>

#include "codegen/YrScripting.gen.h"
void YrScriptingModule::Startup()
{
    __Gen_Type_YrScripting::Register();
    gEngine = new Engine();
    gEngine->Start();
}

void YrScriptingModule::Shutdown()
{
    if (gEngine) {
        delete gEngine;
        gEngine = nullptr;
    }
    __Gen_Type_YrScripting::Unregister();
}
