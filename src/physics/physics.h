#pragma once

#include "physics/jolt/jolt.h"
class TerrainHeightMap;

class Physics
{
public:
    static void Init();
    static void Destroy();
    static void BeginTick();
    static void EndTick();

    static void InitWorld();
    static void DestroyWorld();

    static XKEINEXT_API TerrainHeightMap* gTerrainHeightMap;
};

extern XKEINEXT_API JPH::JobSystem*		                gJobSystem;
extern XKEINEXT_API JPH::PhysicsSystem*	                gPhysicsSystem;
extern XKEINEXT_API JPH::BodyInterface*	                gBodyInterface;
extern XKEINEXT_API JPH::TempAllocator*                 gTempAllocator;
extern XKEINEXT_API JPH::BroadPhaseLayerInterface*      gBroadPhaseLayerInterface;
extern XKEINEXT_API JPH::ObjectVsBroadPhaseLayerFilter* gObjectVsBroadPhaseLayerFilter;
extern XKEINEXT_API JPH::ObjectLayerPairFilter*         gObjectLayerPairFilter;
