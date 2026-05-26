#include "gameplay_cue_manager.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "scripting/common/script_function.h"
#include <CCINIClass.h>
#include <cstring>

GameplayCueManager* GameplayCueManager::Get()
{
    return IniComponentLoader::GetGlobalIniComponent<GameplayCueManager>();
}

void GameplayCueManager::HandleGameplayCue(AbilitySystemComponent* ASC, const GameplayTag& CueTag,
                                            EGameplayCueEvent EventType, const GameplayCueParameters& Params)
{
    // Route to static cue notifies
    auto itStatic = StaticCues.find(CueTag);
    if (itStatic != StaticCues.end())
    {
        for (auto* Cue : itStatic->second)
        {
            if (!Cue) continue;
            switch (EventType)
            {
                case EGameplayCueEvent::Executed:
                    Cue->OnExecute(CueTag, Params);
                    break;
                case EGameplayCueEvent::OnActive:
                case EGameplayCueEvent::WhileActive:
                    Cue->OnActive(CueTag, Params);
                    break;
                case EGameplayCueEvent::Removed:
                    Cue->OnRemove(CueTag, Params);
                    break;
            }
        }
    }

    // Route to actor cue notifies
    auto itActor = ActorCues.find(CueTag);
    if (itActor != ActorCues.end())
    {
        for (auto* Cue : itActor->second)
        {
            if (!Cue) continue;
            switch (EventType)
            {
                case EGameplayCueEvent::Executed:
                    Cue->OnBurst(CueTag, Params);
                    break;
                case EGameplayCueEvent::OnActive:
                case EGameplayCueEvent::WhileActive:
                    Cue->OnBecomeRelevant(CueTag, Params);
                    break;
                case EGameplayCueEvent::Removed:
                    Cue->OnCeaseRelevant(CueTag, Params);
                    break;
            }
        }
    }
}

void GameplayCueManager::AddCueNotify(const GameplayTag& Tag, GameplayCueNotify_Static* Cue)
{
    if (!Cue) return;
    StaticCues[Tag].push_back(Cue);
}

void GameplayCueManager::AddCueNotify(const GameplayTag& Tag, GameplayCueNotify_Actor* Cue)
{
    if (!Cue) return;
    ActorCues[Tag].push_back(Cue);
}

void GameplayCueManager::AfterLoadIni(IniReader& parser, const char* pSection, const char* pKey)
{
    CCINIClass* pIni = parser.GetIni();
    if (!pIni) return;

    for (auto* pSec = pIni->Sections.First(); pSec && pSec->IsValid(); pSec = pSec->Next())
    {
        const char* sectionName = pSec->Name;
        if (!sectionName) continue;

        // Match sections starting with "GameplayCue."
        if (strncmp(sectionName, "GameplayCue.", 12) != 0) continue;

        GameplayTag tag;
        tag.TagName = StringName(sectionName + 12); // skip "GameplayCue." prefix
        if (!tag.IsValid()) continue;

        // Read StaticNotify list (comma-separated factory names)
        std::vector<StringName> staticNames;
        if (parser.Read(sectionName, "StaticNotify", staticNames))
        {
            for (const auto& name : staticNames)
            {
                auto* creator = ScriptFunctionRegister::GetFunctionAs<GameplayCueStaticCreator>(name);
                if (creator)
                {
                    GameplayCueNotify_Static* cue = (*creator)();
                    if (cue)
                    {
                        AddCueNotify(tag, cue);
                    }
                }
            }
        }

        // Read ActorNotify list (comma-separated factory names)
        std::vector<StringName> actorNames;
        if (parser.Read(sectionName, "ActorNotify", actorNames))
        {
            for (const auto& name : actorNames)
            {
                auto* creator = ScriptFunctionRegister::GetFunctionAs<GameplayCueActorCreator>(name);
                if (creator)
                {
                    GameplayCueNotify_Actor* cue = (*creator)();
                    if (cue)
                    {
                        AddCueNotify(tag, cue);
                    }
                }
            }
        }
    }
}
