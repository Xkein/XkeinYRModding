#include "yr_general_event.h"

IMPLEMENT_YR_HOOK_EVENT(YrBootEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrBootEvent, 0x52BA60) {}

IMPLEMENT_YR_HOOK_EVENT(YrTerminateEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTerminateEvent, 0x7CD8EF) {}

// ======================= logic =======================

IMPLEMENT_YR_HOOK_EVENT(YrLogicBeginUpdateEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrLogicBeginUpdateEvent, 0x55AFB3) {}

IMPLEMENT_YR_HOOK_EVENT(YrLogicEndUpdateEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrLogicEndUpdateEvent, 0x55B719) {}

// ======================= scenario =======================

IMPLEMENT_YR_HOOK_EVENT(YrScenarioStartEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrScenarioStartEvent, 0x6875F3) {}

IMPLEMENT_YR_HOOK_EVENT(YrScenarioClearEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrScenarioClearEvent, 0x685659) {}

// ======================= save game =======================

IMPLEMENT_YR_HOOK_EVENT(YrSaveGameBeginEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrSaveGameBeginEvent, 0x67CEF0)
{
    fileNameInfo.fileName = R->ECX<const char*>();
}

IMPLEMENT_YR_HOOK_EVENT(YrSaveGameBeginStreamEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrSaveGameBeginStreamEvent, 0x67D300)
{
    streamInfo.stream = R->ECX<IStream*>();
}

IMPLEMENT_YR_HOOK_EVENT(YrSaveGameEndStreamEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrSaveGameEndStreamEvent, 0x67E42E)
{
    streamInfo.stream = R->ESI<IStream*>();
}

IMPLEMENT_YR_HOOK_EVENT(YrSaveGameEndEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrSaveGameEndEvent, 0x67D2F1)
{
    fileNameInfo.fileName = R->EDI<const char*>();
}

// ======================= load game =======================

IMPLEMENT_YR_HOOK_EVENT(YrLoadGameBeginEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrLoadGameBeginEvent, 0x67E440)
{
    this->fileNameInfo.fileName = R->ECX<const char*>();
}

IMPLEMENT_YR_HOOK_EVENT(YrLoadGameBeginStreamEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrLoadGameBeginStreamEvent, 0x67E730)
{
    this->streamInfo.stream = R->ECX<IStream*>();
}

IMPLEMENT_YR_HOOK_EVENT(YrLoadGameEndStreamEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrLoadGameEndStreamEvent, 0x67F7C8)
{
    this->streamInfo.stream = R->ESI<IStream*>();
}

IMPLEMENT_YR_HOOK_EVENT(YrLoadGameEndEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrLoadGameEndEvent, 0x67E720)
{
    this->fileNameInfo.fileName = R->ESI<const char*>();
}

