#pragma once

#include "yr/yr_event.h"

class AnimTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrAnimTypeCtorEvent
{
public:
    AnimTypeClass* pAnimType;
};

CLASS(HookEvent)
class YrAnimTypeDtorEvent
{
public:
    AnimTypeClass* pAnimType;
};

CLASS(HookEvent)
class YrAnimTypeLoadIniEvent
{
public:
    AnimTypeClass* pAnimType;
    CCINIClass*    pIni;
};