#include "yr/event/trigger_event.h"
#include "yr/yr_hook.h"

#include <TriggerClass.h>

IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTActionExecuteEvent, 0x6DD8B0, 0x6DD910)
BROADCAST_HOOK_EVENT(0x6DD8B0, 0x6, YrTActionExecuteEvent)
{
    E->pAction  = R->ECX<TActionClass*>();
    E->pHouse   = R->Stack<HouseClass*>(0x4);
    E->pObject  = R->Stack<ObjectClass*>(0x8);
    E->pTrigger = R->Stack<TriggerClass*>(0xC);
    E->location = R->Stack<CellStruct const*>(0x10);
}