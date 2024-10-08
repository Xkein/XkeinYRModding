#pragma once

#include "physics/jolt/jolt.h"
class TerrainBody;

class Physics
{
public:
    static void Init();
    static void Destroy();
    static void BeginTick();
    static void EndTick();

    static void LoadWorld();
    static void EnterWorld();
    static void ExitWorld();

    static XKEINEXT_API TerrainBody* gTerrainBody;
};

extern XKEINEXT_API JPH::JobSystem*		                gJobSystem;
extern XKEINEXT_API JPH::PhysicsSystem*	                gPhysicsSystem;
extern XKEINEXT_API JPH::BodyInterface*	                gBodyInterface;
extern XKEINEXT_API JPH::BodyInterface*	                gBodyInterfaceNoLock;
extern XKEINEXT_API JPH::TempAllocator*                 gTempAllocator;
extern XKEINEXT_API JPH::BroadPhaseLayerInterface*      gBroadPhaseLayerInterface;
extern XKEINEXT_API JPH::ObjectVsBroadPhaseLayerFilter* gObjectVsBroadPhaseLayerFilter;
extern XKEINEXT_API JPH::ObjectLayerPairFilter*         gObjectLayerPairFilter;
