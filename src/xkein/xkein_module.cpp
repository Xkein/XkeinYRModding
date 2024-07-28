#include "xkein/xkein_module.h"
#include "codegen/XkeinExt.gen.h"
#include "physics/physics.h"
#include "audio/audio.h"

void YrXkeinModule::Startup()
{
    __Gen_Type_XkeinExt::Register();

    Physics::Init();
    AudioSystem::Init();
}

void YrXkeinModule::Shutdown()
{
    __Gen_Type_XkeinExt::Unregister();
    
    Physics::Destroy();
    AudioSystem::Destroy();
}
