#include "yr/serialization/serialization.h"
#include "yr/serialization/serializer.h"
#include "runtime/platform/path.h"
#include "runtime/ecs/entt.h"
#include "serialization.h"
#include <fstream>

static SerializeContext gContext;
static std::map<void(*)(entt::meta_any), std::vector<entt::meta_any>> gDeferredProcessDataList;
static std::fstream gFileStream;
static std::map<void(*)(ENTITY_SNAPSHOT&), void(*)(ENTITY_SNAPSHOT_LOADER&)> gSnapshots;
Serialization::SerializationArchive Serialization::gArchive;

struct SerHeaderInfo {
    size_t version {0};
    std::vector<std::string> registeredComponents;
    std::string gameMode;

    template<class Archive>
    void serialize(Archive& ar)
    {
        std::string note = "this file store the extra serialization info e.g. XkeinExt.";
        ar(cereal::make_nvp("note", note));
        ar(cereal::make_nvp("version", version));
        ar(cereal::make_nvp("registered_serialization_components", registeredComponents));
        ar(cereal::make_nvp("game_mode", gameMode));
    }
} gSerHeaderInfo;

void ResetContext()
{
    if (gContext.snapshot) {
        delete gContext.snapshot;
        gContext.snapshot = nullptr;
    }
    if (gContext.snapshotLoader) {
        delete gContext.snapshotLoader;
        gContext.snapshotLoader = nullptr;
    }
    gContext.archivePath.clear();
    if (gContext.inputArchive) {
        delete gContext.inputArchive;
        gContext.inputArchive = nullptr;
    }
    if (gContext.outputArchive) {
        delete gContext.outputArchive;
        gContext.outputArchive = nullptr;
    }
    gDeferredProcessDataList.clear();
    if (gFileStream.is_open()) {
        gFileStream.close();
    }
}

SerializeContext* Serialization::GetCurrentContext() {
    return &gContext;
}

bool Serialization::IsSerializing()
{
    return gContext.inputArchive || gContext.outputArchive;
}

std::string Serialization::GetArchivePath(const char* savegameName, const char* extension)
{
    return Paths::GetLaunchDir() / "Saved Games" / Paths::SetExtension(savegameName, extension ? extension : "savex.json");
}

void Serialization::RegisterSnapshotInternal(entt::meta_type type, void(*snapshotSave)(ENTITY_SNAPSHOT&), void(*snapshotLoad)(ENTITY_SNAPSHOT_LOADER&))
{
    if (gSnapshots.find(snapshotSave) == gSnapshots.end()) {
        gSerHeaderInfo.version += type.size_of();
        gSerHeaderInfo.registeredComponents.emplace_back(type.info().name());
    }
    gSnapshots[snapshotSave] = snapshotLoad;
}

void Serialization::RegisterDeferredProcessInternal(entt::meta_any data, void(*processFunc)(entt::meta_any))
{
    gDeferredProcessDataList[processFunc].emplace_back(data);
}

#include "yr/api/yr_entity.h"
#include "yr/event/general_event.h"
#include "yr/component/ini_component.h"
#include <CCINIClass.h>
#include <GameStrings.h>
#include <SessionClass.h>
#include <ScenarioClass.h>
#include <TerrainTypeClass.h>
#include <BulletTypeClass.h>
#include <HouseTypeClass.h>
#include <SuperWeaponTypeClass.h>
#include <WarheadTypeClass.h>

void SimulateIniLoading()
{
    std::vector<const char*> iniArt = { GameStrings::ARTMD_INI };
    std::vector<const char*> iniAi = { ScenarioClass::Instance->FileName, GameStrings::AIMD_INI };
    std::vector<const char*> iniRules = { ScenarioClass::Instance->FileName, gSerHeaderInfo.gameMode.c_str(), GameStrings::RULESMD_INI };

    for (const char* iniName : iniRules)
    {
        CCINIClass ini{};
        ini.LoadFromFile(iniName);
        for (auto&& loadingObj : *TechnoTypeClass::Array) {
            IniComponentLoader::OnLoading(&ini, loadingObj);
        }
        for (auto&& loadingObj : *TerrainTypeClass::Array) {
            IniComponentLoader::OnLoading(&ini, loadingObj);
        }
        for (auto&& loadingObj : *BulletTypeClass::Array) {
            IniComponentLoader::OnLoading(&ini, loadingObj);
        }
        for (auto&& loadingObj : *AnimTypeClass::Array) {
            IniComponentLoader::OnLoading(&ini, loadingObj);
        }
        for (auto&& loadingObj : *HouseTypeClass::Array) {
            IniComponentLoader::OnLoading(&ini, loadingObj);
        }
        for (auto&& loadingObj : *SuperWeaponTypeClass::Array) {
            IniComponentLoader::OnLoading(&ini, loadingObj);
        }
        for (auto&& loadingObj : *WeaponTypeClass::Array) {
            IniComponentLoader::OnLoading(&ini, loadingObj);
        }
        for (auto&& loadingObj : *WarheadTypeClass::Array) {
            IniComponentLoader::OnLoading(&ini, loadingObj);
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneEnterEvent) {
    if (gSerHeaderInfo.gameMode.empty()) {
        gSerHeaderInfo.gameMode = SessionClass::Instance->MPGameMode->INIFilename.PeekBuffer();
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneExitEvent) {
    gSerHeaderInfo.gameMode.clear();
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrSaveGameBeginEvent)
{
    ResetContext();
    gContext.savegameName = E->fileName;
    gContext.archivePath = Serialization::GetArchivePath(E->fileName);
    gFileStream = std::fstream(gContext.archivePath, std::ios::out | std::ios::trunc);
    if (!gFileStream.is_open()) {
        gLogger->error("could not write file {}", gContext.archivePath);
        return;
    }
    gLogger->info("saving game to {}", gContext.archivePath);
    gContext.outputArchive = new cereal::JSONOutputArchive(gFileStream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSaveGameBeginStreamEvent)
{
    if (!gContext.outputArchive) {
        return;
    }
    Serialization::Serialize(gSerHeaderInfo);

    gContext.snapshot = new ENTITY_SNAPSHOT(*gEntt);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSaveGameEndStreamEvent)
{
    if (!gContext.outputArchive) {
        return;
    }
    for (auto&& [snapshotSave, snapshotLoad] : gSnapshots)
    {
        snapshotSave(*gContext.snapshot);
    }

    gContext.outputArchive->serializeDeferments();
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSaveGameEndEvent)
{
    for (auto&& [processFunc, dataList] : gDeferredProcessDataList) {
        for (auto&& data : dataList) {
            processFunc(data);
        }
    }
    ResetContext();
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrLoadGameBeginEvent)
{
    ResetContext();
    gContext.savegameName = E->fileName;
    gContext.archivePath = Serialization::GetArchivePath(E->fileName);
    gFileStream = std::fstream(gContext.archivePath, std::ios::in);
    if (!gFileStream.is_open()) {
        gLogger->error("could not open file {}", gContext.archivePath);
        return;
    }
    gLogger->info("loading game from {}", gContext.archivePath);
    gContext.inputArchive = new cereal::JSONInputArchive(gFileStream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrLoadGameBeginStreamEvent)
{
    if (!gContext.inputArchive) {
        return;
    }
    SerHeaderInfo info;
    Serialization::Serialize(info);
    if (info.version != gSerHeaderInfo.version) {
        gLogger->error("skip loading game {}, version mismatch: current version {}, savegame version {}", gContext.savegameName, gSerHeaderInfo.version, info.version);
        ResetContext();
        return;
    }
    gSerHeaderInfo.gameMode = info.gameMode;

    for(auto entity: gEntt->view<entt::entity>()) {
        if(!gEntt->orphan(entity)) {
            if (gEntt->try_get<YrEntityComponent<ThemeControl>>(entity)) {
                // this entity is never dead
                continue;
            }
            gLogger->warn("entity {} is not orphan", static_cast<uint>(entity));
        }
    }
    gContext.snapshotLoader = new ENTITY_SNAPSHOT_LOADER(*gEntt);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrLoadGameEndStreamEvent)
{
    if (!gContext.inputArchive) {
        return;
    }
    for (auto&& [snapshotSave, snapshotLoad] : gSnapshots) {
        snapshotLoad(*gContext.snapshotLoader);
    }

    gContext.inputArchive->serializeDeferments();
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrLoadGameEndEvent)
{
    if (!gContext.inputArchive) {
        return;
    }
    for (auto&& [processFunc, dataList] : gDeferredProcessDataList) {
        for (auto&& data : dataList) {
            processFunc(data);
        }
    }
    SimulateIniLoading();
    ResetContext();
}