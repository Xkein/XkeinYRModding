#include "yr/event/anim_event.h"
#include "yr/event/anim_type_event.h"
#include "yr/yr_hook.h"

#include <AnimClass.h>
#include <AnimTypeClass.h>
#include <FootClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT_AGAIN(0x422126, 0x5, YrAnimCtorEvent, 0x422707)
BROADCAST_HOOK_EVENT_AGAIN(0x4228D2, 0x5, YrAnimCtorEvent, 0x422707)
BROADCAST_HOOK_EVENT(0x422707, 0x5, YrAnimCtorEvent)
{
    E->pAnim = R->ESI<AnimClass*>();
}

BROADCAST_HOOK_EVENT(0x4228E0, 0x5, YrAnimDtorEvent)
{
    E->pAnim = R->ECX<AnimClass*>();
}

BROADCAST_HOOK_EVENT(0x42784B, 0x5, YrAnimTypeCtorEvent)
{
    E->pAnimType = R->EAX<AnimTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x428EA8, 0x5, YrAnimTypeDtorEvent)
{
    E->pAnimType = R->ECX<AnimTypeClass*>();
}

BROADCAST_HOOK_EVENT_AGAIN(0x4287E9, 0xA, YrAnimTypeLoadIniEvent, 0x4287DC)
BROADCAST_HOOK_EVENT(0x4287DC, 0xA, YrAnimTypeLoadIniEvent)
{
    E->pAnimType = R->ESI<AnimTypeClass*>();
    E->pIni      = R->Stack<CCINIClass*>(0xBC);
}
