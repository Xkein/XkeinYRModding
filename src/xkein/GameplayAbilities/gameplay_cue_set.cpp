#include "gameplay_cue_set.h"
#include "ability_system_globals.h"
#include "ability_system_component.h"

void GameplayCueSet::AddCueNotify(const GameplayCueNotifyData& Data)
{
    GameplayCueData.push_back(Data);
}

void GameplayCueSet::BuildAccelerationMap_Internal()
{
    GameplayCueDataMap.clear();

    // Step 1: Map every registered tag directly to its index
    for (int32 i = 0; i < (int32)GameplayCueData.size(); ++i)
    {
        GameplayCueDataMap[GameplayCueData[i].GameplayCueTag] = i;
    }

    // Step 2: Set up ParentDataIdx chain for hierarchical fallback
    // For each entry, find the deepest registered parent tag.
    // E.g., "Damage.Fire.Burning" → parent "Damage.Fire" (depth 2) over "Damage" (depth 1)
    for (int32 i = 0; i < (int32)GameplayCueData.size(); ++i)
    {
        if (GameplayCueData[i].ParentDataIdx != -1)
            continue; // Already set manually by user

        const GameplayTag& currentTag = GameplayCueData[i].GameplayCueTag;
        int32 bestParentIdx = -1;
        int32 bestDepth = -1;

        for (int32 j = 0; j < (int32)GameplayCueData.size(); ++j)
        {
            if (i == j)
                continue;

            // Does tag[j] match as a parent of tag[i]?
            // "Damage.Fire.Burning".MatchesTag("Damage.Fire") → true
            if (currentTag.MatchesTag(GameplayCueData[j].GameplayCueTag))
            {
                // MatchesTagDepth returns the parent's depth (dot count + 1) if matched
                int32 depth = currentTag.MatchesTagDepth(GameplayCueData[j].GameplayCueTag);
                if (depth > bestDepth)
                {
                    bestDepth = depth;
                    bestParentIdx = j;
                }
            }
        }
        GameplayCueData[i].ParentDataIdx = bestParentIdx;
    }
}

void GameplayCueSet::HandleGameplayCue(AbilitySystemComponent* ASC, const GameplayTag& CueTag,
                                        EGameplayCueEvent EventType, const GameplayCueParameters& Params)
{
    // Step 1: Find the best matching index for this tag
    int32 dataIdx = -1;

    // Check exact match first (fast path via acceleration map)
    auto it = GameplayCueDataMap.find(CueTag);
    if (it != GameplayCueDataMap.end())
    {
        dataIdx = it->second;
    }
    else
    {
        // Parent fallback: scan all registered tags for the closest parent match
        // This handles child tags that weren't registered at BuildAccelerationMap_Internal time
        int32 bestDepth = -1;
        for (int32 i = 0; i < (int32)GameplayCueData.size(); ++i)
        {
            if (CueTag.MatchesTag(GameplayCueData[i].GameplayCueTag))
            {
                int32 depth = CueTag.MatchesTagDepth(GameplayCueData[i].GameplayCueTag);
                if (depth > bestDepth)
                {
                    bestDepth = depth;
                    dataIdx = i;
                }
            }
        }
    }

    // Step 2: Get target entity from ASC
    entt::entity TargetEntity = entt::null;
    if (ASC) TargetEntity = ASC->Owner;

    // Step 3: Walk the ParentDataIdx chain WITH IsOverride control (UE: HandleGameplayCueNotify_Internal)
    while (dataIdx >= 0)
    {
        const GameplayCueNotifyData& data = GameplayCueData[dataIdx];

        // Set MatchedTagName for stacking guard use
        const_cast<GameplayCueParameters&>(Params).MatchedTagName = data.GameplayCueTag;

        // --- Static path: CDO dispatch (UE: lines 296-311) ---
        GameplayCueNotify_Static* nonInstancedCue = GameplayAbilitySystem::CreateCueStatic(data.GameplayCueNotifyObj);
        if (nonInstancedCue && nonInstancedCue->HandlesEvent(EventType))
        {
            switch (EventType)
            {
                case EGameplayCueEvent::Executed:
                    nonInstancedCue->OnExecute(CueTag, Params); break;
                case EGameplayCueEvent::OnActive:
                case EGameplayCueEvent::WhileActive:
                    nonInstancedCue->OnActive(CueTag, Params); break;
                case EGameplayCueEvent::Removed:
                    nonInstancedCue->OnRemove(CueTag, Params); break;
            }

            // IsOverride: stop parent fallback if true (UE: lines 302-304)
            if (!nonInstancedCue->IsOverride)
                dataIdx = data.ParentDataIdx;
            else
                return;
            continue;
        }

        // --- Actor path: centralized HandleGameplayCue dispatch (UE: lines 313-349) ---
        GameplayCueNotify_Actor* instancedCue = GameplayAbilitySystem::CreateCueActor(data.GameplayCueNotifyObj);
        if (instancedCue && instancedCue->HandlesEvent(EventType))
        {
            // Central dispatch through HandleGameplayCue (handles gating, stacking, K2, auto-destroy internally)
            instancedCue->HandleGameplayCue(TargetEntity, EventType, Params);

            // Executed-then-Remove shortcut (UE: lines 316-319, 338-341)
            bool bShouldDestroy = (EventType == EGameplayCueEvent::Executed && 
                                   !Params.bGameplayEffectActive && 
                                   instancedCue->bAutoDestroyOnRemove);
            if (bShouldDestroy)
            {
                instancedCue->HandleGameplayCue(TargetEntity, EGameplayCueEvent::Removed, Params);
            }

            // IsOverride: stop parent fallback if true (UE: lines 333-335)
            if (!instancedCue->IsOverride)
                dataIdx = data.ParentDataIdx;
            else
                return;
            continue;
        }

        // Neither factory matched for this entry — try parent (fallback chain)
        // (UE pattern: if notify exists but doesn't HandlesEvent, fall through to parent;
        //  the `continue` above is reached only when the notify doesn't handle this event type)
        dataIdx = data.ParentDataIdx;
    }
}
