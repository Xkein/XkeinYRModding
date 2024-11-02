#pragma once
#include "yr/yr_extbase.h"

CLASS(YrExtension)
class YrExtUIModule final : public IYrExtension
{
public:
    static void UIMainThread();
    
private:
    virtual void Startup() override;
    virtual void Shutdown() override;
};
