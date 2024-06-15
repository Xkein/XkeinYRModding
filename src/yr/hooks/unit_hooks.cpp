#include "yr/event/unit_event.h"
#include "yr/event/unit_type_event.h"
#include "yr/yr_hook.h"

#include <FootClass.h>
#include <UnitClass.h>
#include <UnitTypeClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x7356A4, 0x5, YrUnitCtorEvent)
{
    E->pUnit = R->ESI<UnitClass*>();
}
BROADCAST_HOOK_EVENT(0x735780, 0x6, YrUnitDtorEvent)
{
    E->pUnit = R->ECX<UnitClass*>();
}


BROADCAST_HOOK_EVENT(0x7472B1, 0x6, YrUnitTypeCtorEvent)
{
    E->pUnitType = R->ESI<UnitTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x748190, 0x6, YrUnitTypeDtorEvent)
{
    E->pUnitType = R->ECX<UnitTypeClass*>();
}
