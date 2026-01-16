#pragma once

#include "yr/yr_event.h"
#include <GeneralDefinitions.h>

class SuperWeaponTypeClass;
class CCINIClass;
struct IStream;
class ObjectClass;

CLASS(HookEvent, BindJs)
class YrSuperWeaponTypeCtorEvent
{
public:
    PROPERTY()
    SuperWeaponTypeClass* pSuperWeaponType;
};

CLASS(HookEvent, BindJs)
class YrSuperWeaponTypeDtorEvent
{
public:
    PROPERTY()
    SuperWeaponTypeClass* pSuperWeaponType;
};

CLASS(HookEvent, BindJs)
class YrSuperWeaponTypeSaveGameBeginEvent
{
public:
    PROPERTY()
    SuperWeaponTypeClass* pSuperWeaponType;
    PROPERTY()
    IStream*              stream;
};

CLASS(HookEvent, BindJs)
class YrSuperWeaponTypeSaveGameEndEvent
{
public:
    PROPERTY()
    SuperWeaponTypeClass* pSuperWeaponType;
    PROPERTY()
    IStream*              stream;
};

CLASS(HookEvent, BindJs)
class YrSuperWeaponTypeLoadGameBeginEvent
{
public:
    PROPERTY()
    SuperWeaponTypeClass* pSuperWeaponType;
    PROPERTY()
    IStream*              stream;
};

CLASS(HookEvent, BindJs)
class YrSuperWeaponTypeLoadGameEndEvent
{
public:
    PROPERTY()
    SuperWeaponTypeClass* pSuperWeaponType;
    PROPERTY()
    IStream*              stream;
};

CLASS(HookEvent, BindJs)
class YrSuperWeaponTypeLoadIniEvent
{
public:
    PROPERTY()
    SuperWeaponTypeClass* pSuperWeaponType;
    PROPERTY()
    CCINIClass*           pIni;
};

CLASS(HookEvent, BindJs)
class YrSuperWeaponTypeMouseOverObjectEvent : public YrHookOverrideReturn<Action>
{
public:
    PROPERTY()
    SuperWeaponTypeClass* pSuperWeaponType;
    PROPERTY()
    CellStruct            cell;
    PROPERTY()
    ObjectClass*          pObjBelowMouse;
};
