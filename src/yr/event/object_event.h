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

CLASS(HookEvent)
class YrObjectMouseOverCellEvent : public YrHookOverrideReturn<Action>
{
public:
    ObjectClass* pObject;
    CellStruct   cell;
    bool         checkFog;
    bool         ignoreForce;
};

CLASS(HookEvent)
class YrObjectMouseOverObjectEvent : public YrHookOverrideReturn<Action>
{
public:
    ObjectClass*       pObject;
    ObjectClass const* pTarget;
    bool               ignoreForce;
};

CLASS(HookEvent)
class YrObjectCellClickedActionEvent : public YrHookOverrideReturn<bool>
{
public:
    ObjectClass* pObject;
    Action       action;
    CellStruct   cell;
    // CellStruct*  pCell1; i dont know what it really means...
};

CLASS(HookEvent)
class YrObjectObjectClickedActionEvent : public YrHookOverrideReturn<bool>
{
public:
    ObjectClass* pObject;
    Action       action;
    ObjectClass* pTarget;
};
