#pragma once

#include "yr/yr_event.h"

class TerrainTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrTerrainTypeCtorEvent
{
public:
    TerrainTypeClass* pTerrainType;
};

CLASS(HookEvent)
class YrTerrainTypeDtorEvent
{
public:
    TerrainTypeClass* pTerrainType;
};

CLASS(HookEvent)
class YrTerrainTypeLoadIniEvent
{
public:
    TerrainTypeClass* pTerrainType;
    CCINIClass*       pIni;
};
