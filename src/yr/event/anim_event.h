#pragma once

#include "yr/yr_event.h"

class AnimClass;
struct IStream;

CLASS(HookEvent)
class YrAnimCtorEvent
{
public:
    AnimClass* pAnim;
};

CLASS(HookEvent)
class YrAnimDtorEvent
{
public:
    AnimClass* pAnim;
};
