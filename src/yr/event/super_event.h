#pragma once

#include "yr/yr_event.h"
#include <GeneralStructures.h>

class SuperClass;
struct IStream;

CLASS(HookEvent)
class YrSuperCtorEvent
{
public:
    SuperClass* pSuper;
};

CLASS(HookEvent)
class YrSuperDtorEvent
{
public:
    SuperClass* pSuper;
};

CLASS(HookEvent)
class YrSuperSaveGameBeginEvent
{
public:
    SuperClass* pSuper;
    IStream*    stream;
};

CLASS(HookEvent)
class YrSuperSaveGameEndEvent
{
public:
    SuperClass* pSuper;
    IStream*    stream;
};

CLASS(HookEvent)
class YrSuperLoadGameBeginEvent
{
public:
    SuperClass* pSuper;
    IStream*    stream;
};

CLASS(HookEvent)
class YrSuperLoadGameEndEvent
{
public:
    SuperClass* pSuper;
    IStream*    stream;
};

CLASS(HookEvent)
class YrSuperLaunchEvent
{
public:
    SuperClass*       pSuper;
    CellStruct const* pCell;
    bool              isPlayer;
};
