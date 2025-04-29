#include "yr/serialization/serialization.h"
#include "yr/serialization/serializer.h"
#include "runtime/platform/path.h"
#include "yr/event/general_event.h"
#include "runtime/ecs/entt.h"
#include "serialization.h"
#include <fstream>

static SerializeContext gContext;
static std::map<void(*)(entt::meta_any), std::vector<entt::meta_any>> gDeferredProcessDataList;
static std::fstream gFileStream;
static std::map<void(*)(entt::snapshot&), void(*)(entt::continuous_loader&)> gSnapshots;
Serialization::SerializationArchive Serialization::gArchive;

struct SerDebugInfo {
    size_t version {0};
    std::vector<std::string> registeredComponents;
    
    template<class Archive>
    void serialize(Archive& ar)
    {
        std::string note = "this file store the extra serialization info e.g. XkeinExt.";
        ar(cereal::make_nvp("note", note));
        ar(cereal::make_nvp("version", version));
        ar(cereal::make_nvp("registered_serialization_components", registeredComponents));
    }
} gSerDebugInfo;

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

void Serialization::RegisterSnapshotInternal(entt::meta_type type, void(*snapshotSave)(entt::snapshot&), void(*snapshotLoad)(entt::continuous_loader&))
{
    if (gSnapshots.find(snapshotSave) == gSnapshots.end()) {
        gSerDebugInfo.version += type.size_of();
        gSerDebugInfo.registeredComponents.emplace_back(type.info().name());
    }
    gSnapshots[snapshotSave] = snapshotLoad;
}

void Serialization::RegisterDeferredProcessInternal(entt::meta_any data, void(*processFunc)(entt::meta_any))
{
    gDeferredProcessDataList[processFunc].emplace_back(data);
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
    Serialization::Serialize(gSerDebugInfo);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSaveGameBeginStreamEvent)
{
    if (!gContext.outputArchive) {
        return;
    }
    gContext.snapshot = new entt::snapshot(*gEntt);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSaveGameEndEvent)
{
    for (auto&& [snapshotSave, snapshotLoad] : gSnapshots)
    {
        snapshotSave(*gContext.snapshot);
    }

    gContext.outputArchive->serializeDeferments();
    for (auto&& [processFunc, dataList] : gDeferredProcessDataList)
    {
        for (auto&& data : dataList)
        {
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
    SerDebugInfo info;
    Serialization::Serialize(info);
    if (info.version != gSerDebugInfo.version) {
        gLogger->error("skip loading game {}, version mismatch: current version {}, savegame version {}", E->fileName, gSerDebugInfo.version, info.version);
        ResetContext();
        return;
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrLoadGameBeginStreamEvent)
{
    if (!gContext.inputArchive) {
        return;
    }
    for(auto entity: gEntt->view<entt::entity>()) {
        if(!gEntt->orphan(entity)) {
            gLogger->warn("entity {} is not orphan", static_cast<uint>(entity));
        }
    }
    gContext.snapshotLoader = new entt::continuous_loader(*gEntt);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrLoadGameEndEvent)
{
    if (!gContext.inputArchive) {
        return;
    }
    for (auto&& [snapshotSave, snapshotLoad] : gSnapshots)
    {
        snapshotLoad(*gContext.snapshotLoader);
    }

    gContext.inputArchive->serializeDeferments();
    for (auto&& [processFunc, dataList] : gDeferredProcessDataList)
    {
        for (auto&& data : dataList)
        {
            processFunc(data);
        }
    }
    ResetContext();
}