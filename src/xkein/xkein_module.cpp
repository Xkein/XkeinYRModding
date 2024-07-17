#include "xkein/xkein_module.h"
#include "codegen/XkeinExt.gen.h"
void YrXkeinModule::Startup()
{
    __Gen_Type_XkeinExt::Register();
}

void YrXkeinModule::Shutdown()
{
    __Gen_Type_XkeinExt::Unregister();
}
