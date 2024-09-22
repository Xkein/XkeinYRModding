#include "yr/event/object_event.h"
#include "yr/yr_hook.h"

// TechnoClass
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectReceiveDamageEvent, 0x701900, 0x702D1F)
BROADCAST_HOOK_EVENT(0x701900, 0x6, YrObjectReceiveDamageEvent)
{
    E->pObject                = R->ECX<ObjectClass*>();
    E->pDamage                = R->Stack<int*>(0x4);
    E->DistanceFromEpicenter  = R->Stack<int>(0x8);
    E->pWH                    = R->Stack<WarheadTypeClass*>(0xC);
    E->Attacker               = R->Stack<ObjectClass*>(0x10);
    E->IgnoreDefenses         = R->Stack<bool>(0x14);
    E->PreventPassengerEscape = R->Stack<bool>(0x18);
    E->pAttackingHouse        = R->Stack<HouseClass*>(0xC);
}

BROADCAST_HOOK_EVENT(0x5F4D53, 0x8, YrObjectLimboCheckedEvent)
{
    E->pObject = R->ESI<ObjectClass*>();
}

BROADCAST_HOOK_EVENT(0x5F4FC2, 0x6, YrObjectUnlimboCheckedEvent)
{
    E->pObject  = R->ESI<ObjectClass*>();
    E->pCrd     = R->Stack<CoordStruct*>(STACK_OFFSET(0x3C, 0x4));
    E->dFaceDir = R->Stack<DirType>(STACK_OFFSET(0x3C, 0x8));
}
