#pragma once

#include <core/reflection/macro.h>

// Extension abstract base, remember to add meta info -- 'CLASS(YrExtension)' and 'add_rules("codegen-cpp")'
// It is not necessary to implement this. An alternative is RAII_Invoker
// Is is not a final design, may be change in the future
class IYrExtension
{
    friend class ExtensionManager;

protected:
    virtual void Startup() {}
    virtual void PostLoad() {}
    virtual void PreUnload() {}
    virtual void Shutdown() {}

    virtual bool SupportsDynamicReloading()
    {
        return true;
    }

};
