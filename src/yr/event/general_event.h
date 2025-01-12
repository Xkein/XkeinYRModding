#pragma once

#include "yr/yr_event.h"

struct IStream;
class CCINIClass;
class RulesClass;
class AbstractClass;

// ======================= logic =======================

CLASS(HookEvent)
class YrLogicBeginUpdateEvent { };

CLASS(HookEvent)
class YrLogicEndUpdateEvent { };

CLASS(HookEvent)
class YrPointerExpireEvent {
public:
    AbstractClass* pAbstract;
    bool removed;
};

// ======================= render =======================

CLASS(HookEvent)
class YrBeginRenderEvent
{};

CLASS(HookEvent)
class YrEndRenderEvent
{};

// ======================= scene =======================

CLASS(HookEvent)
class YrSceneLoadEvent { };

CLASS(HookEvent)
class YrSceneEnterEvent { };

CLASS(HookEvent)
class YrSceneExitEvent { };

// ======================= load ini =======================

CLASS(HookEvent)
class YrRulesLoadBeforeGeneralDataEvent {
public:
    RulesClass* pRules;
    CCINIClass* pIni;
};

CLASS(HookEvent)
class YrRulesLoadBeforeTypeDataEvent {
public:
    RulesClass* pRules;
    CCINIClass* pIni;
};

CLASS(HookEvent)
class YrRulesLoadAfterTypeDataEvent {
public:
    RulesClass* pRules;
    CCINIClass* pIni;
};

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
