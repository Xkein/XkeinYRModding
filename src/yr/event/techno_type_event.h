#pragma once

#include "yr/yr_event.h"

class TechnoTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrTechnoTypeCtorEvent
{
public:
    TechnoTypeClass* pTechnoType {nullptr};
};

CLASS(HookEvent)
class YrTechnoTypeDtorEvent
{
public:
    TechnoTypeClass* pTechnoType {nullptr};
};

CLASS(HookEvent)
class YrTechnoTypeLoadIniEvent
{
public:
    TechnoTypeClass* pTechnoType {nullptr};
    CCINIClass* pIni {nullptr};
};

CLASS(HookEvent)
class YrTechnoTypeSaveGameBeginEvent
{
public:
    TechnoTypeClass* pTechnoType {nullptr};
    IStream* stream {nullptr};
};

CLASS(HookEvent)
class YrTechnoTypeSaveGameEndEvent
{
public:
    TechnoTypeClass* pTechnoType {nullptr};
    IStream* stream {nullptr};
};

CLASS(HookEvent)
class YrTechnoTypeLoadGameBeginEvent
{
public:
    TechnoTypeClass* pTechnoType {nullptr};
    IStream* stream {nullptr};
};

CLASS(HookEvent)
class YrTechnoTypeLoadGameEndEvent
{
public:
    TechnoTypeClass* pTechnoType {nullptr};
    IStream* stream {nullptr};
};
