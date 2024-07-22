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

BROADCAST_HOOK_EVENT(0x71DBC0, 0x7, YrTerrainTypeCtorEvent)
{
    E->pTerrainType = R->ESI<TerrainTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x71E364, 0x6, YrTerrainTypeDtorEvent)
{
    E->pTerrainType = R->ECX<TerrainTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x71E0A6, 0x5, YrTerrainTypeLoadIniEvent)
{
    E->pTerrainType = R->ESI<TerrainTypeClass*>();
    E->pIni         = R->Stack<CCINIClass*>(0x4);
}
