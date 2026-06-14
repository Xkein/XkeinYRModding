#include "gameplay_cue_manager.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/ability_system_globals.h"
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
    // Recursion guard: prevent infinite loops from cue-to-cue triggering
    if (bIsHandlingCue)
        return;
    bIsHandlingCue = true;

    // Set OriginalTag if not already set (for future Translator use)
    GameplayCueParameters LocalParams = Params;
    if (!LocalParams.OriginalTag.IsValid())
    {
        LocalParams.OriginalTag = CueTag;
    }
    // MatchedTagName will be set by CueSet during routing

    // --- Step 1: ShouldAcceptGameplayCue check (UE: RouteGameplayCue lines 189-193) ---
    bool bAcceptsCue = true;
    if (ASC)
        bAcceptsCue = ASC->ShouldAcceptGameplayCue(CueTag, EventType, LocalParams);

    // --- Step 2: Route through CueSet (UE: RouteGameplayCue lines 221-224) ---
    if (bAcceptsCue)
        RuntimeCueSet.HandleGameplayCue(ASC, CueTag, EventType, LocalParams);

    // --- Step 3: ASC-level IGameplayCueInterface::HandleGameplayCue (UE: lines 227-230) ---
    // Independent hook — ASC can intercept cues after CueSet dispatch
    if (ASC && bAcceptsCue)
        ASC->HandleGameplayCue(CueTag, EventType, LocalParams);

    bIsHandlingCue = false;
}

void GameplayCueManager::AddCueNotify(const GameplayTag& Tag, GameplayCueNotify_Static* Cue)
{
    if (!Cue) return;
    StaticCues[Tag].push_back(Cue);
    
    // Register with CueSet (Task 22 will call BuildAccelerationMap after INI loading)
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
                GameplayCueNotify_Static* cue = GameplayAbilitySystem::CreateCueStatic(name);
                if (cue)
                {
                    AddCueNotify(tag, cue);
                }

                // Register to RuntimeCueSet for tag-based lookup with parent fallback
                GameplayCueNotifyData data;
                data.GameplayCueTag = tag;
                data.GameplayCueNotifyObj = name;
                data.ParentDataIdx = -1;
                RuntimeCueSet.AddCueNotify(data);
            }
        }

        // Read ActorNotify list (comma-separated factory names)
        std::vector<StringName> actorNames;
        if (parser.Read(sectionName, "ActorNotify", actorNames))
        {
            for (const auto& name : actorNames)
            {
                GameplayCueNotify_Actor* cue = GameplayAbilitySystem::CreateCueActor(name);
                if (cue)
                {
                    AddCueNotify(tag, cue);
                }

                // Register to RuntimeCueSet for tag-based lookup with parent fallback
                GameplayCueNotifyData data;
                data.GameplayCueTag = tag;
                data.GameplayCueNotifyObj = name;
                data.ParentDataIdx = -1;
                RuntimeCueSet.AddCueNotify(data);
            }
        }
    }

    RuntimeCueSet.BuildAccelerationMap_Internal();
}
