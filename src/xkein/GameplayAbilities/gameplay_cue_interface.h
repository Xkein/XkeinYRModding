#pragma once
#include "gameplay_tag.h"
#include "gameplay_cue.h"  // for EGameplayCueEvent, GameplayCueParameters

/** Interface for objects that can receive gameplay cue events.
 *  Implemented by AbilitySystemComponent and potentially by target actors. */
class IGameplayCueInterface
{
public:
    virtual ~IGameplayCueInterface() = default;

    /** Called before routing a gameplay cue to check if the target accepts it.
     *  Default: accept all. Override to filter cues by tag or event type. */
    virtual bool ShouldAcceptGameplayCue(const GameplayTag& CueTag,
                                          EGameplayCueEvent EventType,
                                          const GameplayCueParameters& Params) const
    {
        return true;
    }

    /** Handle a gameplay cue event. Default: no-op.
     *  Implementors can override to add custom processing after/before CueSet dispatch. */
    virtual void HandleGameplayCue(const GameplayTag& CueTag,
                                    EGameplayCueEvent EventType,
                                    const GameplayCueParameters& Params)
    {
    }
};

/** Interface for objects that carry gameplay tags, used for Stacking checks.
 *  When a CueNotify_Actor receives a Removed event, it checks whether the
 *  target still has the matched tag (via HasMatchingGameplayTag) before
 *  actually running removal logic. This supports multiple overlapping sources. */
class IGameplayTagAssetInterface
{
public:
    virtual ~IGameplayTagAssetInterface() = default;

    /** Returns true if this object owns the given tag (including parent hierarchy).
     *  Used by CueNotify_Actor stacking guard on Removed events. */
    virtual bool HasMatchingGameplayTag(const GameplayTag& TagToCheck) const = 0;
};
