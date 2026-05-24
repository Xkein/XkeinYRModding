#include "gameplay_ability.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

GameplayAbilitySpec::GameplayAbilitySpec(GameplayAbility* InAbility, int32 InLevel)
{
    Ability = InAbility;
    Level = InLevel;
}

// ============================================================
// GameplayAbility lifecycle methods
// ============================================================

static GameplayAbilitySpec* FindAbilitySpec(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo)
{
    if (!ActorInfo || !ActorInfo->AbilitySystemCom)
    {
        return nullptr;
    }

    auto& Abilities = ActorInfo->AbilitySystemCom->ActivatableAbilities;
    for (auto& Spec : Abilities)
    {
        if (Spec.Handle == Handle)
        {
            return &Spec;
        }
    }

    return nullptr;
}

void GameplayAbility::InitFromDefine(GameplayAbilityDefine* AbilityDefine)
{
    this->Define = AbilityDefine;
    
}

bool GameplayAbility::CanActivateAbility(const GameplayAbilitySpecHandle Handle,
                                         const GameplayAbilityActorInfo* ActorInfo,
                                         const GameplayTagContainer*     SourceTags,
                                         const GameplayTagContainer*     TargetTags,
                                         GameplayTagContainer*           OptionalRelevantTags) const
{
    if (!ActorInfo || !ActorInfo->AbilitySystemCom)
    {
        return false;
    }

    if (!Define)
    {
        return false;
    }

    // Check blocked tags on the actor
    if (Define->AbilityTags.HasAny(Define->ActivationBlockedTags))
    {
        return false;
    }
    
    // Check source tags against required/blocked tags
    // Note: full implementation would check against ASC's owned tags
    if (OnK2CanActivateAbility)
    {
        GameplayAbilityActorInfo ActorInfoValue = *ActorInfo;
        if (!OnK2CanActivateAbility(ActorInfoValue, Handle, OptionalRelevantTags))
        {
            return false;
        }
    }

    return true;
}

void GameplayAbility::ActivateAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, const GameplayEventData* TriggerEventData)
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

void GameplayAbility::PreActivate(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded* OnGameplayAbilityEndedDelegate,
    const GameplayEventData* TriggerEventData)
{
    CurrentActorInfo = ActorInfo;
    CurrentSpecHandle = Handle;
    CurrentActivationInfo = ActivationInfo;
    if (TriggerEventData)
    {
        CurrentEventData = *TriggerEventData;
    }

    // Call the derived implementation
    ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void GameplayAbility::CallActivateAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded* OnGameplayAbilityEndedDelegate,
    const GameplayEventData* TriggerEventData)
{
    PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
}

bool GameplayAbility::CommitAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, GameplayTagContainer* OptionalRelevantTags)
{
    if (!ActorInfo || !ActorInfo->AbilitySystemCom)
    {
        return false;
    }
    
    AbilitySystemComponent* ASC = ActorInfo->AbilitySystemCom;
    
    // Check cooldown
    if (!ASC->CheckCooldown(Handle))
    {
        return false;
    }
    
    // Check cost
    if (!ASC->CheckCost(Handle))
    {
        return false;
    }

    ApplyCooldown(Handle, ActorInfo, ActivationInfo);
    ApplyCost(Handle, ActorInfo, ActivationInfo);
    if (OnK2CommitExecute)
    {
        OnK2CommitExecute();
    }

    return true;
}

void GameplayAbility::K2_CancelAbility()
{
    CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

bool GameplayAbility::K2_CommitAbility()
{
    return CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, nullptr);
}

bool GameplayAbility::K2_CommitAbilityCooldown()
{
    if (!CheckCooldown(CurrentSpecHandle, CurrentActorInfo, nullptr))
    {
        return false;
    }

    ApplyCooldown(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
    return true;
}

bool GameplayAbility::K2_CommitAbilityCost()
{
    if (!CheckCost(CurrentSpecHandle, CurrentActorInfo, nullptr))
    {
        return false;
    }

    ApplyCost(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
    return true;
}

bool GameplayAbility::K2_CheckAbilityCooldown()
{
    return CheckCooldown(CurrentSpecHandle, CurrentActorInfo, nullptr);
}

bool GameplayAbility::K2_CheckAbilityCost()
{
    return CheckCost(CurrentSpecHandle, CurrentActorInfo, nullptr);
}

void GameplayAbility::K2_EndAbility()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void GameplayAbility::K2_EndAbilityLocally()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

bool GameplayAbility::CheckCooldown(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo, 
    GameplayTagContainer* OptionalRelevantTags) const
{
    if (!ActorInfo || !ActorInfo->AbilitySystemCom) return false;
    return ActorInfo->AbilitySystemCom->CheckCooldown(Handle);
}

void GameplayAbility::ApplyCooldown(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo, 
    const GameplayAbilityActivationInfo ActivationInfo) const
{
    if (!ActorInfo || !ActorInfo->AbilitySystemCom) return;
    GameplayEffect* CooldownGE = GetCooldownGameplayEffect();
    if (CooldownGE)
    {
        ActorInfo->AbilitySystemCom->ApplyCooldown(Handle, CooldownGE);
    }
}

bool GameplayAbility::CheckCost(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo, 
    GameplayTagContainer* OptionalRelevantTags) const
{
    if (!ActorInfo || !ActorInfo->AbilitySystemCom) return false;
    return ActorInfo->AbilitySystemCom->CheckCost(Handle);
}

void GameplayAbility::ApplyCost(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo, 
    const GameplayAbilityActivationInfo ActivationInfo) const
{
    if (!ActorInfo || !ActorInfo->AbilitySystemCom) return;
    GameplayEffect* CostGE = GetCostGameplayEffect();
    if (CostGE)
    {
        ActorInfo->AbilitySystemCom->ApplyCost(Handle, CostGE);
    }
}

void GameplayAbility::CancelAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
    if (GameplayAbilitySpec* Spec = FindAbilitySpec(Handle, ActorInfo))
    {
        Spec->OnGameplayAbilityCancelled.publish();
    }
    EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility, true);
}

void GameplayAbility::EndAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (OnK2OnEndAbility)
    {
        OnK2OnEndAbility(bWasCancelled);
    }

    // Trigger the ended delegate if the ASC and spec exist
    if (GameplayAbilitySpec* Spec = FindAbilitySpec(Handle, ActorInfo))
    {
        Spec->OnGameplayAbilityEnded.publish(Spec);
        
        // If marked for removal after activation, remove it now
        if (Spec->RemoveAfterActivation)
        {
            // Mark for removal - actual removal happens in Tick to avoid iterator invalidation
        }
    }

    CurrentActorInfo = nullptr;
    CurrentSpecHandle = GameplayAbilitySpecHandle();
    CurrentActivationInfo = GameplayAbilityActivationInfo();
    CurrentEventData = GameplayEventData();
}
