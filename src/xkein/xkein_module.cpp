#include "xkein/xkein_module.h"
#include "codegen/XkeinExt.gen.h"
#include "codegen/gainput.gen.h"
#include "codegen/Wwise.gen.h"
#include "physics/physics.h"
#include "audio/audio.h"
#include "xkein/engine.h"
#include <Unsorted.h>

#define REGISTER_JS_MODULE(Module) \
    extern void __JsRegister_##Module(); \
    __JsRegister_##Module();

void EnsureStart()
{
    if (Game::hWnd && !gEngine)
    {
        gEngine = new Engine();
        gEngine->Start();
    }
}

void YrXkeinModule::Startup()
{
    __Gen_Type_gainput::Register();
    __Gen_Type_Wwise::Register();
    __Gen_Type_XkeinExt::Register();

    REGISTER_JS_MODULE(YRpp);
    REGISTER_JS_MODULE(YrExtCore);
    REGISTER_JS_MODULE(Wwise);
    REGISTER_JS_MODULE(gainput);
    REGISTER_JS_MODULE(XkeinExt);

    EnsureStart();
}

void YrXkeinModule::Shutdown()
{
    if (gEngine) {
        delete gEngine;
        gEngine = nullptr;
    }

    __Gen_Type_XkeinExt::Unregister();
    __Gen_Type_Wwise::Unregister();
    __Gen_Type_gainput::Unregister();
}

#include "yr/event/windows_event.h"
#include "yr/event/general_event.h"
#include "yr/event/ui_event.h"

REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, EnsureStart);
REGISTER_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent, EnsureStart);
REGISTER_YR_HOOK_EVENT_LISTENER(YrAfterCreateWindoweEvent, EnsureStart);
