#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "YRpp/GeneralStructures.h"

/** Event type for gameplay cues */
ENUM()
enum EGameplayCueEvent : int
{
    OnActive,     // Cue activated (persistent effects begin)
    WhileActive,  // Cue is active (per-frame for persistent)
    Executed,     // One-shot execution (instant effects)
    Removed       // Cue removed (persistent effects end)
};

/** Simple gameplay cue parameters */
CLASS()
struct GameplayCueParameters
{
    PROPERTY()
    float NormalizedMagnitude = 1.0f;

    PROPERTY()
    GameplayTagContainer AggregatedSourceTags;

    PROPERTY()
    GameplayTagContainer AggregatedTargetTags;

    PROPERTY()
    CoordStruct Location;

    PROPERTY()
    CoordStruct Normal;

    PROPERTY()
    GameplayEffectContextHandle EffectContext;

    PROPERTY()
    float RawMagnitude = 0.0f;
};

/** Base class for gameplay cue notifies (simplified) */
CLASS(BindJs)
class GameplayCueNotify_Static
{
public:
    virtual void OnExecute(const GameplayTag& CueTag, const GameplayCueParameters& Params) {}
    virtual void OnActive(const GameplayTag& CueTag, const GameplayCueParameters& Params) {}
    virtual void OnRemove(const GameplayTag& CueTag, const GameplayCueParameters& Params) {}
};

/** Actor-based gameplay cue (stub) */
CLASS(BindJs)
class GameplayCueNotify_Actor
{
public:
    virtual void OnBurst(const GameplayTag& CueTag, const GameplayCueParameters& Params) {}
    virtual void OnBecomeRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params) {}
    virtual void OnCeaseRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params) {}
};
