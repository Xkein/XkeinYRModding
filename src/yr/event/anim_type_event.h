#pragma once

#include "yr/yr_event.h"

class AnimTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrAnimTypeCtorEvent
{
public:
    PROPERTY()
    AnimTypeClass* pAnimType;
};

CLASS(HookEvent, BindJs)
class YrAnimTypeDtorEvent
{
public:
    PROPERTY()
    AnimTypeClass* pAnimType;
};

CLASS(HookEvent, BindJs)
class YrAnimTypeSaveGameBeginEvent
{
public:
    PROPERTY()
    AnimTypeClass* pAnimType;
    PROPERTY()
    IStream*       stream;
};

CLASS(HookEvent, BindJs)
class YrAnimTypeSaveGameEndEvent
{
public:
    PROPERTY()
    AnimTypeClass* pAnimType;
    PROPERTY()
    IStream*       stream;
};

CLASS(HookEvent, BindJs)
class YrAnimTypeLoadGameBeginEvent
{
public:
    PROPERTY()
    AnimTypeClass* pAnimType;
    PROPERTY()
    IStream*       stream;
};

CLASS(HookEvent, BindJs)
class YrAnimTypeLoadGameEndEvent
{
public:
    PROPERTY()
    AnimTypeClass* pAnimType;
    PROPERTY()
    IStream*       stream;
};

CLASS(HookEvent, BindJs)
class YrAnimTypeLoadIniEvent
{
public:
    PROPERTY()
    AnimTypeClass* pAnimType;
    PROPERTY()
    CCINIClass*    pIni;
};