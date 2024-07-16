#pragma once

#include "yr/yr_event.h"

class AnimTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrAnimTypeCtorEvent
{
public:
    AnimTypeClass* pAnimType {nullptr};
};

CLASS(HookEvent)
class YrAnimTypeDtorEvent
{
public:
    AnimTypeClass* pAnimType {nullptr};
};
