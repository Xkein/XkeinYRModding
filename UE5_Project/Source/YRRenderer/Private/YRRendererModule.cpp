// YRRendererModule.cpp - UE5 模块入口
#include "YRRendererModule.h"
#include "Mirror/MirrorECS.h"
#include "Transport/DataReceiver.h"

#define LOCTEXT_NAMESPACE "FYRRendererModule"

void FYRRendererModule::StartupModule()
{
    FMirrorECS::Get().Initialize();
    FDataReceiver::Get().StartListening();
}

void FYRRendererModule::ShutdownModule()
{
    FDataReceiver::Get().StopListening();
    FMirrorECS::Get().Shutdown();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FYRRendererModule, YRRenderer)