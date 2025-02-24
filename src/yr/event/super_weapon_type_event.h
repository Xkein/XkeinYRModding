#pragma once

#include "yr/yr_event.h"
#include <GeneralDefinitions.h>

class SuperWeaponTypeClass;
class CCINIClass;
struct IStream;
class ObjectClass;

CLASS(HookEvent)
class YrSuperWeaponTypeCtorEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
};

CLASS(HookEvent)
class YrSuperWeaponTypeDtorEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
};

CLASS(HookEvent)
class YrSuperWeaponTypeSaveGameBeginEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
    IStream*              stream;
};

CLASS(HookEvent)
class YrSuperWeaponTypeSaveGameEndEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
    IStream*              stream;
};

CLASS(HookEvent)
class YrSuperWeaponTypeLoadGameBeginEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
    IStream*              stream;
};

CLASS(HookEvent)
class YrSuperWeaponTypeLoadGameEndEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
    IStream*              stream;
};

CLASS(HookEvent)
class YrSuperWeaponTypeLoadIniEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
    CCINIClass*           pIni;
};

CLASS(HookEvent)
class YrSuperWeaponTypeMouseOverObjectEvent : public YrHookOverrideReturn<Action>
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
    CellStruct            cell;
    ObjectClass*          pObjBelowMouse;
};
