#include "yr/event/house_event.h"
#include "yr/event/house_type_event.h"
#include "yr/yr_hook.h"

#include <FootClass.h>
#include <HouseClass.h>
#include <HouseTypeClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x4F6532, 0x5, YrHouseCtorEvent)
{
    E->pHouse = R->EAX<HouseClass*>();
}
BROADCAST_HOOK_EVENT(0x4F7140, 0x6, YrHouseDtorEvent)
{
    E->pHouse = R->ECX<HouseClass*>();
}

BROADCAST_HOOK_EVENT_AGAIN(0x511635, 0x5, YrHouseTypeCtorEvent, 0x511643)
BROADCAST_HOOK_EVENT(0x511643, 0x5, YrHouseTypeCtorEvent)
{
    E->pHouseType = R->EAX<HouseTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x512760, 0x6, YrHouseTypeDtorEvent)
{
    E->pHouseType = R->ECX<HouseTypeClass*>();
}

BROADCAST_HOOK_EVENT_AGAIN(0x51215A, 0x5, YrHouseTypeLoadIniEvent, 0x51214F)
BROADCAST_HOOK_EVENT(0x51214F, 0x5, YrHouseTypeLoadIniEvent)
{
    E->pHouseType = R->EBX<HouseTypeClass*>();
    E->pIni       = R->Base<CCINIClass*>(0x8);
}