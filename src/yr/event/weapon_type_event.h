#pragma once

#include "yr/yr_event.h"

class WeaponTypeClass;
class WarheadTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrWeaponTypeCtorEvent
{
public:
    PROPERTY()
    WeaponTypeClass* pWeaponType;
};

CLASS(HookEvent, BindJs)
class YrWeaponTypeDtorEvent
{
public:
    PROPERTY()
    WeaponTypeClass* pWeaponType;
};

CLASS(HookEvent, BindJs)
class YrWeaponTypeSaveGameBeginEvent
{
public:
    PROPERTY()
    WeaponTypeClass* pWeaponType;
    PROPERTY()
    IStream*         stream;
};

CLASS(HookEvent, BindJs)
class YrWeaponTypeSaveGameEndEvent
{
public:
    PROPERTY()
    WeaponTypeClass* pWeaponType;
    PROPERTY()
    IStream*         stream;
};

CLASS(HookEvent, BindJs)
class YrWeaponTypeLoadGameBeginEvent
{
public:
    PROPERTY()
    WeaponTypeClass* pWeaponType;
    PROPERTY()
    IStream*         stream;
};

CLASS(HookEvent, BindJs)
class YrWeaponTypeLoadGameEndEvent
{
public:
    PROPERTY()
    WeaponTypeClass* pWeaponType;
    PROPERTY()
    IStream*         stream;
};

CLASS(HookEvent, BindJs)
class YrWeaponTypeLoadIniEvent
{
public:
    PROPERTY()
    WeaponTypeClass* pWeaponType;
    PROPERTY()
    CCINIClass*      pIni;
};

CLASS(HookEvent, BindJs)
class YrWarheadTypeCtorEvent
{
public:
    PROPERTY()
    WarheadTypeClass* pWarheadType;
};

CLASS(HookEvent, BindJs)
class YrWarheadTypeDtorEvent
{
public:
    PROPERTY()
    WarheadTypeClass* pWarheadType;
};

CLASS(HookEvent, BindJs)
class YrWarheadTypeSaveGameBeginEvent
{
public:
    PROPERTY()
    WarheadTypeClass* pWarheadType;
    PROPERTY()
    IStream*          stream;
};

CLASS(HookEvent, BindJs)
class YrWarheadTypeSaveGameEndEvent
{
public:
    PROPERTY()
    WarheadTypeClass* pWarheadType;
    PROPERTY()
    IStream*          stream;
};

CLASS(HookEvent, BindJs)
class YrWarheadTypeLoadGameBeginEvent
{
public:
    PROPERTY()
    WarheadTypeClass* pWarheadType;
    PROPERTY()
    IStream*          stream;
};

CLASS(HookEvent, BindJs)
class YrWarheadTypeLoadGameEndEvent
{
public:
    PROPERTY()
    WarheadTypeClass* pWarheadType;
    PROPERTY()
    IStream*          stream;
};

CLASS(HookEvent, BindJs)
class YrWarheadTypeLoadIniEvent
{
public:
    PROPERTY()
    WarheadTypeClass* pWarheadType;
    PROPERTY()
    CCINIClass*       pIni;
};
