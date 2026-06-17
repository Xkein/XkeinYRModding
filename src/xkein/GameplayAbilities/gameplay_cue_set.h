#pragma once
#include "gameplay_tag.h"
#include "gameplay_cue.h"
#include "core/reflection/reflection.h"
#include <vector>
#include <map>

class AbilitySystemComponent;
class GameplayCueNotifyDefine;

/** One entry in the GameplayCueSet lookup table */
struct GameplayCueNotifyData
{
    /** The gameplay tag this notify responds to */
    GameplayTag GameplayCueTag;
    
    /** Direct pointer to the notify define instance (set by AfterLoadIni) */
    GameplayCueNotifyDefine* DefinePtr = nullptr;
    
    /** Index of parent data for hierarchical fallback, -1 if none */
    int32 ParentDataIdx = -1;
};

/** Lookup table that maps GameplayTags to their registered CueNotify handlers,
 *  with automatic parent-tag fallback when a child tag has no registered handler. */
struct GameplayCueSet
{
    /** Ordered list of all registered cue notify data entries */
    std::vector<GameplayCueNotifyData> GameplayCueData;
    
    /** Acceleration map: GameplayTag → index into GameplayCueData.
     *  Built by BuildAccelerationMap_Internal() with parent fallback. */
    std::map<GameplayTag, int32> GameplayCueDataMap;
    
    /** Lazy rebuild flag. Set to true in AddCueNotify, cleared after BuildAccelerationMap_Internal(). */
    bool bNeedsRebuild = true;
    
    /** Main dispatch: look up CueTag and route to the appropriate notify.
     *  Falls back through ParentDataIdx chain if a notify doesn't handle the event. */
    void HandleGameplayCue(AbilitySystemComponent* ASC, const GameplayTag& CueTag,
                           EGameplayCueEvent EventType, const GameplayCueParameters& Params);
    
    /** Register a notify data entry. Call BuildAccelerationMap_Internal() after adding all entries. */
    void AddCueNotify(const GameplayCueNotifyData& Data);
    
    /** Build the acceleration map, filling in parent-tag fallback for all child tags.
     *  Called after all AddCueNotify calls are complete (e.g., after INI loading). */
    void BuildAccelerationMap_Internal();
};
