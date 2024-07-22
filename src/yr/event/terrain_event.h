#pragma once

#include "yr/yr_event.h"

class TerrainClass;
struct IStream;

CLASS(HookEvent)
class YrTerrainCtorEvent
{
public:
    TerrainClass* pTerrain {nullptr};
};

CLASS(HookEvent)
class YrTerrainDtorEvent
{
public:
    TerrainClass* pTerrain {nullptr};
};
