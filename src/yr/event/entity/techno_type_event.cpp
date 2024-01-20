#include "techno_type_event.h"

#include <TechnoTypeClass.h>

IMPLEMENT_YR_HOOK_EVENT(YrTechnoTypeCtorEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoTypeCtorEvent, 0x711835)
{
    entityInfo.entity = R->ESI<TechnoTypeClass*>();
}

IMPLEMENT_YR_HOOK_EVENT(YrTechnoTypeDtorEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoTypeDtorEvent, 0x711AE0)
{
    entityInfo.entity = R->ECX<TechnoTypeClass*>();
}

IMPLEMENT_YR_HOOK_EVENT(YrTechnoTypeLoadIniEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoTypeLoadIniEvent, 0x716132)
{
    entityInfo.entity        = R->EBP<TechnoTypeClass*>();
    loadIniInfo.yrTypeObject = R->EBP<TechnoTypeClass*>();
    loadIniInfo.yrIni        = R->Stack<CCINIClass*>(0x380);
}
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoTypeLoadIniEvent, 0x716123)
{
    entityInfo.entity        = R->EBP<TechnoTypeClass*>();
    loadIniInfo.yrTypeObject = R->EBP<TechnoTypeClass*>();
    loadIniInfo.yrIni        = R->Stack<CCINIClass*>(0x380);
}

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

IMPLEMENT_YR_HOOK_EVENT(YrTechnoTypeSaveGameBeginEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoTypeSaveGameBeginEvent, 0x716DC0)
{
    entityInfo.entity = R->Stack<TechnoTypeClass*>(0x4);
    streamInfo.stream = R->Stack<IStream*>(0x8);

    gSavingObject = entityInfo.entity;
    gSavingStream = streamInfo.stream;
}

IMPLEMENT_YR_HOOK_EVENT(YrTechnoTypeSaveGameEndEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoTypeSaveGameEndEvent, 0x717094)
{
    entityInfo.entity = gSavingObject;
    streamInfo.stream = gSavingStream;
}

IMPLEMENT_YR_HOOK_EVENT(YrTechnoTypeLoadGameBeginEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoTypeLoadGameBeginEvent, 0x7162F0)
{
    entityInfo.entity = R->Stack<TechnoTypeClass*>(0x4);
    streamInfo.stream = R->Stack<IStream*>(0x8);
}

IMPLEMENT_YR_HOOK_EVENT(YrTechnoTypeLoadGameEndEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoTypeLoadGameEndEvent, 0x716DAC)
{
    entityInfo.entity = gSavingObject;
    streamInfo.stream = gSavingStream;
}
