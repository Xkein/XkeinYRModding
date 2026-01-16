#pragma once

#include "yr/yr_event.h"
#include <GeneralDefinitions.h>
#include <optional>

class ObjectClass;
class WarheadTypeClass;
class HouseClass;

CLASS(HookEvent, BindJs)
class YrObjectReceiveDamageEvent : public YrHookOverrideReturn<DamageState>
{
public:
    PROPERTY()
    ObjectClass*      pObject;
    PROPERTY()
    int*              pDamage;
    PROPERTY()
    int               DistanceFromEpicenter;
    PROPERTY()
    WarheadTypeClass* pWH;
    PROPERTY()
    ObjectClass*      Attacker;
    PROPERTY()
    bool              IgnoreDefenses;
    PROPERTY()
    bool              PreventPassengerEscape;
    PROPERTY()
    HouseClass*       pAttackingHouse;
};

// YrObjectLimboCheckedEvent raised when object is really need Limbo
CLASS(HookEvent, BindJs)
struct YrObjectLimboCheckedEvent
{
    PROPERTY()
    ObjectClass* pObject;
};

// YrObjectUnlimboCheckedEvent raised when object is really need Unlimbo
CLASS(HookEvent, BindJs)
struct YrObjectUnlimboCheckedEvent
{
    PROPERTY()
    ObjectClass* pObject;
    PROPERTY()
    CoordStruct* pCrd;
    PROPERTY()
    DirType      dFaceDir;
};

CLASS(HookEvent, BindJs)
class YrObjectMouseOverCellEvent : public YrHookOverrideReturn<Action>
{
public:
    PROPERTY()
    ObjectClass* pObject;
    PROPERTY()
    CellStruct   cell;
    PROPERTY()
    bool         checkFog;
    PROPERTY()
    bool         ignoreForce;
};

CLASS(HookEvent, BindJs)
class YrObjectMouseOverObjectEvent : public YrHookOverrideReturn<Action>
{
public:
    PROPERTY()
    ObjectClass*       pObject;
    PROPERTY()
    ObjectClass const* pTarget;
    PROPERTY()
    bool               ignoreForce;
};

CLASS(HookEvent, BindJs)
class YrObjectCellClickedActionEvent : public YrHookOverrideReturn<bool>
{
public:
    PROPERTY()
    ObjectClass* pObject;
    PROPERTY()
    Action       action;
    PROPERTY()
    CellStruct   cell;
    // CellStruct*  pCell1; i dont know what it really means...
};

CLASS(HookEvent, BindJs)
class YrObjectObjectClickedActionEvent : public YrHookOverrideReturn<bool>
{
public:
    PROPERTY()
    ObjectClass* pObject;
    PROPERTY()
    Action       action;
    PROPERTY()
    ObjectClass* pTarget;
};

CLASS(HookEvent, BindJs)
class YrObjectGetFLHEvent : public YrHookOverrideReturn<CoordStruct*>
{
public:
    PROPERTY()
    ObjectClass* pObject;
    PROPERTY()
    CoordStruct* pDest;
    PROPERTY()
    int idxWeapon;
    PROPERTY()
    CoordStruct BaseCoords;
    
    void OverrideReturn(CoordStruct result) {
        *pDest = result;
        YrHookOverrideReturn<CoordStruct*>::OverrideReturn(pDest);
    }
};
