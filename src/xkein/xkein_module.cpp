#include "xkein/xkein_module.h"
#include "codegen/XkeinExt.gen.h"
#include "physics/physics.h"
#include "audio/audio.h"
#include "xkein/engine.h"
#include <Unsorted.h>

#define REGISTER_JS_MODULE(Module) \
    extern void __JsRegister_##Module(); \
    __JsRegister_##Module();

void YrXkeinModule::Startup()
{
    __Gen_Type_XkeinExt::Register();

    REGISTER_JS_MODULE(YRpp);
    REGISTER_JS_MODULE(YrExtCore);
    REGISTER_JS_MODULE(XkeinExt);

    gEngine = new Engine();
    if (Game::hWnd)
    {
        gEngine->Start();
    }
}

void YrXkeinModule::Shutdown()
{
    if (gEngine) {
        delete gEngine;
        gEngine = nullptr;
    }

    __Gen_Type_XkeinExt::Unregister();
}

#include "yr/event/windows_event.h"
#include "yr/event/general_event.h"
#include "yr/event/ui_event.h"

void EnsureStart()
{
    if (gEngine && !gEngine->started)
    {
        gEngine->Start();
    }
}

REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, EnsureStart);
REGISTER_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent, EnsureStart);
REGISTER_YR_HOOK_EVENT_LISTENER(YrAfterCreateWindoweEvent, EnsureStart);
