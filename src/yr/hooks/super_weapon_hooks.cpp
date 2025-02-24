#include "yr/event/super_event.h"
#include "yr/event/super_weapon_type_event.h"
#include "yr/yr_hook.h"

#include <FootClass.h>
#include <SuperClass.h>
#include <SuperWeaponTypeClass.h>

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

BROADCAST_HOOK_EVENT(0x6CB10E, 0x7, YrSuperCtorEvent)
{
    E->pSuper = R->ESI<SuperClass*>();
}
BROADCAST_HOOK_EVENT(0x6CB120, 0x7, YrSuperDtorEvent)
{
    E->pSuper = R->ECX<SuperClass*>();
}
BROADCAST_HOOK_EVENT(0x6CDFD0, 0x8, YrSuperSaveGameBeginEvent)
{
    E->pSuper = R->Stack<SuperClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);

    gSavingObject = E->pSuper;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x6CDFEA, 0x5, YrSuperSaveGameEndEvent)
{
    E->pSuper = reinterpret_cast<SuperClass*>(gSavingObject);
    E->stream = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x6CDEF0, 0x5, YrSuperLoadGameBeginEvent)
{
    E->pSuper = R->Stack<SuperClass*>(0x4);
    E->stream = R->Stack<IStream*>(0x8);

    gSavingObject = E->pSuper;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x6CDFC7, 0x5, YrSuperLoadGameEndEvent)
{
    E->pSuper = reinterpret_cast<SuperClass*>(gSavingObject);
    E->stream = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x6CC390, 0x6, YrSuperLaunchEvent)
{
    E->pSuper   = R->ECX<SuperClass*>();
    E->pCell    = R->Stack<CellStruct const*>(0x4);
    E->isPlayer = R->Stack<bool>(0x8);
}

BROADCAST_HOOK_EVENT(0x6CE6F6, 0x5, YrSuperWeaponTypeCtorEvent)
{
    E->pSuperWeaponType = R->EAX<SuperWeaponTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x6CEFE0, 0x8, YrSuperWeaponTypeDtorEvent)
{
    E->pSuperWeaponType = R->ECX<SuperWeaponTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x6CE8D0, 0x8, YrSuperWeaponTypeSaveGameBeginEvent)
{
    E->pSuperWeaponType = R->Stack<SuperWeaponTypeClass*>(0x4);
    E->stream           = R->Stack<IStream*>(0x8);

    gSavingObject = E->pSuperWeaponType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x6CE8EA, 0x5, YrSuperWeaponTypeSaveGameEndEvent)
{
    E->pSuperWeaponType = reinterpret_cast<SuperWeaponTypeClass*>(gSavingObject);
    E->stream           = gSavingStream;
}
BROADCAST_HOOK_EVENT(0x6CE800, 0xA, YrSuperWeaponTypeLoadGameBeginEvent)
{
    E->pSuperWeaponType = R->Stack<SuperWeaponTypeClass*>(0x4);
    E->stream           = R->Stack<IStream*>(0x8);

    gSavingObject = E->pSuperWeaponType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x6CE8C5, 0x5, YrSuperWeaponTypeLoadGameEndEvent)
{
    E->pSuperWeaponType = reinterpret_cast<SuperWeaponTypeClass*>(gSavingObject);
    E->stream           = gSavingStream;
}

BROADCAST_HOOK_EVENT_AGAIN(0x6CEE50, 0xA, YrSuperWeaponTypeLoadIniEvent, 0x6CEE43)
BROADCAST_HOOK_EVENT(0x6CEE43, 0xA, YrSuperWeaponTypeLoadIniEvent)
{
    E->pSuperWeaponType = R->EBP<SuperWeaponTypeClass*>();
    E->pIni             = R->Stack<CCINIClass*>(0x3FC);
}

IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrSuperWeaponTypeMouseOverObjectEvent, 0x6CEF84, 0x6CEFD9)
BROADCAST_HOOK_EVENT(0x6CEF84, 0x7, YrSuperWeaponTypeMouseOverObjectEvent)
{
    E->pSuperWeaponType = R->ECX<SuperWeaponTypeClass*>();
    E->cell             = R->Stack<CellStruct>(STACK_OFFSET(0x8, 0x4));
    E->pObjBelowMouse   = R->Stack<ObjectClass*>(STACK_OFFSET(0x8, 0x8));
}
