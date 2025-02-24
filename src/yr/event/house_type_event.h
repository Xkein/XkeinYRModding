#pragma once

#include "yr/yr_event.h"

class HouseTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrHouseTypeCtorEvent
{
public:
    HouseTypeClass* pHouseType;
};

CLASS(HookEvent)
class YrHouseTypeDtorEvent
{
public:
    HouseTypeClass* pHouseType;
};

CLASS(HookEvent)
class YrHouseTypeSaveGameBeginEvent
{
public:
    HouseTypeClass* pHouseType;
    IStream*        stream;
};

CLASS(HookEvent)
class YrHouseTypeSaveGameEndEvent
{
public:
    HouseTypeClass* pHouseType;
    IStream*        stream;
};

CLASS(HookEvent)
class YrHouseTypeLoadGameBeginEvent
{
public:
    HouseTypeClass* pHouseType;
    IStream*        stream;
};

CLASS(HookEvent)
class YrHouseTypeLoadGameEndEvent
{
public:
    HouseTypeClass* pHouseType;
    IStream*        stream;
};

CLASS(HookEvent)
class YrHouseTypeLoadIniEvent
{
public:
    HouseTypeClass* pHouseType;
    CCINIClass*     pIni;
};