// YRRendererModule.h - UE5 模块入口
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FYRRendererModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};