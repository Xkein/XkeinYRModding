#pragma once
#include "yr/yr_extbase.h"

CLASS(YrExtension)
class YrExtUIModule final : IYrExtension
{
private:
    virtual void Startup();
    virtual void Shutdown();
};
