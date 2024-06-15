#include "yr/event/infantry_event.h"
#include "yr/event/infantry_type_event.h"
#include "yr/yr_hook.h"

#include <FootClass.h>
#include <InfantryClass.h>
#include <InfantryTypeClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x517BDF, 0x5, YrInfantryCtorEvent)
{
    E->pInfantry = R->ESI<InfantryClass*>();
}
BROADCAST_HOOK_EVENT(0x517D90, 0x5, YrInfantryDtorEvent)
{
    E->pInfantry = R->ECX<InfantryClass*>();
}

BROADCAST_HOOK_EVENT(0x523970, 0x5, YrInfantryTypeCtorEvent)
{
    E->pInfantryType = R->ESI<InfantryTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x524D70, 0x6, YrInfantryTypeDtorEvent)
{
    E->pInfantryType = R->ECX<InfantryTypeClass*>();
}
