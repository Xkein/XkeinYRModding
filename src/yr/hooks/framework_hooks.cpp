#include "yr_hook.h"
#include "yr/event/yr_entity_event.h"

BROADCAST_HOOK_EVENT(0x6F3260, 0x5, YrTechnoCtorEvent)
BROADCAST_HOOK_EVENT(0x6F4500, 0x5, YrTechnoDtorEvent)

BROADCAST_HOOK_EVENT(0x70C250, 0x5, YrTechnoSaveGameBeginEvent)
BROADCAST_HOOK_EVENT(0x70C264, 0x5, YrTechnoSaveGameEndEvent)

BROADCAST_HOOK_EVENT(0x70BF50, 0x5, YrTechnoLoadGameBeginEvent)
BROADCAST_HOOK_EVENT(0x70C249, 0x5, YrTechnoLoadGameEndEvent)



BROADCAST_HOOK_EVENT(0x711835, 0x5, YrTechnoTypeCtorEvent)
BROADCAST_HOOK_EVENT(0x711AE0, 0x5, YrTechnoTypeDtorEvent)

BROADCAST_HOOK_EVENT(0x716132, 0x5, YrTechnoTypeLoadIniEvent)
BROADCAST_HOOK_EVENT(0x716123, 0x5, YrTechnoTypeLoadIniEvent)

BROADCAST_HOOK_EVENT(0x716DC0, 0x5, YrTechnoTypeSaveGameBeginEvent)
BROADCAST_HOOK_EVENT(0x717094, 0x5, YrTechnoTypeSaveGameEndEvent)

BROADCAST_HOOK_EVENT(0x7162F0, 0x6, YrTechnoTypeLoadGameBeginEvent)
BROADCAST_HOOK_EVENT(0x716DAC, 0xA, YrTechnoTypeLoadGameEndEvent)
