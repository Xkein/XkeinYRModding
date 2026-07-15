#pragma once
#include "xkein/GameplayAbilities/gameplay_cue.h"
#include "xkein/GameplayAbilities/gameplay_cue_notify_actor.h"
#include "core/tool/delegate.h"

/** Custom gameplay cue notify (Stateless) with JS-scriptable callbacks.
 *  Follows CustomGameplayAbility pattern: virtual methods + PROPERTY TDelegate for JS overrides. */
CLASS(BindJs)
class CustomGameplayCueNotify_Static : public GameplayCueNotify_Static
{
public:
    PROPERTY(Savegame)
    TDelegate<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnExecute;

    PROPERTY(Savegame)
    TDelegate<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnActive;

    PROPERTY(Savegame)
    TDelegate<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnRemove;

    virtual void OnExecute(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Static::OnExecute(CueTag, Params);
        if (OnK2_OnExecute.IsBound()) OnK2_OnExecute.Execute(CueTag, Params);
    }
    virtual void OnActive(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Static::OnActive(CueTag, Params);
        if (OnK2_OnActive.IsBound()) OnK2_OnActive.Execute(CueTag, Params);
    }
    virtual void OnRemove(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Static::OnRemove(CueTag, Params);
        if (OnK2_OnRemove.IsBound()) OnK2_OnRemove.Execute(CueTag, Params);
    }
};

/** Custom burst-latent cue (instanced) with JS callback for OnBurst. */
CLASS(BindJs, AutoSavegame)
class CustomGameplayCueNotify_BurstLatent : public GameplayCueNotify_BurstLatent
{
public:
    PROPERTY(Savegame)
    TDelegate<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnBurst;

    virtual void OnBurst(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_BurstLatent::OnBurst(CueTag, Params);
        if (OnK2_OnBurst.IsBound()) OnK2_OnBurst.Execute(CueTag, Params);
    }
};

/** Custom looping cue (instanced) with JS callbacks for all phases. */
CLASS(BindJs, AutoSavegame)
class CustomGameplayCueNotify_Looping : public GameplayCueNotify_Looping
{
public:
    PROPERTY(Savegame)
    TDelegate<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnBurst;

    PROPERTY(Savegame)
    TDelegate<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnBecomeRelevant;

    PROPERTY(Savegame)
    TDelegate<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnCeaseRelevant;

    virtual void OnBurst(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Looping::OnBurst(CueTag, Params);
        if (OnK2_OnBurst.IsBound()) OnK2_OnBurst.Execute(CueTag, Params);
    }
    virtual void OnBecomeRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Looping::OnBecomeRelevant(CueTag, Params);
        if (OnK2_OnBecomeRelevant.IsBound()) OnK2_OnBecomeRelevant.Execute(CueTag, Params);
    }
    virtual void OnCeaseRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Looping::OnCeaseRelevant(CueTag, Params);
        if (OnK2_OnCeaseRelevant.IsBound()) OnK2_OnCeaseRelevant.Execute(CueTag, Params);
    }
};
