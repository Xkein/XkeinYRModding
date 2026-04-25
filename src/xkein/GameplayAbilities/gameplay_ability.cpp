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

bool GameplayAbility::CanActivateAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayTagContainer* SourceTags, const GameplayTagContainer* TargetTags, GameplayTagContainer* OptionalRelevantTags) const
{
    if (!ActorInfo || !ActorInfo->AbilitySystemCom)
    {
        return false;
    }

    // Check blocked tags on the actor
    if (AbilityTags.HasAny(ActivationBlockedTags))
    {
        return false;
    }
    
    // Check source tags against required/blocked tags
    // Note: full implementation would check against ASC's owned tags
    return true;
}

void GameplayAbility::ActivateAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, const GameplayEventData* TriggerEventData)
{
    // Base implementation: empty. Subclasses override this to implement specific ability logic.
}

void GameplayAbility::PreActivate(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded* OnGameplayAbilityEndedDelegate,
    const GameplayEventData* TriggerEventData)
{
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
    
    return true;
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
    EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility, true);
}

void GameplayAbility::EndAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    // Trigger the ended delegate if the ASC and spec exist
    if (ActorInfo && ActorInfo->AbilitySystemCom)
    {
        auto& Abilities = ActorInfo->AbilitySystemCom->ActivatableAbilities;
        for (auto& Spec : Abilities)
        {
            if (Spec.Handle == Handle)
            {
                Spec.OnGameplayAbilityEnded.publish(&Spec);
                
                // If marked for removal after activation, remove it now
                if (Spec.RemoveAfterActivation)
                {
                    // Mark for removal - actual removal happens in Tick to avoid iterator invalidation
                }
                break;
            }
        }
    }
}
