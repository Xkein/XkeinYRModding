#pragma once
#include "jolt/jolt.h"
#include <vector>

class CellClass;

class BridgeBody
{
public:
    BridgeBody();
    ~BridgeBody();

    void Rebuild();
    void Clear();

    std::vector<JPH::Body*> bodies;
};
