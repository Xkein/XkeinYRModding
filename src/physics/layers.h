#pragma once
#include "runtime/platform/platform.h"
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <jolt/Core/Core.h>

/// Layer that objects can be in, determines which other objects it can collide with
namespace PhysicsLayers
{
    static constexpr JPH::ObjectLayer NON_MOVING = 0;
    static constexpr JPH::ObjectLayer MOVING     = 1;
    static constexpr JPH::ObjectLayer SENSOR     = 2;
    static constexpr JPH::ObjectLayer DEBRIS     = 3;
    static constexpr JPH::ObjectLayer NUM_LAYERS = 4;
}; // namespace PhysicsLayers

/// Broadphase layers
namespace BroadPhaseLayers
{
    static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
    static constexpr JPH::BroadPhaseLayer MOVING(1);
    static constexpr JPH::BroadPhaseLayer SENSOR(2);
    static constexpr JPH::BroadPhaseLayer DEBRIS(3);
    static constexpr uint32               NUM_LAYERS(4);
}; // namespace BroadPhaseLayers
