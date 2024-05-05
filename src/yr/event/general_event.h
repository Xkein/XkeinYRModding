#pragma once

#include "yr/yr_event.h"

struct IStream;

CLASS(HookEvent)
class YrBootEvent { };

CLASS(HookEvent)
class YrTerminateEvent { };

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

// ======================= scenario =======================

CLASS(HookEvent)
class YrScenarioStartEvent { };

CLASS(HookEvent)
class YrScenarioClearEvent { };

// ======================= save game =======================

CLASS(HookEvent)
class YrSaveGameBeginEvent
{
public:
    const char* fileName {nullptr};
};

CLASS(HookEvent)
class YrSaveGameEndEvent
{
public:
    const char* fileName {nullptr};
};

CLASS(HookEvent)
class YrSaveGameBeginStreamEvent
{
public:
    IStream* stream {nullptr};
};

CLASS(HookEvent)
class YrSaveGameEndStreamEvent
{
public:
    IStream* stream {nullptr};
};

// ======================= load game =======================

CLASS(HookEvent)
class YrLoadGameBeginEvent
{
public:
    const char* fileName {nullptr};
};

CLASS(HookEvent)
class YrLoadGameEndEvent
{
public:
    const char* fileName {nullptr};
};

CLASS(HookEvent)
class YrLoadGameBeginStreamEvent
{
public:
    IStream* stream {nullptr};
};

CLASS(HookEvent)
class YrLoadGameEndStreamEvent
{
public:
    IStream* stream {nullptr};
};
