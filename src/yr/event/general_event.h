#pragma once

#include "yr/yr_event.h"

struct IStream;
class CCINIClass;
class RulesClass;
class AbstractClass;

// ======================= logic =======================

CLASS(HookEvent, BindJs)
class YrLogicBeginUpdateEvent { };

CLASS(HookEvent, BindJs)
class YrLogicEndUpdateEvent { };

CLASS(HookEvent, BindJs)
class YrPointerExpireEvent {
public:
    PROPERTY()
    AbstractClass* pAbstract;
    PROPERTY()
    bool removed;
};

// ======================= render =======================

CLASS(HookEvent, BindJs)
class YrBeginRenderEvent
{};

CLASS(HookEvent, BindJs)
class YrEndRenderEvent
{};

// ======================= scene =======================

CLASS(HookEvent, BindJs)
class YrSceneLoadEvent { };

CLASS(HookEvent, BindJs)
class YrSceneEnterEvent { };

CLASS(HookEvent, BindJs)
class YrSceneExitEvent { };

// ======================= load ini =======================

CLASS(HookEvent, BindJs)
class YrRulesLoadBeforeGeneralDataEvent {
public:
    PROPERTY()
    RulesClass* pRules;
    PROPERTY()
    CCINIClass* pIni;
};

CLASS(HookEvent, BindJs)
class YrRulesLoadBeforeTypeDataEvent {
public:
    PROPERTY()
    RulesClass* pRules;
    PROPERTY()
    CCINIClass* pIni;
};

CLASS(HookEvent, BindJs)
class YrRulesLoadAfterTypeDataEvent {
public:
    PROPERTY()
    RulesClass* pRules;
    PROPERTY()
    CCINIClass* pIni;
};

// ======================= save game =======================

CLASS(HookEvent, BindJs)
class YrSaveGameBeginEvent
{
public:
    PROPERTY()
    const char* fileName;
};

CLASS(HookEvent, BindJs)
class YrSaveGameEndEvent
{
public:
    PROPERTY()
    const char* fileName;
};

CLASS(HookEvent, BindJs)
class YrSaveGameBeginStreamEvent
{
public:
    PROPERTY()
    IStream* stream;
};

CLASS(HookEvent, BindJs)
class YrSaveGameEndStreamEvent
{
public:
    PROPERTY()
    IStream* stream;
};

// ======================= load game =======================

CLASS(HookEvent, BindJs)
class YrLoadGameBeginEvent
{
public:
    PROPERTY()
    const char* fileName;
};

CLASS(HookEvent, BindJs)
class YrLoadGameEndEvent
{
public:
    PROPERTY()
    const char* fileName;
};

CLASS(HookEvent, BindJs)
class YrLoadGameBeginStreamEvent
{
public:
    PROPERTY()
    IStream* stream;
};

CLASS(HookEvent, BindJs)
class YrLoadGameEndStreamEvent
{
public:
    PROPERTY()
    IStream* stream;
};
