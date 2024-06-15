#pragma once
#include "yr/yr_extbase.h"

CLASS(YrExtension)
class YrExtUIModule final : public IYrExtension
{
private:
    virtual void Startup();
    virtual void Shutdown();
};
