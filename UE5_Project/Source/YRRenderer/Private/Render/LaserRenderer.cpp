// LaserRenderer.cpp
#include "Render/LaserRenderer.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ALaserRenderer::ALaserRenderer()
{
    PrimaryActorTick.bCanEverTick = true;
    NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraLaser"));
    RootComponent = NiagaraComp;
}

void ALaserRenderer::AddLaser(const FLaserRenderData& Laser)
{
    ActiveLasers.Add(Laser);
    // TODO: 激活 Niagara System 对应此 Laser
    // UNiagaraFunctionLibrary::SpawnSystemAtLocation(...)
}

void ALaserRenderer::ClearLasers()
{
    ActiveLasers.Empty();
}

void ALaserRenderer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 清理过期的 Laser
    for (int32 i = ActiveLasers.Num() - 1; i >= 0; --i)
    {
        ActiveLasers[i].Duration -= DeltaTime;
        if (ActiveLasers[i].Duration <= 0.0f)
            ActiveLasers.RemoveAt(i);
    }
}