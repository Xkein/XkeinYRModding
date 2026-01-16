#pragma once

#include "yr/yr_event.h"

class TerrainTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrTerrainTypeCtorEvent
{
public:
    PROPERTY()
    TerrainTypeClass* pTerrainType;
};

CLASS(HookEvent, BindJs)
class YrTerrainTypeDtorEvent
{
public:
    PROPERTY()
    TerrainTypeClass* pTerrainType;
};

CLASS(HookEvent, BindJs)
class YrTerrainTypeSaveGameBeginEvent
{
public:
    PROPERTY()
    TerrainTypeClass* pTerrainType;
    PROPERTY()
    IStream*          stream;
};

CLASS(HookEvent, BindJs)
class YrTerrainTypeSaveGameEndEvent
{
public:
    PROPERTY()
    TerrainTypeClass* pTerrainType;
    PROPERTY()
    IStream*          stream;
};

CLASS(HookEvent, BindJs)
class YrTerrainTypeLoadGameBeginEvent
{
public:
    PROPERTY()
    TerrainTypeClass* pTerrainType;
    PROPERTY()
    IStream*          stream;
};

CLASS(HookEvent, BindJs)
class YrTerrainTypeLoadGameEndEvent
{
public:
    PROPERTY()
    TerrainTypeClass* pTerrainType;
    PROPERTY()
    IStream*          stream;
};

CLASS(HookEvent, BindJs)
class YrTerrainTypeLoadIniEvent
{
public:
    PROPERTY()
    TerrainTypeClass* pTerrainType;
    PROPERTY()
    CCINIClass*       pIni;
};
