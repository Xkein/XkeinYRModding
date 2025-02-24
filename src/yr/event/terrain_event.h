#pragma once

#include "yr/yr_event.h"

class TerrainClass;
struct IStream;

CLASS(HookEvent)
class YrTerrainCtorEvent
{
public:
    TerrainClass* pTerrain;
};

CLASS(HookEvent)
class YrTerrainDtorEvent
{
public:
    TerrainClass* pTerrain;
};

CLASS(HookEvent)
class YrTerrainSaveGameBeginEvent
{
public:
    TerrainClass* pTerrain;
    IStream*      stream;
};

CLASS(HookEvent)
class YrTerrainSaveGameEndEvent
{
public:
    TerrainClass* pTerrain;
    IStream*      stream;
};

CLASS(HookEvent)
class YrTerrainLoadGameBeginEvent
{
public:
    TerrainClass* pTerrain;
    IStream*      stream;
};

CLASS(HookEvent)
class YrTerrainLoadGameEndEvent
{
public:
    TerrainClass* pTerrain;
    IStream*      stream;
};