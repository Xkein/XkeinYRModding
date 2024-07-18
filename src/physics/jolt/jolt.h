#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Core/Reference.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Body/MotionType.h>

namespace JPH
{
    enum class EActivation;
    enum class ValidateResult;
} // namespace JPH

namespace JPH
{
    class PhysicsSystem;
    class JobSystem;
    class TempAllocator;
    class BroadPhaseLayerInterface;
    class JobSystemThreadPool;
    class BodyInterface;
    class BoxShapeSettings;
    class ShapeSettings;
    class Shape;
    class BodyCreationSettings;
    class Body;
    class BodyID;
    class SphereShape;
    class BroadPhaseLayer;
    class ObjectLayerPairFilter;
    class ObjectVsBroadPhaseLayerFilter;
    class ContactListener;
    class BodyActivationListener;
    class CollideShapeResult;
    class ContactManifold;
    class ContactSettings;
    class SubShapeIDPair;
    class Factory;
} // namespace JPH

