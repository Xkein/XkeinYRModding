#include "yr/yr_hook.h"
#include "yr/event/techno_event.h"
#include "yr/event/techno_type_event.h"

#include <TechnoClass.h>
#include <FootClass.h>
#include <TechnoTypeClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x6F3260, 0x5, YrTechnoCtorEvent)
{
    E->pTechno = R->ESI<TechnoClass*>();
}
BROADCAST_HOOK_EVENT(0x6F4500, 0x5, YrTechnoDtorEvent)
{
    E->pTechno = R->ECX<TechnoClass*>();
}

BROADCAST_HOOK_EVENT(0x70C250, 0x5, YrTechnoSaveGameBeginEvent)
{
    
    E->pTechno = R->Stack<TechnoClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTechno;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x70C264, 0x5, YrTechnoSaveGameEndEvent)
{
    E->pTechno = reinterpret_cast<TechnoClass*>(gSavingObject);
    E->stream = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x70BF50, 0x5, YrTechnoLoadGameBeginEvent)
{
    E->pTechno = R->Stack<TechnoClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);
}
BROADCAST_HOOK_EVENT(0x70C249, 0x5, YrTechnoLoadGameEndEvent)
{
    E->pTechno = reinterpret_cast<TechnoClass*>(gSavingObject);
    E->stream = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x711835, 0x5, YrTechnoTypeCtorEvent)
{
    E->pTechnoType = R->ESI<TechnoTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x711AE0, 0x5, YrTechnoTypeDtorEvent)
{
    E->pTechnoType = R->ECX<TechnoTypeClass*>();
}

BROADCAST_HOOK_EVENT(0x716132, 0x5, YrTechnoTypeLoadIniEvent)
{
    E->pTechnoType = R->EBP<TechnoTypeClass*>();
    E->pIni = R->Stack<CCINIClass*>(0x380);
}
BROADCAST_HOOK_EVENT(0x716123, 0x5, YrTechnoTypeLoadIniEvent)
{
    E->pTechnoType = R->EBP<TechnoTypeClass*>();
    E->pIni = R->Stack<CCINIClass*>(0x380);
}

BROADCAST_HOOK_EVENT(0x716DC0, 0x5, YrTechnoTypeSaveGameBeginEvent)
{
    E->pTechnoType = R->Stack<TechnoTypeClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTechnoType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x717094, 0x5, YrTechnoTypeSaveGameEndEvent)
{
    E->pTechnoType = reinterpret_cast<TechnoTypeClass*>(gSavingObject);
    E->stream = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x7162F0, 0x6, YrTechnoTypeLoadGameBeginEvent)
{
    E->pTechnoType = R->Stack<TechnoTypeClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);
}
BROADCAST_HOOK_EVENT(0x716DAC, 0xA, YrTechnoTypeLoadGameEndEvent)
{
    E->pTechnoType = reinterpret_cast<TechnoTypeClass*>(gSavingObject);
    E->stream = gSavingStream;
}
