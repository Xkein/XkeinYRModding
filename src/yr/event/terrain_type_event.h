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
class YrTerrainTypeSaveGameBeginEvent
{
public:
    TerrainTypeClass* pTerrainType;
    IStream*          stream;
};

CLASS(HookEvent)
class YrTerrainTypeSaveGameEndEvent
{
public:
    TerrainTypeClass* pTerrainType;
    IStream*          stream;
};

CLASS(HookEvent)
class YrTerrainTypeLoadGameBeginEvent
{
public:
    TerrainTypeClass* pTerrainType;
    IStream*          stream;
};

CLASS(HookEvent)
class YrTerrainTypeLoadGameEndEvent
{
public:
    TerrainTypeClass* pTerrainType;
    IStream*          stream;
};

CLASS(HookEvent)
class YrTerrainTypeLoadIniEvent
{
public:
    TerrainTypeClass* pTerrainType;
    CCINIClass*       pIni;
};
