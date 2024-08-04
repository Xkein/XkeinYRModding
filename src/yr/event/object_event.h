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
    ObjectClass*      pObject;
    int*              pDamage;
    int               DistanceFromEpicenter;
    WarheadTypeClass* pWH;
    ObjectClass*      Attacker;
    bool              IgnoreDefenses;
    bool              PreventPassengerEscape;
    HouseClass*       pAttackingHouse;
};

// YrObjectLimboCheckedEvent raised when object is really need Limbo
CLASS(HookEvent)
struct YrObjectLimboCheckedEvent
{
    ObjectClass* pObject;
};

// YrObjectUnlimboCheckedEvent raised when object is really need Unlimbo
CLASS(HookEvent)
struct YrObjectUnlimboCheckedEvent
{
    ObjectClass* pObject;
    CoordStruct* pCrd;
    DirType      dFaceDir;
};
