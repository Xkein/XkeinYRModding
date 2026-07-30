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
            return OnK2CanActivateAbility.Execute(const_cast<CustomGameplayAbility*>(this), ActorInfo, Handle, OptionalRelevantTags);
        }
        return true;
    }

    void K2_OnActivateAbility(const GameplayEventData* TriggerEventData) override
    {
        if (TriggerEventData && OnK2ActivateAbilityFromEvent.IsBound())
        {
            OnK2ActivateAbilityFromEvent.Execute(this, *TriggerEventData);
            return;
        }
        if (OnK2ActivateAbility.IsBound())
        {
            OnK2ActivateAbility.Execute(this);
        }
    }

    void K2_OnCommitExecute() override
    {
        if (OnK2CommitExecute.IsBound())
        {
            OnK2CommitExecute.Execute(this);
        }
    }

    void K2_OnEndAbility(bool bWasCancelled) override
    {
        if (OnK2OnEndAbility.IsBound())
        {
            OnK2OnEndAbility.Execute(this, bWasCancelled);
        }
    }

    PROPERTY(Savegame)
    TDelegate<bool(GameplayAbility*, GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)> OnK2CanActivateAbility;

    PROPERTY(Savegame)
    TDelegate<void(GameplayAbility*)> OnK2ActivateAbility;

    PROPERTY(Savegame)
    TDelegate<void(GameplayAbility*, const GameplayEventData&)> OnK2ActivateAbilityFromEvent;

    PROPERTY(Savegame)
    TDelegate<void(GameplayAbility*)> OnK2CommitExecute;

    PROPERTY(Savegame)
    TDelegate<void(GameplayAbility*, bool)> OnK2OnEndAbility;
};
IMPL_YR_SERIALIZE_SWIZZLE(CustomGameplayAbility);
