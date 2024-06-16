#include "scripting/yr_scripting.h"
#include "scripting/javascript/js_env.h"
#include "scripting/engine.h"
#include <imgui.h>
#include <yr/yr_all_events.h>

#include "codegen/YrScripting.gen.h"
void YrScriptingModule::Startup()
{
    __Gen_Type_YrScripting::Register();
    gJsEnv = std::make_shared<JsEnv>();
    gEngine->Start();
}

void YrScriptingModule::Shutdown()
{
    gEngine->Exit();
    gJsEnv.reset();
    __Gen_Type_YrScripting::Unregister();
}
