#pragma once

#include <core/reflection/macro.h>

// Extension abstract base, remember to add meta info -- 'CLASS(YrExtension)' and 'add_rules("codegen-cpp")'
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
