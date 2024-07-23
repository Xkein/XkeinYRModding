#pragma once

#include "yr/yr_event.h"

class TechnoTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrTechnoTypeCtorEvent
{
public:
    TechnoTypeClass* pTechnoType;
};

CLASS(HookEvent)
class YrTechnoTypeDtorEvent
{
public:
    TechnoTypeClass* pTechnoType;
};

CLASS(HookEvent)
class YrTechnoTypeLoadIniEvent
{
public:
    TechnoTypeClass* pTechnoType;
    CCINIClass* pIni;
};

CLASS(HookEvent)
class YrTechnoTypeSaveGameBeginEvent
{
public:
    TechnoTypeClass* pTechnoType;
    IStream* stream;
};

CLASS(HookEvent)
class YrTechnoTypeSaveGameEndEvent
{
public:
    TechnoTypeClass* pTechnoType;
    IStream* stream;
};

CLASS(HookEvent)
class YrTechnoTypeLoadGameBeginEvent
{
public:
    TechnoTypeClass* pTechnoType;
    IStream* stream;
};

CLASS(HookEvent)
class YrTechnoTypeLoadGameEndEvent
{
public:
    TechnoTypeClass* pTechnoType;
    IStream* stream;
};
