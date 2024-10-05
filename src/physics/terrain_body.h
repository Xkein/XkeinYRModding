#pragma once
#include "jolt/jolt.h"
#include <vector>

class CellClass;

class TerrainBody
{
public:
    TerrainBody();
    ~TerrainBody();

    void Rebuild();
    void Clear();

    std::vector<JPH::Body*> heightBodies;
    std::vector<JPH::Body*> cliffBodies;
private:
    void CreateCellBody(CellClass* pCell);
};
