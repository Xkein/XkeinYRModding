#pragma once

#include "core/reflection/reflection.h"
#include "core/tool/delegate.h"
#include "physics/jolt/jolt.h"
#include "physics/physics_component.h"
#include <jolt/Physics/Collision/ContactListener.h>

class TerrainBody;
class PhysicsCollisionAddAndPersistResult;
class PhysicsCollisionRemoveResult;

namespace cereal
{
    template<class Archive>
    void save(Archive& ar, JPH::BodyID const& data)
    {
        ar(data.GetIndexAndSequenceNumber());
    }
    template<class Archive>
    void load(Archive& ar, JPH::BodyID& data)
    {
        uint32 id = data.GetIndexAndSequenceNumber();
        ar(id);
        data = JPH::BodyID(id);
    }
    REMOVE_SERIALIZE_BRACKET(JPH::BodyID);
}

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

    static XKEINEXT_API TMulticastDelegateRegistration<void(const PhysicsCollisionAddAndPersistResult&)>& GetOnCollisionEnter();
    static XKEINEXT_API TMulticastDelegateRegistration<void(const PhysicsCollisionAddAndPersistResult&)>& GetOnCollisionPersist();
    static XKEINEXT_API TMulticastDelegateRegistration<void(const PhysicsCollisionRemoveResult&)>& GetOnCollisionExit();

private:
    friend void OnContactAdded(const JPH::Body&, const JPH::Body&,
                                const JPH::ContactManifold&, JPH::ContactSettings&);
    friend void OnContactPersisted(const JPH::Body&, const JPH::Body&,
                                   const JPH::ContactManifold&, JPH::ContactSettings&);
    friend void OnContactRemoved(const JPH::SubShapeIDPair&);

    static TMulticastDelegate<void(const PhysicsCollisionAddAndPersistResult&)> mOnCollisionEnter;
    static TMulticastDelegate<void(const PhysicsCollisionAddAndPersistResult&)> mOnCollisionPersist;
    static TMulticastDelegate<void(const PhysicsCollisionRemoveResult&)> mOnCollisionExit;
};

extern XKEINEXT_API JPH::JobSystem*		                gJobSystem;
extern XKEINEXT_API JPH::PhysicsSystem*	                gPhysicsSystem;
extern XKEINEXT_API JPH::BodyInterface*	                gBodyInterface;
extern XKEINEXT_API JPH::BodyInterface*	                gBodyInterfaceNoLock;
extern XKEINEXT_API JPH::TempAllocator*                 gTempAllocator;
extern XKEINEXT_API JPH::BroadPhaseLayerInterface*      gBroadPhaseLayerInterface;
extern XKEINEXT_API JPH::ObjectVsBroadPhaseLayerFilter* gObjectVsBroadPhaseLayerFilter;
extern XKEINEXT_API JPH::ObjectLayerPairFilter*         gObjectLayerPairFilter;


CLASS(BindJs)
class PhysicsCollisionAddAndPersistResult
{
public:
    PROPERTY()
    PhysicsComponent* com1;
    PROPERTY()
    PhysicsComponent* com2;
    PROPERTY()
    CoordStruct point;
    PROPERTY()
    Vector3D<float> normal;
};

CLASS(BindJs)
class PhysicsCollisionRemoveResult
{
public:
    PROPERTY()
    PhysicsComponent* com1;
    PROPERTY()
    PhysicsComponent* com2;

};
