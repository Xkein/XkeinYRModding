#include "yr/event/mission_event.h"
#include "yr/yr_hook.h"
#include <FootClass.h>

IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrMissionExecuteEvent, 0x5B30B2, 0x5B30D8)
BROADCAST_HOOK_EVENT(0x5B30B2, 0x6, YrMissionExecuteEvent)
{
    E->pMission = R->EDI<MissionClass*>();
}
IMPL_HOOK_BROADCAST(YrMissionExecuteEvent, 0x5B30B2) {
    auto retAddr = hookEvent->Broadcast(R, E);
    if (E->hasSet) {
        E->pMission->UpdateTimer.Start(E->returnValue);
    }
    return retAddr;
}
