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

BROADCAST_HOOK_EVENT(0x4253B0, 0x5, YrAnimSaveGameBeginEvent)
{
    E->pAnim  = R->Stack<AnimClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);

    gSavingObject = E->pAnim;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x4253FF, 0x5, YrAnimSaveGameEndEvent)
{
    E->pAnim  = reinterpret_cast<AnimClass*>(gSavingObject);
    E->stream = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x425280, 0x5, YrAnimLoadGameBeginEvent)
{
    E->pAnim  = R->Stack<AnimClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);

    gSavingObject = E->pAnim;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT_AGAIN(0x4253A2, 0x7, YrAnimLoadGameEndEvent, 0x425391)
BROADCAST_HOOK_EVENT_AGAIN(0x425358, 0x7, YrAnimLoadGameEndEvent, 0x425391)
BROADCAST_HOOK_EVENT(0x425391, 0x7, YrAnimLoadGameEndEvent)
{
    E->pAnim  = reinterpret_cast<AnimClass*>(gSavingObject);
    E->stream = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x42784B, 0x5, YrAnimTypeCtorEvent)
{
    E->pAnimType = R->EAX<AnimTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x428EA8, 0x5, YrAnimTypeDtorEvent)
{
    E->pAnimType = R->ECX<AnimTypeClass*>();
}

BROADCAST_HOOK_EVENT(0x428970, 0x8, YrAnimTypeSaveGameBeginEvent)
{
    E->pAnimType = R->Stack<AnimTypeClass*>(0x4);
    E->stream    = R->Stack<IStream*>(0x8);

    gSavingObject = E->pAnimType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x42898A, 0x5, YrAnimTypeSaveGameEndEvent)
{
    E->pAnimType = reinterpret_cast<AnimTypeClass*>(gSavingObject);
    E->stream    = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x428800, 0xA, YrAnimTypeLoadGameBeginEvent)
{
    E->pAnimType = R->Stack<AnimTypeClass*>(0x4);
    E->stream    = R->Stack<IStream*>(0x8);

    gSavingObject = E->pAnimType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT_AGAIN(0x42892C, 0x6, YrAnimTypeLoadGameEndEvent, 0x428958)
BROADCAST_HOOK_EVENT(0x428958, 0x6, YrAnimTypeLoadGameEndEvent)
{
    E->pAnimType = reinterpret_cast<AnimTypeClass*>(gSavingObject);
    E->stream    = gSavingStream;
}

BROADCAST_HOOK_EVENT_AGAIN(0x4287E9, 0xA, YrAnimTypeLoadIniEvent, 0x4287DC)
BROADCAST_HOOK_EVENT(0x4287DC, 0xA, YrAnimTypeLoadIniEvent)
{
    E->pAnimType = R->ESI<AnimTypeClass*>();
    E->pIni      = R->Stack<CCINIClass*>(0xBC);
}
