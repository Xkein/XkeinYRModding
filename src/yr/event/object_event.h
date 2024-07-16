#pragma once

#include "yr/yr_event.h"
#include <GeneralDefinitions.h>
#include <optional>

class ObjectClass;
class WarheadTypeClass;
class HouseClass;

CLASS(HookEvent)
class YrObjectReceiveDamageEvent : public YrHookOverrideReturn<DamageState>
{
public:
    ObjectClass*      pObject {nullptr};
    int*              pDamage {nullptr};
    int               DistanceFromEpicenter {false};
    WarheadTypeClass* pWH {nullptr};
    ObjectClass*      Attacker {nullptr};
    bool              IgnoreDefenses {false};
    bool              PreventPassengerEscape {false};
    HouseClass*       pAttackingHouse {nullptr};
};
