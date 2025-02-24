#include "yr/event/techno_event.h"
#include "yr/event/techno_type_event.h"
#include "yr/yr_hook.h"

#include <FootClass.h>
#include <TechnoClass.h>
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
    E->stream  = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTechno;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x70C264, 0x5, YrTechnoSaveGameEndEvent)
{
    E->pTechno = reinterpret_cast<TechnoClass*>(gSavingObject);
    E->stream  = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x70BF50, 0x5, YrTechnoLoadGameBeginEvent)
{
    E->pTechno = R->Stack<TechnoClass*>(0x4);
    E->stream  = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTechno;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x70C249, 0x5, YrTechnoLoadGameEndEvent)
{
    E->pTechno = reinterpret_cast<TechnoClass*>(gSavingObject);
    E->stream  = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x711835, 0x5, YrTechnoTypeCtorEvent)
{
    E->pTechnoType = R->ESI<TechnoTypeClass*>();
}
BROADCAST_HOOK_EVENT(0x711AE0, 0x5, YrTechnoTypeDtorEvent)
{
    E->pTechnoType = R->ECX<TechnoTypeClass*>();
}

BROADCAST_HOOK_EVENT_AGAIN(0x716132, 0x5, YrTechnoTypeLoadIniEvent, 0x716123)
BROADCAST_HOOK_EVENT(0x716123, 0x5, YrTechnoTypeLoadIniEvent)
{
    E->pTechnoType = R->EBP<TechnoTypeClass*>();
    E->pIni        = R->Stack<CCINIClass*>(0x380);
}

BROADCAST_HOOK_EVENT(0x716DC0, 0x5, YrTechnoTypeSaveGameBeginEvent)
{
    E->pTechnoType = R->Stack<TechnoTypeClass*>(0x4);
    E->stream      = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTechnoType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x717094, 0x5, YrTechnoTypeSaveGameEndEvent)
{
    E->pTechnoType = reinterpret_cast<TechnoTypeClass*>(gSavingObject);
    E->stream      = gSavingStream;
}

BROADCAST_HOOK_EVENT(0x7162F0, 0x6, YrTechnoTypeLoadGameBeginEvent)
{
    E->pTechnoType = R->Stack<TechnoTypeClass*>(0x4);
    E->stream      = R->Stack<IStream*>(0x8);

    gSavingObject = E->pTechnoType;
    gSavingStream = E->stream;
}
BROADCAST_HOOK_EVENT(0x716DAC, 0xA, YrTechnoTypeLoadGameEndEvent)
{
    E->pTechnoType = reinterpret_cast<TechnoTypeClass*>(gSavingObject);
    E->stream      = gSavingStream;
}

// BEGIN hooks for TechnoClass::Fire ===================================
// TechnoClass::Fire
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoFireEvent, 0x6FDD50, 0x6FDE0B)
BROADCAST_HOOK_EVENT(0x6FDD50, 0x6, YrTechnoFireEvent)
{
    E->pTechno      = R->ECX<TechnoClass*>();
    E->pTarget      = R->Stack<AbstractClass*>(0x4);
    E->nWeaponIndex = R->Stack<int>(0x8);
}
IMPL_HOOK_BROADCAST(YrTechnoFireEvent, 0x6FDD50)
{
    switch (E->pTechno->WhatAmI())
    {
        case AbstractType::Aircraft:
        case AbstractType::Infantry:
        case AbstractType::Unit:
            return 0;
    }
    return Broadcast_Impl_Default<YrTechnoFireEvent, 0x6FDD50>(hookEvent, R, E);
}
// AircraftClass::Fire
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoFireEvent, 0x415EE0, 0x415F05)
BROADCAST_HOOK_EVENT(0x415EE0, 0x6, YrTechnoFireEvent)
{
    E->pTechno      = R->ECX<TechnoClass*>();
    E->pTarget      = R->Stack<AbstractClass*>(0x4);
    E->nWeaponIndex = R->Stack<int>(0x8);
}
// InfantryClass::Fire
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoFireEvent, 0x51DF60, 0x51DFE0)
BROADCAST_HOOK_EVENT(0x51DF60, 0x5, YrTechnoFireEvent)
{
    E->pTechno      = R->ECX<TechnoClass*>();
    E->pTarget      = R->Stack<AbstractClass*>(0x4);
    E->nWeaponIndex = R->Stack<int>(0x8);
}
// UnitClass::Fire
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoFireEvent, 0x741340, 0x74136D)
BROADCAST_HOOK_EVENT(0x741340, 0x6, YrTechnoFireEvent)
{
    E->pTechno      = R->ECX<TechnoClass*>();
    E->pTarget      = R->Stack<AbstractClass*>(0x4);
    E->nWeaponIndex = R->Stack<int>(0x8);
}
// END hooks for TechnoClass::Fire ===================================

// BEGIN hooks for TechnoClass::SelectWeapon ===================================
// TechnoClass::SelectWeapon
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoSelectWeaponEvent, 0x6F3330, 0x6F3376)
BROADCAST_HOOK_EVENT(0x6F3330, 0x5, YrTechnoSelectWeaponEvent)
{
    E->pTechno = R->ECX<TechnoClass*>();
    E->pTarget = R->Stack<AbstractClass*>(0x4);
}
IMPL_HOOK_BROADCAST(YrTechnoSelectWeaponEvent, 0x6F3330)
{
    switch (E->pTechno->WhatAmI())
    {
        case AbstractType::Infantry:
        case AbstractType::Unit:
            return 0;
    }
    return Broadcast_Impl_Default<YrTechnoSelectWeaponEvent, 0x6F3330>(hookEvent, R, E);
}
// InfantryClass::SelectWeapon
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoSelectWeaponEvent, 0x5218E0, 0x521914)
BROADCAST_HOOK_EVENT(0x5218E0, 0x9, YrTechnoSelectWeaponEvent)
{
    E->pTechno = R->ECX<TechnoClass*>();
    E->pTarget = R->Stack<AbstractClass*>(0x4);
}
// UnitClass::SelectWeapon
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoSelectWeaponEvent, 0x746CD0, 0x746CF0)
BROADCAST_HOOK_EVENT(0x746CD0, 0x6, YrTechnoSelectWeaponEvent)
{
    E->pTechno = R->ECX<TechnoClass*>();
    E->pTarget = R->Stack<AbstractClass*>(0x4);
}
// END hooks for TechnoClass::SelectWeapon ===================================

// BEGIN hooks for TechnoClass::GetFireError ===================================
// AircraftClass::GetFireError
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoGetFireErrorEvent, 0x41A9E0, 0x41AA1B)
BROADCAST_HOOK_EVENT(0x41A9E0, 0x5, YrTechnoGetFireErrorEvent)
{
    E->pTechno     = R->ECX<TechnoClass*>();
    E->pTarget     = R->Stack<AbstractClass*>(0x4);
    E->weaponIndex = R->Stack<int>(0x8);
    E->ignoreRange = R->Stack<bool>(0xC);
}
// BuildingClass::GetFireError
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoGetFireErrorEvent, 0x447F10, 0x447F6C)
BROADCAST_HOOK_EVENT(0x447F10, 0x5, YrTechnoGetFireErrorEvent)
{
    E->pTechno     = R->ECX<TechnoClass*>();
    E->pTarget     = R->Stack<AbstractClass*>(0x4);
    E->weaponIndex = R->Stack<int>(0x8);
    E->ignoreRange = R->Stack<bool>(0xC);
}
// InfantryClass::GetFireError
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoGetFireErrorEvent, 0x51C8B0, 0x51C8FB)
BROADCAST_HOOK_EVENT(0x51C8B0, 0x6, YrTechnoGetFireErrorEvent)
{
    E->pTechno     = R->ECX<TechnoClass*>();
    E->pTarget     = R->Stack<AbstractClass*>(0x4);
    E->weaponIndex = R->Stack<int>(0x8);
    E->ignoreRange = R->Stack<bool>(0xC);
}
// UnitClass::GetFireError
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoGetFireErrorEvent, 0x740FD0, 0x740FEF)
BROADCAST_HOOK_EVENT(0x740FD0, 0x5, YrTechnoGetFireErrorEvent)
{
    E->pTechno     = R->ECX<TechnoClass*>();
    E->pTarget     = R->Stack<AbstractClass*>(0x4);
    E->weaponIndex = R->Stack<int>(0x8);
    E->ignoreRange = R->Stack<bool>(0xC);
}
// END hooks for TechnoClass::GetFireError ===================================
