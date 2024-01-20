#include "read_scheduler.h"
#include "resources/ini.h"
#include "resources/ini_asset.h"
#include "resources/asset.h"
#include "yr/event/yr_general_event.h"

#include <ScenarioClass.h>
#include <SessionClass.h>
#include <MPGameModeClass.h>

#include <vector>
#include <memory>

static bool gPreloaded = false;

static Ini gRulesIni;
static Ini gArtIni;
static Ini gAiIni;

void ReadScheduler::ScheduleRead(ScheduleReadInfo readInfo)
{
    IReadTask* task = readInfo.task;

    if (!task)
    {
        return;
    }

    if (!readInfo.async)
    {
        ReadImmediately(readInfo);
        return;
    }


}

void ReadScheduler::ClearAllTasks()
{
    
}

void ReadScheduler::Tick()
{
    
}

void ReadScheduler::Preload()
{
    auto preloadIni = []() {
        std::shared_ptr<IniAsset> rulesIniAsset = Asset::Load<IniAsset>("rulesmd.ini");
        gRulesIni.Read(*rulesIniAsset);

        if (SessionClass::Instance->GameMode != GameMode::Campaign)
        {
            std::shared_ptr<IniAsset> gameModeIniAsset = Asset::Load<IniAsset>(SessionClass::Instance->MPGameMode->INIFilename.PeekBuffer());
            gRulesIni.Read(*gameModeIniAsset);
        }

        std::shared_ptr<IniAsset> mapIniAsset = Asset::Load<IniAsset>(ScenarioClass::Instance->FileName);
        gRulesIni.Read(*mapIniAsset);

        std::shared_ptr<IniAsset> artIniAsset = Asset::Load<IniAsset>("artmd.ini");
        gArtIni.Read(*artIniAsset);

        std::shared_ptr<IniAsset> aiIniAsset = Asset::Load<IniAsset>("aimd.ini");
        gAiIni.Read(*aiIniAsset).Read(*mapIniAsset);

        gPreloaded = true;
    };


}

bool ReadScheduler::HasTasks()
{
    return false;
}

void ReadScheduler::Clear()
{
    ClearAllTasks();

    gRulesIni.Clear();
    gArtIni.Clear();
    gAiIni.Clear();

    gPreloaded = false;
}

void ReadScheduler::ReadImmediately(const ScheduleReadInfo& readInfo)
{
    IReadTask* task = readInfo.task;

    if (readInfo.rules)
    {
        task->Read(gRulesIni);
    }
    if (readInfo.art)
    {
        task->Read(gArtIni);
    }
    if (readInfo.ai)
    {
        task->Read(gAiIni);
    }
    if (readInfo.custom)
    {
        task->ReadCustom();
    }
}


