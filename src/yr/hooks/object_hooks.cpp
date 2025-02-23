#include "yr/event/object_event.h"
#include "yr/yr_hook.h"
#include <FootClass.h>

// BEGIN hooks for ObjectClass::ReceiveDamage ===================================
// ObjectClass::ReceiveDamage
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectReceiveDamageEvent, 0x5F5390, 0x5F5465)
BROADCAST_HOOK_EVENT(0x5F5390, 0x5, YrObjectReceiveDamageEvent)
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
IMPL_HOOK_BROADCAST(YrObjectReceiveDamageEvent, 0x5F5390)
{
    switch (E->pObject->WhatAmI())
    {
        case AbstractType::Aircraft:
        case AbstractType::Building:
        case AbstractType::Infantry:
        case AbstractType::Unit:
        case AbstractType::Terrain:
        case AbstractType::VeinholeMonster:
            return 0;
    }
    return Broadcast_Impl_Default<YrObjectReceiveDamageEvent, 0x5F5390>(hookEvent, R, E);
}
// AircraftClass::ReceiveDamage
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectReceiveDamageEvent, 0x4165C0, 0x416609)
BROADCAST_HOOK_EVENT(0x4165C0, 0x7, YrObjectReceiveDamageEvent)
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
// BuildingClass::ReceiveDamage
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectReceiveDamageEvent, 0x442230, 0x4423A0)
BROADCAST_HOOK_EVENT(0x442230, 0x6, YrObjectReceiveDamageEvent)
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
// InfantryClass::ReceiveDamage
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectReceiveDamageEvent, 0x517FA0, 0x518058)
BROADCAST_HOOK_EVENT(0x517FA0, 0x6, YrObjectReceiveDamageEvent)
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
// UnitClass::ReceiveDamage
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectReceiveDamageEvent, 0x737C90, 0x737D2E)
BROADCAST_HOOK_EVENT(0x737C90, 0x5, YrObjectReceiveDamageEvent)
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
// TerrainClass::ReceiveDamage
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectReceiveDamageEvent, 0x71B920, 0x71B940)
BROADCAST_HOOK_EVENT(0x71B920, 0x7, YrObjectReceiveDamageEvent)
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
// VeinholeMonsterClass::ReceiveDamage
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectReceiveDamageEvent, 0x74D5D0, 0x74D63D)
BROADCAST_HOOK_EVENT(0x74D5D0, 0x8, YrObjectReceiveDamageEvent)
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
// END hooks for ObjectClass::ReceiveDamage ===================================

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

// BEGIN hooks for ObjectClass::MouseOverCell ===================================
// AircraftClass::MouseOverCell
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectMouseOverCellEvent, 0x417F83, 0x417F94)
BROADCAST_HOOK_EVENT(0x417F83, 0x6, YrObjectMouseOverCellEvent)
{
    E->pObject     = R->ECX<ObjectClass*>();
    E->cell        = *R->Stack<CellStruct*>(STACK_OFFSET(0x4, 0x4));
    E->checkFog    = R->Stack<bool>(STACK_OFFSET(0x4, 0x8));
    E->ignoreForce = R->Stack<bool>(STACK_OFFSET(0x4, 0xC));
}
// BuildingClass::MouseOverCell
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectMouseOverCellEvent, 0x447540, 0x447560)
BROADCAST_HOOK_EVENT(0x447540, 0x5, YrObjectMouseOverCellEvent)
{
    E->pObject     = R->ECX<ObjectClass*>();
    E->cell        = *R->Stack<CellStruct*>(0x4);
    E->checkFog    = R->Stack<bool>(0x8);
    E->ignoreForce = R->Stack<bool>(0xC);
}
// InfantryClass::MouseOverCell
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectMouseOverCellEvent, 0x51F800, 0x51F81F)
BROADCAST_HOOK_EVENT(0x51F800, 0x5, YrObjectMouseOverCellEvent)
{
    E->pObject     = R->ECX<ObjectClass*>();
    E->cell        = *R->Stack<CellStruct*>(0x4);
    E->checkFog    = R->Stack<bool>(0x8);
    E->ignoreForce = R->Stack<bool>(0xC);
}
// UnitClass::MouseOverCell
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectMouseOverCellEvent, 0x7404B0, 0x7404D1)
BROADCAST_HOOK_EVENT(0x7404B0, 0x5, YrObjectMouseOverCellEvent)
{
    E->pObject     = R->ECX<ObjectClass*>();
    E->cell        = *R->Stack<CellStruct*>(0x4);
    E->checkFog    = R->Stack<bool>(0x8);
    E->ignoreForce = R->Stack<bool>(0xC);
}
// END hooks for ObjectClass::MouseOverCell ===================================

// BEGIN hooks for ObjectClass::MouseOverObject ===================================
// AircraftClass::MouseOverObject
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectMouseOverObjectEvent, 0x417CC0, 0x417CE6)
BROADCAST_HOOK_EVENT(0x417CC0, 0x5, YrObjectMouseOverObjectEvent)
{
    E->pObject     = R->ECX<ObjectClass*>();
    E->pTarget     = R->Stack<ObjectClass*>(0x4);
    E->ignoreForce = R->Stack<bool>(0x8);
}
// BuildingClass::MouseOverObject
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectMouseOverObjectEvent, 0x447210, 0x447230)
BROADCAST_HOOK_EVENT(0x447210, 0x5, YrObjectMouseOverObjectEvent)
{
    E->pObject     = R->ECX<ObjectClass*>();
    E->pTarget     = R->Stack<ObjectClass*>(0x4);
    E->ignoreForce = R->Stack<bool>(0x8);
}
// InfantryClass::MouseOverObject
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectMouseOverObjectEvent, 0x51E3B0, 0x51E45F)
BROADCAST_HOOK_EVENT(0x51E3B0, 0x7, YrObjectMouseOverObjectEvent)
{
    E->pObject     = R->ECX<ObjectClass*>();
    E->pTarget     = R->Stack<ObjectClass*>(0x4);
    E->ignoreForce = R->Stack<bool>(0x8);
}
// UnitClass::MouseOverObject
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectMouseOverObjectEvent, 0x73FD50, 0x73FD78)
BROADCAST_HOOK_EVENT(0x73FD50, 0x7, YrObjectMouseOverObjectEvent)
{
    E->pObject     = R->ECX<ObjectClass*>();
    E->pTarget     = R->Stack<ObjectClass*>(0x4);
    E->ignoreForce = R->Stack<bool>(0x8);
}
// END hooks for ObjectClass::MouseOverObject ===================================

// BEGIN hooks for ObjectClass::CellClickedAction ===================================
// AircraftClass::CellClickedAction
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectCellClickedActionEvent, 0x417C80, 0x417C99)
BROADCAST_HOOK_EVENT(0x417C80, 0x8, YrObjectCellClickedActionEvent)
{
    E->pObject = R->ECX<ObjectClass*>();
    E->action  = R->Stack<Action>(0x4);
    E->cell    = *R->Stack<CellStruct*>(0x8);
}
// BuildingClass::CellClickedAction
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectCellClickedActionEvent, 0x4436F0, 0x44372C)
BROADCAST_HOOK_EVENT(0x4436F0, 0x7, YrObjectCellClickedActionEvent)
{
    E->pObject = R->ECX<ObjectClass*>();
    E->action  = R->Stack<Action>(0x4);
    E->cell    = *R->Stack<CellStruct*>(0x8);
}
// InfantryClass::CellClickedAction
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectCellClickedActionEvent, 0x51F250, 0x51F28C)
BROADCAST_HOOK_EVENT(0x51F250, 0x5, YrObjectCellClickedActionEvent)
{
    E->pObject = R->ECX<ObjectClass*>();
    E->action  = R->Stack<Action>(0x4);
    E->cell    = *R->Stack<CellStruct*>(0x8);
}
// UnitClass::CellClickedAction
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectCellClickedActionEvent, 0x738910, 0x73893A)
BROADCAST_HOOK_EVENT(0x738910, 0x5, YrObjectCellClickedActionEvent)
{
    E->pObject = R->ECX<ObjectClass*>();
    E->action  = R->Stack<Action>(0x4);
    E->cell    = *R->Stack<CellStruct*>(0x8);
}
// END hooks for ObjectClass::CellClickedAction ===================================

// BEGIN hooks for ObjectClass::ObjectClickedAction ===================================
// AircraftClass::ObjectClickedAction
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectObjectClickedActionEvent, 0x417BD0, 0x417C0F)
BROADCAST_HOOK_EVENT(0x417BD0, 0x5, YrObjectObjectClickedActionEvent)
{
    E->pObject = R->ECX<ObjectClass*>();
    E->action  = R->Stack<Action>(0x4);
    E->pTarget = R->Stack<ObjectClass*>(0x8);
}
// BuildingClass::ObjectClickedAction
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectObjectClickedActionEvent, 0x443414, 0x44344D)
BROADCAST_HOOK_EVENT(0x443414, 0x6, YrObjectObjectClickedActionEvent)
{
    E->pObject = R->ECX<ObjectClass*>();
    E->action  = R->Stack<Action>(0x4);
    E->pTarget = R->Stack<ObjectClass*>(0x8);
}
// InfantryClass::ObjectClickedAction
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectObjectClickedActionEvent, 0x51F190, 0x51F1D5)
BROADCAST_HOOK_EVENT(0x51F190, 0x5, YrObjectObjectClickedActionEvent)
{
    E->pObject = R->ECX<ObjectClass*>();
    E->action  = R->Stack<Action>(0x4);
    E->pTarget = R->Stack<ObjectClass*>(0x8);
}
// UnitClass::ObjectClickedAction
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrObjectObjectClickedActionEvent, 0x738890, 0x7388E8)
BROADCAST_HOOK_EVENT(0x738890, 0x5, YrObjectObjectClickedActionEvent)
{
    E->pObject = R->ECX<ObjectClass*>();
    E->action  = R->Stack<Action>(0x4);
    E->pTarget = R->Stack<ObjectClass*>(0x8);
}
// END hooks for ObjectClass::ObjectClickedAction ===================================
