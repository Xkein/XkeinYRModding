#include "physics/terrain_height_map.h"
#include "physics/physics.h"
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/PhysicsSystem.h>

TerrainHeightMap::TerrainHeightMap()
{

}

TerrainHeightMap::~TerrainHeightMap()
{
    for (JPH::Body* cliffBody : cliffBodies)
    {
        gBodyInterface->RemoveBody(body->GetID());
    }
    if (body)
    {
        gBodyInterface->RemoveBody(body->GetID());
    }
}
