#pragma once

#include "yr_event.h"
#include "yr_event_info.h"

// ======================= yr application =======================

DEFINE_HOOK_EVENT_BEGIN(YrBootEvent)
    DESCRIBE_HOOK_EVENT("ApplicationBoot", "Raised when application boot.")
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTerminateEvent)
    DESCRIBE_HOOK_EVENT("ApplicationTerminate", "Raised when application terminate.")
DEFINE_HOOK_EVENT_END()

// ======================= logic =======================

DEFINE_HOOK_EVENT_BEGIN(YrLogicBeginUpdateEvent)
    DESCRIBE_HOOK_EVENT("LogicBeginUpdate", "Raised when LogicClass begin update.")
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrLogicEndUpdateEvent)
    DESCRIBE_HOOK_EVENT("LogicEndUpdate", "Raised when LogicClass end update.")
DEFINE_HOOK_EVENT_END()

// ======================= scenario =======================

DEFINE_HOOK_EVENT_BEGIN(YrScenarioStartEvent)
    DESCRIBE_HOOK_EVENT("ScenarioStart", "Raised when scenario start.")
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrScenarioClearEvent)
    DESCRIBE_HOOK_EVENT("ScenarioClear", "Raised when scenario is cleaning classes.")
DEFINE_HOOK_EVENT_END()

// ======================= save game =======================

DEFINE_HOOK_EVENT_BEGIN(YrSaveGameBeginEvent)
    DESCRIBE_HOOK_EVENT("SaveGameBegin", "Raised when begin to save game.")
    IMPLEMENT_EVENT_INFO(FileNameEventInfo, fileNameInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrSaveGameBeginStreamEvent)
    DESCRIBE_HOOK_EVENT("SaveGameBeginStream", "Raised when begin to write saving game.")
    IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrSaveGameEndStreamEvent)
    DESCRIBE_HOOK_EVENT("SaveGameEndStream", "Raised when end to write saving game.")
    IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrSaveGameEndEvent)
    DESCRIBE_HOOK_EVENT("SaveGameBeginStream", "Raised when end to save game.")
    IMPLEMENT_EVENT_INFO(FileNameEventInfo, fileNameInfo)
DEFINE_HOOK_EVENT_END()

// ======================= load game =======================

DEFINE_HOOK_EVENT_BEGIN(YrLoadGameBeginEvent)
    DESCRIBE_HOOK_EVENT("LoadGameBegin", "Raised when begin to load game.")
    IMPLEMENT_EVENT_INFO(FileNameEventInfo, fileNameInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrLoadGameBeginStreamEvent)
    DESCRIBE_HOOK_EVENT("LoadGameBeginStream", "Raised when begin to read saved game.")
    IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrLoadGameEndStreamEvent)
    DESCRIBE_HOOK_EVENT("LoadGameBeginStream", "Raised when end to read saved game.")
    IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrLoadGameEndEvent)
    DESCRIBE_HOOK_EVENT("LoadGameBeginStream", "Raised when end to load game.")
    IMPLEMENT_EVENT_INFO(FileNameEventInfo, fileNameInfo)
DEFINE_HOOK_EVENT_END()