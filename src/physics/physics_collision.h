#pragma once
#include "core/reflection/reflection.h"
#include "physics/jolt/jolt.h"
#include <jolt/Physics/Collision/ContactListener.h>

class PhysicsComponent;
#ifndef __HEADER_TOOL__
#include "physics/physics_component.h"
#endif
struct PhysicsCollision
{
    static void OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings);
    static void OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings);
    static void OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair);
};

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
