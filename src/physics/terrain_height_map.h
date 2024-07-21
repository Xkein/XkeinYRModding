#pragma once
#include "jolt/jolt.h"
#include <vector>

class TerrainHeightMap
{
public:
    TerrainHeightMap();
    ~TerrainHeightMap();

    JPH::Body* body;
    std::vector<JPH::Body*> cliffBodies;
};
