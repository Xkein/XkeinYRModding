#include "xkein/xkein_module.h"
#include "codegen/XkeinExt.gen.h"
#include "physics/physics.h"
#include "audio/audio.h"
#include "scripting/engine.h"

void YrXkeinModule::Startup()
{
    __Gen_Type_XkeinExt::Register();

    Physics::Init();
    AudioSystem::Init();
    gEngine = new Engine();
    gEngine->Start();
}

void YrXkeinModule::Shutdown()
{
    if (gEngine) {
        delete gEngine;
        gEngine = nullptr;
    }

    Physics::Destroy();
    AudioSystem::Destroy();

    __Gen_Type_XkeinExt::Unregister();
}
