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
BROADCAST_HOOK_EVENT(0x504080, 0x5, YrHouseSaveGameBeginEvent)
{
    E->pHouse = R->Stack<HouseClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);

    gSavingObject = E->pHouse;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x5046DE, 0x7, YrHouseSaveGameEndEvent)
{
    E->pHouse = reinterpret_cast<HouseClass*>(gSavingObject);
    E->stream = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x503040, 0x5, YrHouseLoadGameBeginEvent)
{
    E->pHouse = R->Stack<HouseClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);

    gSavingObject = E->pHouse;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x504069, 0x7, YrHouseLoadGameEndEvent)
{
    E->pHouse = reinterpret_cast<HouseClass*>(gSavingObject);
    E->stream = gSavingStream;
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
BROADCAST_HOOK_EVENT(0x512480, 0x5, YrHouseTypeSaveGameBeginEvent)
{
    E->pHouseType = R->Stack<HouseTypeClass*>(0x4);
    E->stream     = R->Stack<IStream*>(0x8);

    gSavingObject = E->pHouseType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x51255C, 0x5, YrHouseTypeSaveGameEndEvent)
{
    E->pHouseType = reinterpret_cast<HouseTypeClass*>(gSavingObject);
    E->stream     = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x512290, 0x5, YrHouseTypeLoadGameBeginEvent)
{
    E->pHouseType = R->Stack<HouseTypeClass*>(0x4);
    E->stream     = R->Stack<IStream*>(0x8);

    gSavingObject = E->pHouseType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x51246D, 0x5, YrHouseTypeLoadGameEndEvent)
{
    E->pHouseType = reinterpret_cast<HouseTypeClass*>(gSavingObject);
    E->stream     = gSavingStream;
}
BROADCAST_HOOK_EVENT_AGAIN(0x51215A, 0x5, YrHouseTypeLoadIniEvent, 0x51214F)
BROADCAST_HOOK_EVENT(0x51214F, 0x5, YrHouseTypeLoadIniEvent)
{
    E->pHouseType = R->EBX<HouseTypeClass*>();
    E->pIni       = R->Base<CCINIClass*>(0x8);
}