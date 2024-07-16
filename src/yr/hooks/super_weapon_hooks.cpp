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

BROADCAST_HOOK_EVENT(0x6CE6F6, 0x5, YrSuperWeaponTypeCtorEvent)
{
    E->pSuperWeaponType = R->EAX<SuperWeaponTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x6CEFE0, 0x8, YrSuperWeaponTypeDtorEvent)
{
    E->pSuperWeaponType = R->ECX<SuperWeaponTypeClass*>();
}
