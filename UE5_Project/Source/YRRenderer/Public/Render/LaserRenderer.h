// LaserRenderer.h - 激光/闪电渲染器 (Niagara)
#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "LaserRenderer.generated.h"

USTRUCT()
struct FLaserRenderData
{
    GENERATED_BODY()

    UPROPERTY() FVector Start;
    UPROPERTY() FVector End;
    UPROPERTY() FColor  InnerColor;
    UPROPERTY() FColor  OuterColor;
    UPROPERTY() uint8   Type = 0;
    UPROPERTY() float   Duration = 1.0f;
};

UCLASS()
class YRRENDERER_API ALaserRenderer : public AActor
{
    GENERATED_BODY()

public:
    ALaserRenderer();

    void AddLaser(const FLaserRenderData& Laser);
    void ClearLasers();
    virtual void Tick(float DeltaTime) override;

    UPROPERTY()
    class UNiagaraComponent* NiagaraComp;

private:
    TArray<FLaserRenderData> ActiveLasers;
};