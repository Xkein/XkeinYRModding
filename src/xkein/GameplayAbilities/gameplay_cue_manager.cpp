#include "gameplay_cue_manager.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

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

void GameplayCueManager::AddCueNotify(const GameplayTag&, GameplayCueNotify_Static*)
{
}

void GameplayCueManager::AddCueNotify(const GameplayTag&, GameplayCueNotify_Actor*)
{
}

void GameplayCueManager::AfterLoadIni(IniReader&, const char*, const char*)
{
}
