#pragma once

#include "yr/yr_event.h"

class WeaponTypeClass;
class WarheadTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrWeaponTypeCtorEvent
{
public:
    WeaponTypeClass* pWeaponType;
};

CLASS(HookEvent)
class YrWeaponTypeDtorEvent
{
public:
    WeaponTypeClass* pWeaponType;
};

CLASS(HookEvent)
class YrWeaponTypeSaveGameBeginEvent
{
public:
    WeaponTypeClass* pWeaponType;
    IStream*         stream;
};

CLASS(HookEvent)
class YrWeaponTypeSaveGameEndEvent
{
public:
    WeaponTypeClass* pWeaponType;
    IStream*         stream;
};

CLASS(HookEvent)
class YrWeaponTypeLoadGameBeginEvent
{
public:
    WeaponTypeClass* pWeaponType;
    IStream*         stream;
};

CLASS(HookEvent)
class YrWeaponTypeLoadGameEndEvent
{
public:
    WeaponTypeClass* pWeaponType;
    IStream*         stream;
};

CLASS(HookEvent)
class YrWeaponTypeLoadIniEvent
{
public:
    WeaponTypeClass* pWeaponType;
    CCINIClass*      pIni;
};

CLASS(HookEvent)
class YrWarheadTypeCtorEvent
{
public:
    WarheadTypeClass* pWarheadType;
};

CLASS(HookEvent)
class YrWarheadTypeDtorEvent
{
public:
    WarheadTypeClass* pWarheadType;
};

CLASS(HookEvent)
class YrWarheadTypeSaveGameBeginEvent
{
public:
    WarheadTypeClass* pWarheadType;
    IStream*          stream;
};

CLASS(HookEvent)
class YrWarheadTypeSaveGameEndEvent
{
public:
    WarheadTypeClass* pWarheadType;
    IStream*          stream;
};

CLASS(HookEvent)
class YrWarheadTypeLoadGameBeginEvent
{
public:
    WarheadTypeClass* pWarheadType;
    IStream*          stream;
};

CLASS(HookEvent)
class YrWarheadTypeLoadGameEndEvent
{
public:
    WarheadTypeClass* pWarheadType;
    IStream*          stream;
};

CLASS(HookEvent)
class YrWarheadTypeLoadIniEvent
{
public:
    WarheadTypeClass* pWarheadType;
    CCINIClass*       pIni;
};
