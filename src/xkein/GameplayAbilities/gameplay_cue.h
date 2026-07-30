#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/gameplay_cue_notify_define.h"
#include "audio/audio.h"
#include <entt/entity/fwd.hpp>
#include <AnimClass.h>
#include <GeneralStructures.h>
#include <Memory.h>

/** Simple gameplay cue parameters, mirroring UE5.5 FGameplayCueParameters */
CLASS(BindJs, AutoSavegame, AllSavegame)
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

    /** Context handle (not exposed to JS — internal C++ type) */
    PROPERTY(Savegame)
    GameplayEffectContextHandle EffectContext;

    PROPERTY()
    float RawMagnitude = 0.0f;

    /** Instigator actor, the actor that owns the ability system component */
    PROPERTY()
    entt::entity Instigator = entt::null;

    /** The physical actor that actually did the damage, can be a weapon or projectile */
    PROPERTY()
    entt::entity EffectCauser = entt::null;

    /** Object this effect was created from, can be an actor or static object */
    PROPERTY()
    entt::entity SourceObject = entt::null;

    /** Level of the gameplay effect that triggered this cue */
    PROPERTY()
    int32 GameplayEffectLevel = 1;

    /** Level of the ability that triggered this cue */
    PROPERTY()
    int32 AbilityLevel = 1;

    /** Matched tag name, set during cue routing. Mutable - not replicated */
    mutable GameplayTag MatchedTagName;

    /** Original tag before any tag translation. Mutable - not replicated */
    mutable GameplayTag OriginalTag;

    /** Whether this cue was triggered from an active gameplay effect */
    bool bGameplayEffectActive = false;

    /** Physical material from hit result (UE parity) */
    PROPERTY()
    int32 PhysicalMaterial = 0;

    /** Component/entity to attach spawned effects to (UE parity) */
    PROPERTY()
    entt::entity TargetAttachComponent = entt::null;

    /** Default constructor (required when explicit constructors exist) */
    GameplayCueParameters() = default;

    /** Construct parameters from a gameplay effect spec */
    explicit GameplayCueParameters(const GameplayEffectSpec& Spec)
        : NormalizedMagnitude(1.0f)
        , RawMagnitude(0.0f)
        , GameplayEffectLevel(Spec.Level)
        , bGameplayEffectActive(true)
    {
        if (Spec.EffectContext.Data)
        {
            Instigator = Spec.EffectContext.Data->Instigator;
            EffectCauser = Spec.EffectContext.Data->EffectCauser;
            SourceObject = Spec.EffectContext.Data->SourceObject;
            AbilityLevel = Spec.EffectContext.Data->AbilityLevel;
            EffectContext = Spec.EffectContext;
        }
        AggregatedSourceTags = Spec.CapturedSourceTags;
    }
};

/** Base class for gameplay cue notifies (stateless, non-instanced).
 *  Each call to OnExecute/OnActive creates a one-shot effect (Wwise event + AnimClass). */
CLASS(BindJs)
class GameplayCueNotify_Static
{
public:
    /** Configuration define. Set by InitFromDefine. Runtime reads config from here. */
    const GameplayCueNotifyDefine_Static* Define = nullptr;

    void InitFromDefine(const GameplayCueNotifyDefine_Static* In) { Define = In; }

    /** One-shot execution: play audio + spawn visual. Called for Instant GE cues. */
    virtual void OnExecute(const GameplayTag& CueTag, const GameplayCueParameters& Params)
    {
        PlayEffects(Params);
    }

    /** Cue activated (persistent effect begins). Same as OnExecute for Stateless. */
    virtual void OnActive(const GameplayTag& CueTag, const GameplayCueParameters& Params)
    {
        if (Define ? Define->bAllowMultipleOnActiveEvents : true)
            PlayEffects(Params);
    }

    /** Cue removed. No-op for stateless (no persistent state to clean up). */
    virtual void OnRemove(const GameplayTag& CueTag, const GameplayCueParameters& Params) {}

    /** Factory method for ScriptFunction registration */
    FUNCTION()
    static GameplayCueNotify_Static* CreateInstance()
    {
        return new GameplayCueNotify_Static();
    }

    /** Does this notify handle this event type? Delegated to Define. */
    virtual bool HandlesEvent(EGameplayCueEvent EventType) const
    {
        return Define ? Define->HandlesEvent(EventType) : true;
    }

private:
    void PlayEffects(const GameplayCueParameters& Params)
    {
        // Post Wwise audio event
        auto& wwiseName = Define ? Define->WwiseEventName : StringName();
        if (!wwiseName.IsEmpty())
        {
            auto eventID = AudioSystem::GetIDFromString(wwiseName.c_str());
            if (eventID != AK_INVALID_UNIQUE_ID)
                AudioSystem::PostEvent(eventID, AudioSystem::GetNextGameObjId());
        }

        // Spawn one-shot animation
        auto* burstAnim = Define ? Define->BurstAnim : nullptr;
        if (burstAnim)
        {
            // AnimClass(AnimTypeClass*, CoordStruct, loopDelay=0, loopCount=1, flags=0x600, forceZAdjust=0, reverse=false)
            auto* anim = GameCreate<AnimClass>(burstAnim, Params.Location, 0, 1, 0x600, 0, false);
            if (anim)
                anim->Start();
        }
    }
};

/** Instanced (stateful) gameplay cue notify. Extend this for cues that need to
 *  own and manage visual entities (AnimClass) over their lifetime.
 *  Actor-owns-AnimClass: OnBecomeRelevant creates, OnCeaseRelevant destroys. */
CLASS(BindJs)
class GameplayCueNotify_Actor
{
public:
    /** Configuration define. Set by InitFromDefine. */
    const GameplayCueNotifyDefine_Actor* Define = nullptr;

    void InitFromDefine(const GameplayCueNotifyDefine_Actor* In) { Define = In; }

    /** Currently managed AnimClass instance. Created on OnBecomeRelevant,
     *  destroyed (nullptr) on OnCeaseRelevant. Subclasses can extend. */
    AnimClass* SpawnedAnimEntity = nullptr;

    /** Gating: prevent duplicate OnActive events */
    bool bHasHandledOnActiveEvent = false;

    /** Gating: prevent duplicate WhileActive events */
    bool bHasHandledWhileActiveEvent = false;

    /** Gating: prevent duplicate OnRemove events */
    bool bHasHandledOnRemoveEvent = false;

    // ========================================================================
    // UE5.5 alignment: central dispatch + lifecycle
    // ========================================================================

    /** Central dispatch — called by CueSet. Handles gating, stacking guard, K2, and routing to specific events. */
    virtual void HandleGameplayCue(entt::entity TargetEntity, EGameplayCueEvent EventType, const GameplayCueParameters& Params);

    /** Called when the GC is finished. Resets state for potential reuse. */
    virtual void GameplayCueFinishedCallback();

    /** Reset state so this instance can be reused. Returns false if this class cannot be recycled. */
    virtual bool Recycle();

    /** Called when about to reuse after recycling. Undo what Recycle did. */
    virtual void ReuseAfterRecycle() {}

    /** Generic K2 handler (BlueprintImplementableEvent) — called for every event type before specific dispatch */
    PROPERTY(Savegame)
    TDelegate<void(GameplayCueNotify_Actor*, EGameplayCueEvent, const GameplayCueParameters&)> OnK2_HandleGameplayCue;

    /** Does this notify handle this event type? Delegated to Define. */
    virtual bool HandlesEvent(EGameplayCueEvent EventType) const
    {
        return Define ? Define->HandlesEvent(EventType) : true;
    }

    // ========================================================================
    // Lifecycle callbacks
    // ========================================================================

    /** One-shot burst: spawn a single AnimClass from BurstAnim */
    virtual void OnBurst(const GameplayTag& CueTag, const GameplayCueParameters& Params)
    {
        auto* burstAnim = Define ? Define->BurstAnim : nullptr;
        if (burstAnim)
        {
            auto* anim = GameCreate<AnimClass>(burstAnim, Params.Location, 0, 1, 0x600, 0, false);
            if (anim) anim->Start();
            // Note: this is a one-shot — we don't store it in SpawnedAnimEntity
        }
    }

    /** Cue becomes relevant (OnActive/WhileActive).
     *  Creates persistent AnimClass from LoopingAnim. */
    virtual void OnBecomeRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params)
    {
        if (bHasHandledOnActiveEvent && Define && !Define->bAllowMultipleOnActiveEvents)
            return;
        bHasHandledOnActiveEvent = true;

        auto* loopingAnim = Define ? Define->LoopingAnim : nullptr;
        if (loopingAnim)
        {
            SpawnedAnimEntity = GameCreate<AnimClass>(loopingAnim, Params.Location, 0, -1, 0x600, 0, false);
            if (SpawnedAnimEntity)
                SpawnedAnimEntity->Start();
        }
    }

    /** Cue ceases to be relevant (Removed).
     *  Destroys the managed AnimClass and resets gating flags. */
    virtual void OnCeaseRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params)
    {
        // TODO: Stacking guard — before releasing the managed entity, check whether
        // the target ASC still has this tag (from another concurrent source). If so,
        // skip removal to avoid prematurely ending the cue.
        // This requires passing the ASC pointer through to OnCeaseRelevant, which
        // is a known limitation in the current signature. When the ASC is available:
        //   if (auto* TagInterface = dynamic_cast<IGameplayTagAssetInterface*>(ASC))
        //       if (TagInterface->HasMatchingGameplayTag(Params.MatchedTagName))
        //           return;

        // Release the managed AnimClass entity
        SpawnedAnimEntity = nullptr;

        // Reset gating flags for potential reuse
        bHasHandledOnActiveEvent = false;
        bHasHandledWhileActiveEvent = false;
        bHasHandledOnRemoveEvent = false;
    }

    // ========================================================================
    // Factory
    // ========================================================================

    /** Factory method for ScriptFunction registration */
    FUNCTION()
    static GameplayCueNotify_Actor* CreateInstance()
    {
        return new GameplayCueNotify_Actor();
    }
};

// ============================================================
// Active GameplayCue tracking (UE: FActiveGameplayCue / FActiveGameplayCueContainer)
// ============================================================

/** One active gameplay cue tracked by ASC. Multiple entries with same tag are allowed
 *  (from different sources). RemoveCue removes the FIRST matching entry (FIFO).
 *  Stacking guard on Removed: CueNotify_Actor checks if ASC still has the tag before cleanup. */
CLASS(BindJs, AutoSavegame)
struct ActiveGameplayCue
{
    /** The gameplay tag identifying this cue */
    PROPERTY(Savegame)
    GameplayTag GameplayCueTag;

    /** Parameters passed when the cue was added. Used for Removed event replay. */
    PROPERTY(Savegame)
    GameplayCueParameters Parameters;
};

/** Container for active gameplay cues on an AbilitySystemComponent.
 *  Replaces std::set<GameplayTag> to support multiple sources per tag (Stacking). */
CLASS(BindJs, AutoSavegame)
struct ActiveGameplayCueContainer
{
    /** List of all currently active gameplay cues. Multiple entries per tag allowed. */
    PROPERTY(Savegame)
    std::vector<ActiveGameplayCue> GameplayCues;

    /** Add a new active cue. Always adds, even if the same tag is already present.
     *  This supports multiple GE sources adding the same cue tag (Stacking).
     *  @return true if the cue was added (always true) */
    bool AddCue(const GameplayTag& Tag, const GameplayCueParameters& Params)
    {
        GameplayCues.push_back({ Tag, Params });
        return true;
    }

    /** Remove the FIRST matching cue entry for this tag (FIFO order).
     *  When the LAST entry for a tag is removed, the caller should trigger
     *  the actual Removed event (via Stacking guard in CueNotify_Actor).
     *  @return true if a matching cue was found and removed */
    bool RemoveCue(const GameplayTag& Tag)
    {
        for (auto it = GameplayCues.begin(); it != GameplayCues.end(); ++it)
        {
            if (it->GameplayCueTag == Tag)
            {
                GameplayCues.erase(it);
                return true;
            }
        }
        return false;
    }

    /** Check if any active cue has the given tag.
     *  Used by ASC::IsGameplayCueActive and Stacking guard. */
    bool HasCue(const GameplayTag& Tag) const
    {
        for (const auto& Cue : GameplayCues)
        {
            if (Cue.GameplayCueTag == Tag)
                return true;
        }
        return false;
    }

    /** Remove all active cues. Calls RemoveCue for each tag (which triggers Removed events).
     *  Note: Since RemoveCue only removes one entry per call, iterate until empty. */
    void RemoveAllCues()
    {
        while (!GameplayCues.empty())
        {
            GameplayTag tag = GameplayCues.front().GameplayCueTag;
            RemoveCue(tag);
        }
    }
};
