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

    if (dataIdx < 0)
        return; // No matching notify found for this tag

    // Step 2: Walk the ParentDataIdx chain
    // If the most-specific notify can't handle this event type (factory returns null),
    // fall back to its parent, then grandparent, etc.
    while (dataIdx >= 0)
    {
        const GameplayCueNotifyData& data = GameplayCueData[dataIdx];

        // Try static cue notify factory first
        GameplayCueNotify_Static* staticCue = GameplayAbilitySystem::CreateCueStatic(data.GameplayCueNotifyObj);
        if (staticCue)
        {
            switch (EventType)
            {
                case EGameplayCueEvent::Executed:
                    staticCue->OnExecute(CueTag, Params);
                    break;
                case EGameplayCueEvent::OnActive:
                case EGameplayCueEvent::WhileActive:
                    staticCue->OnActive(CueTag, Params);
                    break;
                case EGameplayCueEvent::Removed:
                    staticCue->OnRemove(CueTag, Params);
                    break;
            }
            return; // Handled by static notify
        }

        // Try actor-based cue notify factory
        GameplayCueNotify_Actor* actorCue = GameplayAbilitySystem::CreateCueActor(data.GameplayCueNotifyObj);
        if (actorCue)
        {
            switch (EventType)
            {
                case EGameplayCueEvent::Executed:
                    actorCue->OnBurst(CueTag, Params);
                    break;
                case EGameplayCueEvent::OnActive:
                case EGameplayCueEvent::WhileActive:
                    actorCue->OnBecomeRelevant(CueTag, Params);
                    break;
                case EGameplayCueEvent::Removed:
                    actorCue->OnCeaseRelevant(CueTag, Params);
                    break;
            }
            return; // Handled by actor notify
        }

        // Neither factory matched for this entry — try parent (fallback chain)
        dataIdx = data.ParentDataIdx;
    }
}
