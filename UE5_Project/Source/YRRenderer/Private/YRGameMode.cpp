// YRGameMode.cpp
#include "YRGameMode.h"
#include "Mirror/MirrorECS.h"
#include "Transport/DataReceiver.h"
#include "Camera/CameraComponent.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/World.h"

AYRGameMode::AYRGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 1.0f / 60.0f; // 同步到 60fps
}

void AYRGameMode::BeginPlay()
{
    Super::BeginPlay();

    // 创建正交相机用于等距渲染
    IsoCamera = NewObject<UCameraComponent>(this);
    IsoCamera->RegisterComponent();
    IsoCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    IsoCamera->SetWorldLocation(FVector(0, -10000, 5000));
    IsoCamera->SetWorldRotation(FRotator(-45, 0, 0)); // 等距视角近似
    IsoCamera->OrthoWidth = 4096;

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
        PC->SetViewTarget(this);

    // 创建迷雾后处理体积
    FogVolume = GetWorld()->SpawnActor<APostProcessVolume>();
    if (FogVolume)
    {
        FogVolume->bUnbound = true;
        // Fog 参数由 FogPostProcess 蓝图或 Material 控制
    }
}

void AYRGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // 接收并应用帧数据
    FFramePacket Packet;
    if (FDataReceiver::Get().TryReceiveFrame(Packet))
    {
        FMirrorECS::Get().ApplyFramePacket(Packet);
    }
}