#include "xkein/xkein_module.h"
#include "codegen/XkeinExt.gen.h"
#include "physics/physics.h"
#include "audio/audio.h"
#include "xkein/engine.h"

#define REGISTER_JS_MODULE(Module) \
    extern void __JsRegister_##Module(); \
    __JsRegister_##Module();

void YrXkeinModule::Startup()
{
    __Gen_Type_XkeinExt::Register();

    REGISTER_JS_MODULE(YRpp);
    REGISTER_JS_MODULE(YrExtCore);
    REGISTER_JS_MODULE(YrExtUI);
    REGISTER_JS_MODULE(XkeinExt);

    gEngine = new Engine();
    gEngine->Start();
}

void YrXkeinModule::Shutdown()
{
    if (gEngine) {
        delete gEngine;
        gEngine = nullptr;
    }

    __Gen_Type_XkeinExt::Unregister();
}
