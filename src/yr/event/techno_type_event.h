#pragma once

#include "yr/yr_event.h"

class TechnoTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrTechnoTypeCtorEvent
{
public:
    PROPERTY()
    TechnoTypeClass* pTechnoType;
};

CLASS(HookEvent, BindJs)
class YrTechnoTypeDtorEvent
{
public:
    PROPERTY()
    TechnoTypeClass* pTechnoType;
};

CLASS(HookEvent, BindJs)
class YrTechnoTypeLoadIniEvent
{
public:
    PROPERTY()
    TechnoTypeClass* pTechnoType;
    PROPERTY()
    CCINIClass* pIni;
};

CLASS(HookEvent, BindJs)
class YrTechnoTypeSaveGameBeginEvent
{
public:
    PROPERTY()
    TechnoTypeClass* pTechnoType;
    PROPERTY()
    IStream* stream;
};

CLASS(HookEvent, BindJs)
class YrTechnoTypeSaveGameEndEvent
{
public:
    PROPERTY()
    TechnoTypeClass* pTechnoType;
    PROPERTY()
    IStream* stream;
};

CLASS(HookEvent, BindJs)
class YrTechnoTypeLoadGameBeginEvent
{
public:
    PROPERTY()
    TechnoTypeClass* pTechnoType;
    PROPERTY()
    IStream* stream;
};

CLASS(HookEvent, BindJs)
class YrTechnoTypeLoadGameEndEvent
{
public:
    PROPERTY()
    TechnoTypeClass* pTechnoType;
    PROPERTY()
    IStream* stream;
};
