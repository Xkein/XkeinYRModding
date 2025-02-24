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

CLASS(HookEvent)
class YrAnimSaveGameBeginEvent
{
public:
    AnimClass* pAnim;
    IStream*   stream;
};

CLASS(HookEvent)
class YrAnimSaveGameEndEvent
{
public:
    AnimClass* pAnim;
    IStream*   stream;
};

CLASS(HookEvent)
class YrAnimLoadGameBeginEvent
{
public:
    AnimClass* pAnim;
    IStream*   stream;
};

CLASS(HookEvent)
class YrAnimLoadGameEndEvent
{
public:
    AnimClass* pAnim;
    IStream*   stream;
};
