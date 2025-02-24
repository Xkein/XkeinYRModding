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
class YrAnimTypeSaveGameBeginEvent
{
public:
    AnimTypeClass* pAnimType;
    IStream*       stream;
};

CLASS(HookEvent)
class YrAnimTypeSaveGameEndEvent
{
public:
    AnimTypeClass* pAnimType;
    IStream*       stream;
};

CLASS(HookEvent)
class YrAnimTypeLoadGameBeginEvent
{
public:
    AnimTypeClass* pAnimType;
    IStream*       stream;
};

CLASS(HookEvent)
class YrAnimTypeLoadGameEndEvent
{
public:
    AnimTypeClass* pAnimType;
    IStream*       stream;
};

CLASS(HookEvent)
class YrAnimTypeLoadIniEvent
{
public:
    AnimTypeClass* pAnimType;
    CCINIClass*    pIni;
};