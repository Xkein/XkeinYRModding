#pragma once

#include "yr/yr_event.h"

class TerrainClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrTerrainCtorEvent
{
public:
    PROPERTY()
    TerrainClass* pTerrain;
};

CLASS(HookEvent, BindJs)
class YrTerrainDtorEvent
{
public:
    PROPERTY()
    TerrainClass* pTerrain;
};

CLASS(HookEvent, BindJs)
class YrTerrainSaveGameBeginEvent
{
public:
    PROPERTY()
    TerrainClass* pTerrain;
    PROPERTY()
    IStream*      stream;
};

CLASS(HookEvent, BindJs)
class YrTerrainSaveGameEndEvent
{
public:
    PROPERTY()
    TerrainClass* pTerrain;
    PROPERTY()
    IStream*      stream;
};

CLASS(HookEvent, BindJs)
class YrTerrainLoadGameBeginEvent
{
public:
    PROPERTY()
    TerrainClass* pTerrain;
    PROPERTY()
    IStream*      stream;
};

CLASS(HookEvent, BindJs)
class YrTerrainLoadGameEndEvent
{
public:
    PROPERTY()
    TerrainClass* pTerrain;
    PROPERTY()
    IStream*      stream;
};