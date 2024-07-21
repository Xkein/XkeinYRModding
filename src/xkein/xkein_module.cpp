#include "xkein/xkein_module.h"
#include "codegen/XkeinExt.gen.h"
#include "physics/physics.h"

void YrXkeinModule::Startup()
{
    __Gen_Type_XkeinExt::Register();

    Physics::Init();
}

void YrXkeinModule::Shutdown()
{
    __Gen_Type_XkeinExt::Unregister();
    
    Physics::Destroy();
}
