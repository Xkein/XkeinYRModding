#pragma once
#include "xkein/GameplayAbilities/gameplay_ability.h"

CLASS(BindJs, AutoSavegame, Swizzleable)
class CustomGameplayAbility : public GameplayAbility
{
public:
    CustomGameplayAbility();

    FUNCTION()
    static CustomGameplayAbility* Create();

    bool K2_CanActivateAbility(const GameplayAbilityActorInfo& ActorInfo, const GameplayAbilitySpecHandle Handle,
        GameplayTagContainer* OptionalRelevantTags) const override
    {
        if (OnK2CanActivateAbility.IsBound())
        {
            return OnK2CanActivateAbility.Execute(ActorInfo, Handle, OptionalRelevantTags);
        }
        return true;
    }

    void K2_OnActivateAbility(const GameplayEventData* TriggerEventData) override
    {
        if (TriggerEventData && OnK2ActivateAbilityFromEvent.IsBound())
        {
            OnK2ActivateAbilityFromEvent.Execute(*TriggerEventData);
            return;
        }
        if (OnK2ActivateAbility.IsBound())
        {
            OnK2ActivateAbility.Execute();
        }
    }

    void K2_OnCommitExecute() override
    {
        if (OnK2CommitExecute.IsBound())
        {
            OnK2CommitExecute.Execute();
        }
    }

    void K2_OnEndAbility(bool bWasCancelled) override
    {
        if (OnK2OnEndAbility.IsBound())
        {
            OnK2OnEndAbility.Execute(bWasCancelled);
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

    PROPERTY(Savegame)
    TDelegate<bool(GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)> OnK2CanActivateAbility;

    PROPERTY(Savegame)
    TDelegate<void()> OnK2ActivateAbility;

    PROPERTY(Savegame)
    TDelegate<void(const GameplayEventData&)> OnK2ActivateAbilityFromEvent;

    PROPERTY(Savegame)
    TDelegate<void()> OnK2CommitExecute;

    PROPERTY(Savegame)
    TDelegate<void(bool)> OnK2OnEndAbility;
};
IMPL_YR_SERIALIZE_SWIZZLE(CustomGameplayAbility);
