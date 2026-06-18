#pragma once
#include "xkein/GameplayAbilities/gameplay_cue.h"
#include "xkein/GameplayAbilities/gameplay_cue_notify_actor.h"
#include <functional>

/** Custom gameplay cue notify (Stateless) with JS-scriptable callbacks.
 *  Follows CustomGameplayAbility pattern: virtual methods + PROPERTY std::function for JS overrides. */
CLASS(BindJs)
class CustomGameplayCueNotify_Static : public GameplayCueNotify_Static
{
public:
    PROPERTY()
    std::function<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnExecute;

    PROPERTY()
    std::function<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnActive;

    PROPERTY()
    std::function<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnRemove;

    virtual void OnExecute(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Static::OnExecute(CueTag, Params);
        if (OnK2_OnExecute) OnK2_OnExecute(CueTag, Params);
    }
    virtual void OnActive(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Static::OnActive(CueTag, Params);
        if (OnK2_OnActive) OnK2_OnActive(CueTag, Params);
    }
    virtual void OnRemove(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Static::OnRemove(CueTag, Params);
        if (OnK2_OnRemove) OnK2_OnRemove(CueTag, Params);
    }
};

/** Custom burst-latent cue (instanced) with JS callback for OnBurst. */
CLASS(BindJs)
class CustomGameplayCueNotify_BurstLatent : public GameplayCueNotify_BurstLatent
{
public:
    PROPERTY()
    std::function<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnBurst;

    virtual void OnBurst(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_BurstLatent::OnBurst(CueTag, Params);
        if (OnK2_OnBurst) OnK2_OnBurst(CueTag, Params);
    }
};

/** Custom looping cue (instanced) with JS callbacks for all phases. */
CLASS(BindJs)
class CustomGameplayCueNotify_Looping : public GameplayCueNotify_Looping
{
public:
    PROPERTY()
    std::function<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnBurst;

    PROPERTY()
    std::function<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnBecomeRelevant;

    PROPERTY()
    std::function<void(const GameplayTag&, const GameplayCueParameters&)> OnK2_OnCeaseRelevant;

    virtual void OnBurst(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Looping::OnBurst(CueTag, Params);
        if (OnK2_OnBurst) OnK2_OnBurst(CueTag, Params);
    }
    virtual void OnBecomeRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Looping::OnBecomeRelevant(CueTag, Params);
        if (OnK2_OnBecomeRelevant) OnK2_OnBecomeRelevant(CueTag, Params);
    }
    virtual void OnCeaseRelevant(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        GameplayCueNotify_Looping::OnCeaseRelevant(CueTag, Params);
        if (OnK2_OnCeaseRelevant) OnK2_OnCeaseRelevant(CueTag, Params);
    }
};
