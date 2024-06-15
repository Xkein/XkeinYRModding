#include "yr/event/building_event.h"
#include "yr/event/building_type_event.h"
#include "yr/yr_hook.h"

#include <BuildingClass.h>
#include <BuildingTypeClass.h>
#include <FootClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x43BCB3, 0x6, YrBuildingCtorEvent)
{
    E->pBuilding = R->ESI<BuildingClass*>();
}
BROADCAST_HOOK_EVENT(0x43BCF0, 0x6, YrBuildingDtorEvent)
{
    E->pBuilding = R->ECX<BuildingClass*>();
}

BROADCAST_HOOK_EVENT(0x45E50C, 0x6, YrBuildingTypeCtorEvent)
{
    E->pBuildingType = R->EAX<BuildingTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x45E580, 0x5, YrBuildingTypeDtorEvent)
{
    E->pBuildingType = R->ECX<BuildingTypeClass*>();
}
