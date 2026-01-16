#pragma once

#include "yr/yr_event.h"

class AnimClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrAnimCtorEvent
{
public:
    PROPERTY()
    AnimClass* pAnim;
};

CLASS(HookEvent, BindJs)
class YrAnimDtorEvent
{
public:
    PROPERTY()
    AnimClass* pAnim;
};

CLASS(HookEvent, BindJs)
class YrAnimSaveGameBeginEvent
{
public:
    PROPERTY()
    AnimClass* pAnim;
    PROPERTY()
    IStream*   stream;
};

CLASS(HookEvent, BindJs)
class YrAnimSaveGameEndEvent
{
public:
    PROPERTY()
    AnimClass* pAnim;
    PROPERTY()
    IStream*   stream;
};

CLASS(HookEvent, BindJs)
class YrAnimLoadGameBeginEvent
{
public:
    PROPERTY()
    AnimClass* pAnim;
    PROPERTY()
    IStream*   stream;
};

CLASS(HookEvent, BindJs)
class YrAnimLoadGameEndEvent
{
public:
    PROPERTY()
    AnimClass* pAnim;
    PROPERTY()
    IStream*   stream;
};
