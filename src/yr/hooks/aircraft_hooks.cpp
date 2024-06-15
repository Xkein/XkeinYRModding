#include "yr/event/aircraft_event.h"
#include "yr/event/aircraft_type_event.h"
#include "yr/yr_hook.h"

#include <FootClass.h>
#include <AircraftClass.h>
#include <AircraftTypeClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x413F68, 0x5, YrAircraftCtorEvent)
{
    E->pAircraft = R->ESI<AircraftClass*>();
}
BROADCAST_HOOK_EVENT(0x414080, 0x5, YrAircraftDtorEvent)
{
    E->pAircraft = R->ECX<AircraftClass*>();
}

BROADCAST_HOOK_EVENT(0x41C9E1, 0x7, YrAircraftTypeCtorEvent)
{
    E->pAircraftType = R->ECX<AircraftTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x41CFE0, 0x6, YrAircraftTypeDtorEvent)
{
    E->pAircraftType = R->ECX<AircraftTypeClass*>();
}
