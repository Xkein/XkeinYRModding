#include "yr/event/weapon_type_event.h"
#include "yr/yr_hook.h"
#include <WarheadTypeClass.h>
#include <WeaponTypeClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x771EE9, 0x5, YrWeaponTypeCtorEvent)
{
    E->pWeaponType = R->ESI<WeaponTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x77311D, 0x6, YrWeaponTypeDtorEvent)
{
    E->pWeaponType = R->ESI<WeaponTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x772EB0, 0x5, YrWeaponTypeSaveGameBeginEvent)
{
    E->pWeaponType = R->Stack<WeaponTypeClass*>(0x4);
    E->stream      = R->Stack<IStream*>(0x8);

    gSavingObject = E->pWeaponType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x772F8C, 0x5, YrWeaponTypeSaveGameEndEvent)
{
    E->pWeaponType = reinterpret_cast<WeaponTypeClass*>(gSavingObject);
    E->stream      = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x772CD0, 0x7, YrWeaponTypeLoadGameBeginEvent)
{
    E->pWeaponType = R->Stack<WeaponTypeClass*>(0x4);
    E->stream      = R->Stack<IStream*>(0x8);

    gSavingObject = E->pWeaponType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x772EA6, 0x6, YrWeaponTypeLoadGameEndEvent)
{
    E->pWeaponType = reinterpret_cast<WeaponTypeClass*>(gSavingObject);
    E->stream      = gSavingStream;
}
BROADCAST_HOOK_EVENT_AGAIN(0x7729C7, 0x5, YrWeaponTypeLoadIniEvent, 0x7729B0)
BROADCAST_HOOK_EVENT_AGAIN(0x7729D6, 0x5, YrWeaponTypeLoadIniEvent, 0x7729B0)
BROADCAST_HOOK_EVENT(0x7729B0, 0x5, YrWeaponTypeLoadIniEvent)
{
    E->pWeaponType = R->ESI<WeaponTypeClass*>();
    E->pIni        = R->Stack<CCINIClass*>(0xE4);
}

BROADCAST_HOOK_EVENT(0x75D1A9, 0x7, YrWarheadTypeCtorEvent)
{
    E->pWarheadType = R->EBP<WarheadTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x75E5C8, 0x6, YrWarheadTypeDtorEvent)
{
    E->pWarheadType = R->ESI<WarheadTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x75E2C0, 0x5, YrWarheadTypeSaveGameBeginEvent)
{
    E->pWarheadType = R->Stack<WarheadTypeClass*>(0x4);
    E->stream       = R->Stack<IStream*>(0x8);

    gSavingObject = E->pWarheadType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x75E39C, 0x5, YrWarheadTypeSaveGameEndEvent)
{
    E->pWarheadType = reinterpret_cast<WarheadTypeClass*>(gSavingObject);
    E->stream       = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x75E0C0, 0x8, YrWarheadTypeLoadGameBeginEvent)
{
    E->pWarheadType = R->Stack<WarheadTypeClass*>(0x4);
    E->stream       = R->Stack<IStream*>(0x8);

    gSavingObject = E->pWarheadType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x75E2AE, 0x7, YrWarheadTypeLoadGameEndEvent)
{
    E->pWarheadType = reinterpret_cast<WarheadTypeClass*>(gSavingObject);
    E->stream       = gSavingStream;
}
BROADCAST_HOOK_EVENT_AGAIN(0x75DEAF, 0x5, YrWarheadTypeLoadIniEvent, 0x75DEA0)
BROADCAST_HOOK_EVENT(0x75DEA0, 0x5, YrWarheadTypeLoadIniEvent)
{
    E->pWarheadType = R->ESI<WarheadTypeClass*>();
    E->pIni         = R->Stack<CCINIClass*>(0x150);
}
