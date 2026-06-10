// YRGameMode.h - 游戏视图的 ViewportClient
// 负责驱动每帧数据接收和 MirrorECS 更新
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "YRGameMode.generated.h"

UCLASS()
class YRRENDERER_API AYRGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AYRGameMode();

    virtual void Tick(float DeltaSeconds) override;
    virtual void BeginPlay() override;

    // 获取用于等距渲染的正交相机
    class UCameraComponent* GetIsoCamera() const { return IsoCamera; }

    UPROPERTY()
    class UCameraComponent* IsoCamera;

    UPROPERTY()
    class APostProcessVolume* FogVolume; // 战争迷雾后处理
};