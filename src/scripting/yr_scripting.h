#pragma once
#include "yr/yr_extbase.h"

CLASS(YrExtension)
class YrScriptingModule final : public IYrExtension
{
private:
    virtual void Startup() override;
    virtual void Shutdown() override;
};
