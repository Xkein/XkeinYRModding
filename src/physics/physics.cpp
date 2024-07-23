#include "physics/physics.h"
#include "physics/layers.h"
#include "physics/physics_component.h"
#include "physics/terrain_height_map.h"
#include "physics/yr_tools.h"
#include "physics/jolt/debug_renderer.h"
#include "runtime/logger/logger.h"
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Physics/Collision/CollideShape.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>
#include <stdarg.h>

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

// Tests the contact listener callbacks
class ContactListenerImpl : public JPH::ContactListener
{
public:
    // See: ContactListener
    virtual JPH::ValidateResult OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult) override;
    virtual void                OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;
    virtual void                OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;
    virtual void                OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override;

    // Saving / restoring state for replay
    void SaveState(JPH::StateRecorder& inStream) const;
    void RestoreState(JPH::StateRecorder& inStream);

    // Draw the current contact state
    void DrawState();

    // Ability to defer to the next contact listener after this one handles the callback
    void SetNextListener(ContactListener* inListener)
    {
        mNext = inListener;
    }

private:
    // Map that keeps track of the current state of contacts based on the contact listener callbacks
    using StatePair = std::pair<JPH::RVec3, JPH::ContactPoints>;
    using StateMap  = JPH::UnorderedMap<JPH::SubShapeIDPair, StatePair>;
    JPH::Mutex mStateMutex;
    StateMap   mState;

    ContactListener* mNext = nullptr;
};

JPH::ValidateResult ContactListenerImpl::OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult)
{
    // Check ordering contract between body 1 and body 2
    bool contract = inBody1.GetMotionType() >= inBody2.GetMotionType() || (inBody1.GetMotionType() == inBody2.GetMotionType() && inBody1.GetID() < inBody2.GetID());
    if (!contract)
        JPH_BREAKPOINT;

    JPH::ValidateResult result;
    if (mNext != nullptr)
        result = mNext->OnContactValidate(inBody1, inBody2, inBaseOffset, inCollisionResult);
    else
        result = ContactListener::OnContactValidate(inBody1, inBody2, inBaseOffset, inCollisionResult);

    JPH::RVec3 contact_point = inBaseOffset + inCollisionResult.mContactPointOn1;
    JPH::DebugRenderer::sInstance->DrawArrow(contact_point, contact_point - inCollisionResult.mPenetrationAxis.NormalizedOr(JPH::Vec3::sZero()), JPH::Color::sBlue, 0.05f);

    JPH::Trace("Validate %u and %u result %d", inBody1.GetID().GetIndex(), inBody2.GetID().GetIndex(), (int)result);

    return result;
}

void ContactListenerImpl::OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
    // Expect bodies to be sorted
    if (!(inBody1.GetID() < inBody2.GetID()))
        JPH_BREAKPOINT;

    JPH::Trace("Contact added %u (%08x) and %u (%08x)", inBody1.GetID().GetIndex(), inManifold.mSubShapeID1.GetValue(), inBody2.GetID().GetIndex(), inManifold.mSubShapeID2.GetValue());

    JPH::DebugRenderer::sInstance->DrawWirePolygon(JPH::RMat44::sTranslation(inManifold.mBaseOffset), inManifold.mRelativeContactPointsOn1, JPH::Color::sGreen, 0.05f);
    JPH::DebugRenderer::sInstance->DrawWirePolygon(JPH::RMat44::sTranslation(inManifold.mBaseOffset), inManifold.mRelativeContactPointsOn2, JPH::Color::sGreen, 0.05f);
    JPH::DebugRenderer::sInstance->DrawArrow(inManifold.GetWorldSpaceContactPointOn1(0), inManifold.GetWorldSpaceContactPointOn1(0) + inManifold.mWorldSpaceNormal, JPH::Color::sGreen, 0.05f);

    // Insert new manifold into state map
    {
        std::lock_guard     lock(mStateMutex);
        JPH::SubShapeIDPair key(inBody1.GetID(), inManifold.mSubShapeID1, inBody2.GetID(), inManifold.mSubShapeID2);
        if (mState.find(key) != mState.end())
            JPH_BREAKPOINT; // Added contact that already existed
        mState[key] = StatePair(inManifold.mBaseOffset, inManifold.mRelativeContactPointsOn1);
    }

    if (mNext != nullptr)
        mNext->OnContactAdded(inBody1, inBody2, inManifold, ioSettings);
}

void ContactListenerImpl::OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
    // Expect bodies to be sorted
    if (!(inBody1.GetID() < inBody2.GetID()))
        JPH_BREAKPOINT;

    JPH::Trace("Contact persisted %u (%08x) and %u (%08x)", inBody1.GetID().GetIndex(), inManifold.mSubShapeID1.GetValue(), inBody2.GetID().GetIndex(), inManifold.mSubShapeID2.GetValue());

    JPH::DebugRenderer::sInstance->DrawWirePolygon(JPH::RMat44::sTranslation(inManifold.mBaseOffset), inManifold.mRelativeContactPointsOn1, JPH::Color::sYellow, 0.05f);
    JPH::DebugRenderer::sInstance->DrawWirePolygon(JPH::RMat44::sTranslation(inManifold.mBaseOffset), inManifold.mRelativeContactPointsOn2, JPH::Color::sYellow, 0.05f);
    JPH::DebugRenderer::sInstance->DrawArrow(inManifold.GetWorldSpaceContactPointOn1(0), inManifold.GetWorldSpaceContactPointOn1(0) + inManifold.mWorldSpaceNormal, JPH::Color::sYellow, 0.05f);

    // Update existing manifold in state map
    {
        std::lock_guard     lock(mStateMutex);
        JPH::SubShapeIDPair key(inBody1.GetID(), inManifold.mSubShapeID1, inBody2.GetID(), inManifold.mSubShapeID2);
        StateMap::iterator  i = mState.find(key);
        if (i != mState.end())
            i->second = StatePair(inManifold.mBaseOffset, inManifold.mRelativeContactPointsOn1);
        else
            JPH_BREAKPOINT; // Persisted contact that didn't exist
    }

    if (mNext != nullptr)
        mNext->OnContactPersisted(inBody1, inBody2, inManifold, ioSettings);
}

void ContactListenerImpl::OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair)
{
    // Expect bodies to be sorted
    if (!(inSubShapePair.GetBody1ID() < inSubShapePair.GetBody2ID()))
        JPH_BREAKPOINT;

    JPH::Trace("Contact removed %u (%08x) and %u (%08x)",
               inSubShapePair.GetBody1ID().GetIndex(),
               inSubShapePair.GetSubShapeID1().GetValue(),
               inSubShapePair.GetBody2ID().GetIndex(),
               inSubShapePair.GetSubShapeID2().GetValue());

    // Update existing manifold in state map
    {
        std::lock_guard    lock(mStateMutex);
        StateMap::iterator i = mState.find(inSubShapePair);
        if (i != mState.end())
            mState.erase(i);
        else
            JPH_BREAKPOINT; // Removed contact that didn't exist
    }

    if (mNext != nullptr)
        mNext->OnContactRemoved(inSubShapePair);
}

XKEINEXT_API JPH::JobSystem* gJobSystem;
XKEINEXT_API JPH::PhysicsSystem* gPhysicsSystem;
XKEINEXT_API JPH::BodyInterface* gBodyInterface;
XKEINEXT_API JPH::TempAllocator* gTempAllocator;
XKEINEXT_API JPH::BroadPhaseLayerInterface* gBroadPhaseLayerInterface;
XKEINEXT_API JPH::ObjectVsBroadPhaseLayerFilter* gObjectVsBroadPhaseLayerFilter;
XKEINEXT_API JPH::ObjectLayerPairFilter* gObjectLayerPairFilter;

XKEINEXT_API TerrainHeightMap* Physics::gTerrainHeightMap;

static constexpr uint cNumBodies             = 10240;
static constexpr uint cNumBodyMutexes        = 0; // Autodetect
static constexpr uint cMaxBodyPairs          = 65536;
static constexpr uint cMaxContactConstraints = 20480;

static JPH::PhysicsSettings gPhysicsSettings;
static ContactListenerImpl* gContactListener = nullptr;
static DebugRendererImpl* gDebugRenderer = nullptr;

static void JoltTrace(const char* inFMT, ...)
{
    // Format the message
    va_list list;
    va_start(list, inFMT);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), inFMT, list);
    va_end(list);

    gLogger->info(buffer);
}

void Physics::Init()
{
    JPH::Trace = JoltTrace;
    JPH::RegisterDefaultAllocator();
    JPH::Factory::sInstance = new JPH::Factory;
    // Register physics types with the factory
    JPH::RegisterTypes();

    gDebugRenderer = new DebugRendererImpl();

    int mMaxConcurrentJobs = std::thread::hardware_concurrency();
    gTempAllocator         = new JPH::TempAllocatorImpl(32 * 1024 * 1024);
    gJobSystem             = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, mMaxConcurrentJobs - 1);

    gBroadPhaseLayerInterface      = new BPLayerInterfaceImpl();
    gObjectVsBroadPhaseLayerFilter = new ObjectVsBroadPhaseLayerFilterImpl();
    gObjectLayerPairFilter         = new ObjectLayerPairFilterImpl();
}

void Physics::Destroy()
{
    delete gBroadPhaseLayerInterface;
    delete gObjectVsBroadPhaseLayerFilter;
    delete gObjectLayerPairFilter;
    delete gJobSystem;
    delete gTempAllocator;
    delete gDebugRenderer;

    // Unregisters all types with the factory and cleans up the default material
    JPH::UnregisterTypes();

    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
}

void Physics::InitWorld()
{
    gPhysicsSystem = new JPH::PhysicsSystem();
    gPhysicsSystem->Init(cNumBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, *gBroadPhaseLayerInterface, *gObjectVsBroadPhaseLayerFilter, *gObjectLayerPairFilter);
    gPhysicsSystem->SetPhysicsSettings(gPhysicsSettings);
    gPhysicsSystem->SetGravity(JPH::Vec3(0, 0, -9.81f));

    gBodyInterface = &gPhysicsSystem->GetBodyInterface();

    gContactListener = new ContactListenerImpl();
    gPhysicsSystem->SetContactListener(gContactListener);

    gTerrainHeightMap = new TerrainHeightMap();

    gPhysicsSystem->OptimizeBroadPhase();
}

void Physics::DestroyWorld()
{
    delete gTerrainHeightMap;
    delete gContactListener;

    gBodyInterface = nullptr;
    delete gPhysicsSystem;
}

const float DELTA_TIME      = 1.0f / 30;
const int   COLLISION_STEPS = 1;

void Physics::BeginTick()
{
    auto view = gEntt->view<PhysicsComponent>();
    // PrePhysicsUpdate
    // set yr transform to physics world
    for (auto&& [entity, com] : view.each())
    {
        AbstractClass* pYrObject = com.owner;
        JPH::Body*     body      = com.body;
        switch (pYrObject->WhatAmI())
        {
            case AbstractType::Bullet:
            case AbstractType::VoxelAnim: {
                JPH::Vec3 linearVelocity  = ToVec3(GetObjectLinearVelocity(pYrObject));
                JPH::Vec3 angularVelocity = ToVec3(GetObjectAngularVelocity(pYrObject));
                gBodyInterface->SetLinearAndAngularVelocity(body->GetID(), linearVelocity, angularVelocity);
                break;
            }
        }
        JPH::Vec3        position   = ToVec3(GetObjectCoords(pYrObject));
        JPH::Quat        quat       = ToQuat(GetObjectRotation(pYrObject));
        JPH::EActivation activation = body->IsStatic() ? JPH::EActivation::DontActivate : JPH::EActivation::Activate;
        if (quat.IsNaN()) {
            quat = JPH::Quat::sIdentity();
            gLogger->error("{} rotation is NaN!", (void*)pYrObject);
        }
        else {
            quat = quat.Normalized();
        }
        gBodyInterface->SetPositionAndRotationWhenChanged(body->GetID(), position, quat, activation);
    }

    gPhysicsSystem->Update(DELTA_TIME, COLLISION_STEPS, gTempAllocator, gJobSystem);

    // PostPhysicsUpdate
    // set yr transform from physics world
    for (auto&& [entity, com] : view.each())
    {
        AbstractClass* pYrObject = com.owner;
        JPH::Body*     body      = com.body;
        if (body->IsActive())
        {
            JPH::Vec3 position        = body->GetPosition();
            JPH::Quat rotation        = body->GetRotation();
            JPH::Vec3 linearVelocity  = body->GetLinearVelocity();
            JPH::Vec3 angularVelocity = body->GetAngularVelocity();
            SetObjectCoords(pYrObject, ToCoord(position));
            SetObjectRotation(pYrObject, ToQuaternion(rotation));
            switch (pYrObject->WhatAmI())
            {
                case AbstractType::Bullet:
                case AbstractType::VoxelAnim: {
                    SetObjectLinearVelocity(pYrObject, ToVector3f(linearVelocity));
                    SetObjectAngularVelocity(pYrObject, ToVector3f(angularVelocity));
                    break;
                }
            }
        }
    }
}

void Physics::EndTick() {}

#include "yr/event/general_event.h"
REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioStartEvent, Physics::InitWorld);
REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioClearEvent, Physics::DestroyWorld);
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, Physics::BeginTick);
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, Physics::EndTick);
