#pragma once

#include "yr/yr_event.h"
#include <GeneralStructures.h>

class SuperClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrSuperCtorEvent
{
public:
    PROPERTY()
    SuperClass* pSuper;
};

CLASS(HookEvent, BindJs)
class YrSuperDtorEvent
{
public:
    PROPERTY()
    SuperClass* pSuper;
};

CLASS(HookEvent, BindJs)
class YrSuperSaveGameBeginEvent
{
public:
    PROPERTY()
    SuperClass* pSuper;
    PROPERTY()
    IStream*    stream;
};

CLASS(HookEvent, BindJs)
class YrSuperSaveGameEndEvent
{
public:
    PROPERTY()
    SuperClass* pSuper;
    PROPERTY()
    IStream*    stream;
};

CLASS(HookEvent, BindJs)
class YrSuperLoadGameBeginEvent
{
public:
    PROPERTY()
    SuperClass* pSuper;
    PROPERTY()
    IStream*    stream;
};

CLASS(HookEvent, BindJs)
class YrSuperLoadGameEndEvent
{
public:
    PROPERTY()
    SuperClass* pSuper;
    PROPERTY()
    IStream*    stream;
};

CLASS(HookEvent, BindJs)
class YrSuperLaunchEvent
{
public:
    PROPERTY()
    SuperClass*       pSuper;
    PROPERTY()
    CellStruct const* pCell;
    PROPERTY()
    bool              isPlayer;
};
