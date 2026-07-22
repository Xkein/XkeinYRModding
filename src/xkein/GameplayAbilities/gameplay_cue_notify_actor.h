#pragma once
#include "xkein/GameplayAbilities/gameplay_cue.h"
#include "xkein/GameplayAbilities/gameplay_cue_notify_static.h"
#include <AnimTypeClass.h>

/** Instanced, one-shot gameplay cue with support for latent actions (delays, callbacks).
 *  Since it is instanced (extends Actor), it can hold state for timed operations like
 *  auto-destroying after animation playback completes.
 *  
 *  JS bindable: OnK2_OnBurst TDelegate follows CustomGameplayAbility pattern. */
CLASS(BindJs, AutoSavegame)
class GameplayCueNotify_BurstLatent : public GameplayCueNotify_Actor
{
public:
    /** JS-scriptable OnBurst callback (BlueprintImplementableEvent pattern).
     *  Called when this burst cue fires. Script can override for custom behavior. */
    PROPERTY(Savegame)
    TDelegate<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnBurst;

    /** Animation type to spawn on burst */
    PROPERTY()
    AnimTypeClass* BurstAnim = nullptr;

    /** Currently managed AnimClass entity spawned by OnBurst */
    AnimClass* SpawnedAnimEntity = nullptr;

    /** Create a one-shot animation and call JS callback.
     *  Can be overridden by C++ subclasses for custom burst behavior. */
    virtual void OnBurst(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        // Default: spawn one-shot AnimClass
        if (BurstAnim)
        {
            SpawnedAnimEntity = GameCreate<AnimClass>(BurstAnim, Params.Location, 0, 1, 0x600, 0, false);
            if (SpawnedAnimEntity)
                SpawnedAnimEntity->Start();
        }

        // Fire JS callback if bound
        if (OnK2_OnBurst.IsBound())
            OnK2_OnBurst.Execute(CueTag, Params);
    }

    /** Factory method for ScriptFunction registration */
    FUNCTION()
    static GameplayCueNotify_BurstLatent* CreateInstance()
    {
        return new GameplayCueNotify_BurstLatent();
    }
};

// ============================================================
// GameplayCueNotify_Looping — four-phase persistent cue
// ============================================================

/** Effects for the looping phase of a GameplayCueNotify_Looping.
 *  The looping AnimClass persists until OnCeaseRelevant is called. */
CLASS(BindJs)
struct GameplayCueNotify_LoopingEffects
{
    PROPERTY()
    AnimTypeClass* LoopingAnim = nullptr;

    PROPERTY()
    std::vector<StringName> WwiseEvents;  // looping audio events
};

/** Instanced, continuous gameplay cue with four-phase effect model.
 *  - Application (OnBecomeRelevant): one-shot burst effects when cue starts
 *  - Looping (WhileActive): persistent AnimClass that runs until Removed
 *  - Recurring (OnBurst): periodic burst during active phase
 *  - Removal (OnCeaseRelevant): one-shot burst + stop looping when cue ends */
CLASS(BindJs)
class GameplayCueNotify_Looping : public GameplayCueNotify_Actor
{
public:
    /** One-shot burst effects triggered when the looping cue becomes active */
    PROPERTY()
    GameplayCueNotify_BurstEffects ApplicationEffects;

    /** Persistent looping effects (AnimClass that stays alive until removed) */
    PROPERTY()
    GameplayCueNotify_LoopingEffects LoopingEffects;

    /** Burst effects triggered on periodic/Executed events while active */
    PROPERTY()
    GameplayCueNotify_BurstEffects RecurringEffects;

    /** One-shot burst effects triggered when the looping cue is removed */
    PROPERTY()
    GameplayCueNotify_BurstEffects RemovalEffects;

    /** Persistent AnimClass spawned by OnBecomeRelevant. Set to nullptr on cleanup. */
    AnimClass* SpawnedAnimEntity = nullptr;

    /** Whether looping effects have been stopped (prevents double-cleanup) */
    bool bLoopingEffectsRemoved = false;

    /** Cue becomes relevant (OnActive/WhileActive).
     *  Triggers ApplicationEffects + starts LoopingEffects. */
    virtual void OnBecomeRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        // Application burst effects
        for (auto* animType : ApplicationEffects.Anims)
        {
            if (animType)
            {
                auto* anim = GameCreate<AnimClass>(animType, Params.Location, 0, 1, 0x600, 0, false);
                if (anim) anim->Start();
            }
        }

        // Start looping effects (persistent)
        if (LoopingEffects.LoopingAnim)
        {
            SpawnedAnimEntity = GameCreate<AnimClass>(LoopingEffects.LoopingAnim, Params.Location,
                                               0, -1, 0x600, 0, false);
            if (SpawnedAnimEntity)
                SpawnedAnimEntity->Start();
        }
        bLoopingEffectsRemoved = false;
    }

    /** One-shot execution (Recurring effects during active state) */
    virtual void OnBurst(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        for (auto* animType : RecurringEffects.Anims)
        {
            if (animType)
            {
                auto* anim = GameCreate<AnimClass>(animType, Params.Location, 0, 1, 0x600, 0, false);
                if (anim) anim->Start();
            }
        }
    }

    /** Cue ceases to be relevant (Removed).
     *  Stops looping + triggers RemovalEffects. */
    virtual void OnCeaseRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        // Removal burst effects
        for (auto* animType : RemovalEffects.Anims)
        {
            if (animType)
            {
                auto* anim = GameCreate<AnimClass>(animType, Params.Location, 0, 1, 0x600, 0, false);
                if (anim) anim->Start();
            }
        }

        // Stop and clean up looping effects
        // AnimClass auto-finishes based on loopCount; release reference.
        if (!bLoopingEffectsRemoved && SpawnedAnimEntity)
        {
            SpawnedAnimEntity = nullptr;
            bLoopingEffectsRemoved = true;
        }
    }

    FUNCTION()
    static GameplayCueNotify_Looping* CreateInstance()
    {
        return new GameplayCueNotify_Looping();
    }
};
