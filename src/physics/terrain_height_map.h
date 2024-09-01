#pragma once
#include "jolt/jolt.h"
#include <vector>

class TerrainHeightMap
{
public:
    TerrainHeightMap();
    ~TerrainHeightMap();

    void Rebuild();
    void Clear();

    JPH::Body* heightMapBody;
    std::vector<JPH::Body*> cliffBodies;
};
