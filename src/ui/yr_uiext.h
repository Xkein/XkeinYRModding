#pragma once
#include "yr/yr_extbase.h"

CLASS(YrExtension)
class YrExtUIModule final : public IYrExtension
{
public:
    static void UIMainThread();
    static void InitUIModule();
    static void DestroyUIModule();
    
private:
    virtual void Startup() override;
    virtual void Shutdown() override;
};
