#pragma once

#include "yr/yr_event.h"

struct IStream;

// ======================= logic =======================

CLASS(HookEvent)
class YrLogicBeginUpdateEvent { };

CLASS(HookEvent)
class YrLogicEndUpdateEvent { };

// ======================= render =======================

CLASS(HookEvent)
class YrBeginRenderEvent
{};

CLASS(HookEvent)
class YrEndRenderEvent
{};

CLASS(HookEvent)
class YrSceneLoadEvent { };

CLASS(HookEvent)
class YrSceneEnterEvent { };

CLASS(HookEvent)
class YrSceneExitEvent { };

// ======================= save game =======================

CLASS(HookEvent)
class YrSaveGameBeginEvent
{
public:
    const char* fileName;
};

CLASS(HookEvent)
class YrSaveGameEndEvent
{
public:
    const char* fileName;
};

CLASS(HookEvent)
class YrSaveGameBeginStreamEvent
{
public:
    IStream* stream;
};

CLASS(HookEvent)
class YrSaveGameEndStreamEvent
{
public:
    IStream* stream;
};

// ======================= load game =======================

CLASS(HookEvent)
class YrLoadGameBeginEvent
{
public:
    const char* fileName;
};

CLASS(HookEvent)
class YrLoadGameEndEvent
{
public:
    const char* fileName;
};

CLASS(HookEvent)
class YrLoadGameBeginStreamEvent
{
public:
    IStream* stream;
};

CLASS(HookEvent)
class YrLoadGameEndStreamEvent
{
public:
    IStream* stream;
};
