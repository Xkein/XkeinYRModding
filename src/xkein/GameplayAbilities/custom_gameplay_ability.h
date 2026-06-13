#pragma once
#include "xkein/GameplayAbilities/gameplay_ability.h"
#include <functional>

CLASS(BindJs)
class CustomGameplayAbility : public GameplayAbility
{
public:
    CustomGameplayAbility();

    FUNCTION()
    static CustomGameplayAbility* Create();

    bool K2_CanActivateAbility(const GameplayAbilityActorInfo& ActorInfo, const GameplayAbilitySpecHandle Handle,
        GameplayTagContainer* OptionalRelevantTags) const override
    {
        if (OnK2CanActivateAbility)
        {
            return OnK2CanActivateAbility(ActorInfo, Handle, OptionalRelevantTags);
        }
        return true;
    }

    void K2_OnActivateAbility(const GameplayEventData* TriggerEventData) override
    {
        if (TriggerEventData && OnK2ActivateAbilityFromEvent)
        {
            OnK2ActivateAbilityFromEvent(*TriggerEventData);
            return;
        }
        if (OnK2ActivateAbility)
        {
            OnK2ActivateAbility();
        }
    }

    void K2_OnCommitExecute() override
    {
        if (OnK2CommitExecute)
        {
            OnK2CommitExecute();
        }
    }

    void K2_OnEndAbility(bool bWasCancelled) override
    {
        if (OnK2OnEndAbility)
        {
            OnK2OnEndAbility(bWasCancelled);
        }
    }

    FUNCTION()
    void K2_CancelAbility()
    {
        CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
    }

    FUNCTION()
    bool K2_CommitAbility()
    {
        return CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, nullptr);
    }

    FUNCTION()
    bool K2_CommitAbilityCooldown()
    {
        if (!CheckCooldown(CurrentSpecHandle, CurrentActorInfo, nullptr))
        {
            return false;
        }
        ApplyCooldown(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
        return true;
    }

    FUNCTION()
    bool K2_CommitAbilityCost()
    {
        if (!CheckCost(CurrentSpecHandle, CurrentActorInfo, nullptr))
        {
            return false;
        }
        ApplyCost(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
        return true;
    }

    FUNCTION()
    bool K2_CheckAbilityCooldown()
    {
        return CheckCooldown(CurrentSpecHandle, CurrentActorInfo, nullptr);
    }

    FUNCTION()
    bool K2_CheckAbilityCost()
    {
        return CheckCost(CurrentSpecHandle, CurrentActorInfo, nullptr);
    }

    FUNCTION()
    void K2_EndAbility()
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
    }

    FUNCTION()
    void K2_EndAbilityLocally()
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
    }

    PROPERTY()
    std::function<bool(GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)> OnK2CanActivateAbility;

    PROPERTY()
    std::function<void()> OnK2ActivateAbility;

    PROPERTY()
    std::function<void(const GameplayEventData&)> OnK2ActivateAbilityFromEvent;

    PROPERTY()
    std::function<void()> OnK2CommitExecute;

    PROPERTY()
    std::function<void(bool)> OnK2OnEndAbility;
};
