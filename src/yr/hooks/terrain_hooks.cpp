#include "yr/event/terrain_event.h"
#include "yr/event/terrain_type_event.h"
#include "yr/yr_hook.h"

#include <FootClass.h>
#include <TerrainClass.h>
#include <TerrainTypeClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x71BDD7, 0x7, YrTerrainCtorEvent)
{
    E->pTerrain = R->ESI<TerrainClass*>();
}
BROADCAST_HOOK_EVENT(0x71B7B0, 0x6, YrTerrainDtorEvent)
{
    E->pTerrain = R->ECX<TerrainClass*>();
}
BROADCAST_HOOK_EVENT(0x71CF30, 0x8, YrTerrainSaveGameBeginEvent)
{
    E->pTerrain = R->Stack<TerrainClass*>(0x4);
    E->stream   = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTerrain;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x71CF44, 0x5, YrTerrainSaveGameEndEvent)
{
    E->pTerrain = reinterpret_cast<TerrainClass*>(gSavingObject);
    E->stream   = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x71CDA0, 0x8, YrTerrainLoadGameBeginEvent)
{
    E->pTerrain = R->Stack<TerrainClass*>(0x4);
    E->stream   = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTerrain;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x71CF2B, 0x5, YrTerrainLoadGameEndEvent)
{
    E->pTerrain = reinterpret_cast<TerrainClass*>(gSavingObject);
    E->stream   = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x71DBC0, 0x7, YrTerrainTypeCtorEvent)
{
    E->pTerrainType = R->ESI<TerrainTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x71E364, 0x6, YrTerrainTypeDtorEvent)
{
    E->pTerrainType = R->ECX<TerrainTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x71E240, 0x8, YrTerrainTypeSaveGameBeginEvent)
{
    E->pTerrainType = R->Stack<TerrainTypeClass*>(0x4);
    E->stream       = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTerrainType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x71E25A, 0x5, YrTerrainTypeSaveGameEndEvent)
{
    E->pTerrainType = reinterpret_cast<TerrainTypeClass*>(gSavingObject);
    E->stream       = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x71E1D0, 0x5, YrTerrainTypeLoadGameBeginEvent)
{
    E->pTerrainType = R->Stack<TerrainTypeClass*>(0x4);
    E->stream       = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTerrainType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x71E235, 0x5, YrTerrainTypeLoadGameEndEvent)
{
    E->pTerrainType = reinterpret_cast<TerrainTypeClass*>(gSavingObject);
    E->stream       = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x71E0A6, 0x5, YrTerrainTypeLoadIniEvent)
{
    E->pTerrainType = R->ESI<TerrainTypeClass*>();
    E->pIni         = R->Stack<CCINIClass*>(0x4);
}
