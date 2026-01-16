#pragma once

#include "yr/yr_event.h"

class HouseTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrHouseTypeCtorEvent
{
public:
    PROPERTY()
    HouseTypeClass* pHouseType;
};

CLASS(HookEvent, BindJs)
class YrHouseTypeDtorEvent
{
public:
    PROPERTY()
    HouseTypeClass* pHouseType;
};

CLASS(HookEvent, BindJs)
class YrHouseTypeSaveGameBeginEvent
{
public:
    PROPERTY()
    HouseTypeClass* pHouseType;
    PROPERTY()
    IStream*        stream;
};

CLASS(HookEvent, BindJs)
class YrHouseTypeSaveGameEndEvent
{
public:
    PROPERTY()
    HouseTypeClass* pHouseType;
    PROPERTY()
    IStream*        stream;
};

CLASS(HookEvent, BindJs)
class YrHouseTypeLoadGameBeginEvent
{
public:
    PROPERTY()
    HouseTypeClass* pHouseType;
    PROPERTY()
    IStream*        stream;
};

CLASS(HookEvent, BindJs)
class YrHouseTypeLoadGameEndEvent
{
public:
    PROPERTY()
    HouseTypeClass* pHouseType;
    PROPERTY()
    IStream*        stream;
};

CLASS(HookEvent, BindJs)
class YrHouseTypeLoadIniEvent
{
public:
    PROPERTY()
    HouseTypeClass* pHouseType;
    PROPERTY()
    CCINIClass*     pIni;
};