#pragma once
#include "jolt/jolt.h"
#include <vector>

class CellClass;

class TerrainHeightMap
{
public:
    TerrainHeightMap();
    ~TerrainHeightMap();

    void Rebuild();
    void Clear();

    JPH::Body* heightMapBody;
    std::vector<JPH::Body*> cliffBodies;
private:
    void CreateCellBody(CellClass* pCell);
};
