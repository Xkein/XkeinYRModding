#include "physics/physics.h"
#include "physics/layers.h"
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>

XKEINEXT_API JPH::JobSystem*		             gJobSystem;
XKEINEXT_API JPH::PhysicsSystem*	             gPhysicsSystem;
XKEINEXT_API JPH::BodyInterface*	             gBodyInterface;
XKEINEXT_API JPH::TempAllocator*                 gTempAllocator;
XKEINEXT_API JPH::BroadPhaseLayerInterface*      gBroadPhaseLayerInterface;
XKEINEXT_API JPH::ObjectVsBroadPhaseLayerFilter* gObjectVsBroadPhaseLayerFilter;
XKEINEXT_API JPH::ObjectLayerPairFilter*         gObjectLayerPairFilter;

/// Class that determines if two object layers can collide
class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
{
public:
    virtual bool ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const override
    {
        switch (inObject1)
        {
            case PhysicsLayers::NON_MOVING:
                return inObject2 == PhysicsLayers::MOVING;
            case PhysicsLayers::MOVING:
                return inObject2 == PhysicsLayers::NON_MOVING || inObject2 == PhysicsLayers::MOVING;
            default:
                JPH_ASSERT(false);
                return false;
        }
    }
};

/// BroadPhaseLayerInterface implementation
class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
{
public:
    BPLayerInterfaceImpl()
    {
        // Create a mapping table from object to broad phase layer
        mObjectToBroadPhase[PhysicsLayers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
        mObjectToBroadPhase[PhysicsLayers::MOVING]     = BroadPhaseLayers::MOVING;
    }

    virtual uint GetNumBroadPhaseLayers() const override
    {
        return BroadPhaseLayers::NUM_LAYERS;
    }

    virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override
    {
        JPH_ASSERT(inLayer < PhysicsLayers::NUM_LAYERS);
        return mObjectToBroadPhase[inLayer];
    }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    virtual const char* GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override
    {
        switch ((BroadPhaseLayer::Type)inLayer)
        {
            case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:
                return "NON_MOVING";
            case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:
                return "MOVING";
            case (BroadPhaseLayer::Type)BroadPhaseLayers::DEBRIS:
                return "DEBRIS";
            case (BroadPhaseLayer::Type)BroadPhaseLayers::SENSOR:
                return "SENSOR";
            case (BroadPhaseLayer::Type)BroadPhaseLayers::UNUSED:
                return "UNUSED";
            default:
                JPH_ASSERT(false);
                return "INVALID";
        }
    }
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

private:
    JPH::BroadPhaseLayer mObjectToBroadPhase[PhysicsLayers::NUM_LAYERS];
};

/// Class that determines if an object layer can collide with a broadphase layer
class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
    virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
    {
        switch (inLayer1)
        {
            case PhysicsLayers::NON_MOVING:
                return inLayer2 == BroadPhaseLayers::MOVING;
            case PhysicsLayers::MOVING:
                return inLayer2 == BroadPhaseLayers::NON_MOVING || inLayer2 == BroadPhaseLayers::MOVING;
                return false;
            default:
                JPH_ASSERT(false);
                return false;
        }
    }
};

void Physics::Init()
{
    int mMaxConcurrentJobs = std::thread::hardware_concurrency();  
	gTempAllocator = new JPH::TempAllocatorImpl(32 * 1024 * 1024);
	gJobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, mMaxConcurrentJobs - 1);
}

void Physics::Destroy()
{
	delete gJobSystem;
	delete gTempAllocator;
}

void Physics::InitWorld()
{
    gPhysicsSystem = new JPH::PhysicsSystem();

}

void Physics::DestroyWorld()
{

	delete gPhysicsSystem;
}

void Physics::Tick()
{

}
