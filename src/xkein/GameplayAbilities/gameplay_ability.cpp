#include "gameplay_ability.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/ge_component/ge_component_target_tags.h"

GameplayAbilitySpec::GameplayAbilitySpec(GameplayAbility* InAbility, int32 InLevel)
    : ActiveCount(0)
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

    // Check blocked tags on the actor — any blocked tag on the owning ASC prevents activation
    if (!Define->ActivationBlockedTags.IsEmpty() &&
        ActorInfo->AbilitySystemCom->GetOwnedGameplayTags().HasAny(Define->ActivationBlockedTags))
    {
        return false;
    }
    
    // Check source tags against required/blocked tags
    // Note: full implementation would check against ASC's owned tags
    if (!K2_CanActivateAbility(*ActorInfo, Handle, OptionalRelevantTags))
    {
        return false;
    }

    return true;
}

void GameplayAbility::ActivateAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, const GameplayEventData* TriggerEventData)
{
    K2_OnActivateAbility(TriggerEventData);
}

void GameplayAbility::PreActivate(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded* OnGameplayAbilityEndedDelegate,
    const GameplayEventData* TriggerEventData)
{
    CurrentActorInfo = ActorInfo;
    CurrentSpecHandle = Handle;
    CurrentActivationInfo = ActivationInfo;
    bIsActive = true;
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
    
    // Check cooldown
    if (!CheckCooldown(Handle, ActorInfo, OptionalRelevantTags))
    {
        return false;
    }
    
    // Check cost
    if (!CheckCost(Handle, ActorInfo, OptionalRelevantTags))
    {
        return false;
    }

    ApplyCooldown(Handle, ActorInfo, ActivationInfo);
    ApplyCost(Handle, ActorInfo, ActivationInfo);
    K2_OnCommitExecute();

    return true;
}

const GameplayTagContainer* GameplayAbility::GetCooldownTags() const
{
    GameplayEffect* CDGE = GetCooldownGameplayEffect();
    if (!CDGE) return nullptr;

    for (auto* Component : CDGE->GEComponents)
    {
        if (auto* TagComp = dynamic_cast<TargetTagsGEComponent*>(Component))
        {
            return &TagComp->GrantedTags;
        }
    }
    return nullptr;
}

bool GameplayAbility::CheckCooldown(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo, 
    GameplayTagContainer* OptionalRelevantTags) const
{
    if (!ActorInfo || !ActorInfo->AbilitySystemCom) return false;

    const GameplayTagContainer* CooldownTags = GetCooldownTags();
    if (CooldownTags && !CooldownTags->IsEmpty())
    {
        if (ActorInfo->AbilitySystemCom->HasAnyMatchingGameplayTags(*CooldownTags))
        {
            return false;
        }
    }
    return true;
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
    GameplayEffect* CostGE = GetCostGameplayEffect();
    if (CostGE)
    {
        if (!ActorInfo || !ActorInfo->AbilitySystemCom) return false;

        int32 Level = GetAbilityLevel(Handle);
        GameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemCom->MakeEffectContext();

        if (!ActorInfo->AbilitySystemCom->CanApplyAttributeModifiers(CostGE, static_cast<float>(Level), EffectContext))
        {
            return false;
        }
    }
    return true;
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

bool GameplayAbility::IsEndAbilityValid(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo) const
{
    // 防止 EndAbility 被多次调用
    if (bIsActive == false || bIsAbilityEnding == true)
    {
        return false;
    }

    // 检查 ASC 是否有效
    AbilitySystemComponent* Comp = ActorInfo ? ActorInfo->AbilitySystemCom : nullptr;
    if (Comp == nullptr)
    {
        return false;
    }

    // 检查 spec 是否仍然活跃
    const GameplayAbilitySpec* Spec = FindAbilitySpec(Handle, ActorInfo);
    const bool bIsSpecActive = Spec ? Spec->IsActive() : IsActive();
    if (!bIsSpecActive)
    {
        return false;
    }

    return true;
}

void GameplayAbility::EndAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (!IsEndAbilityValid(Handle, ActorInfo))
    {
        return;
    }

    bIsAbilityEnding = true;

    K2_OnEndAbility(bWasCancelled);

    // 防止 K2 回调中重入 EndAbility 导致重复清理
    if (bIsActive == false)
    {
        return;
    }

    // 广播结束委托
    if (GameplayAbilitySpec* Spec = FindAbilitySpec(Handle, ActorInfo))
    {
        if (Spec->ActiveCount > 0)
        {
            Spec->ActiveCount--;
        }
        Spec->OnGameplayAbilityEnded.publish(Spec);
        
        if (Spec->RemoveAfterActivation)
        {
            // Mark for removal - actual removal happens in Tick to avoid iterator invalidation
        }
    }

    bIsActive = false;
    bIsAbilityEnding = false;

    CurrentActorInfo = nullptr;
    CurrentSpecHandle = GameplayAbilitySpecHandle();
    CurrentActivationInfo = GameplayAbilityActivationInfo();
    CurrentEventData = GameplayEventData();
}

// ============================================================
// Wave 2 Task 11 - New virtual methods
// ============================================================

bool GameplayAbility::CanBeCanceled() const
{
    return true;
}

void GameplayAbility::ExternalEndAbility()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void GameplayAbility::ExternalCancelAbility()
{
    CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

bool GameplayAbility::DoesAbilitySatisfyTagRequirements(const AbilitySystemComponent& ASC) const
{
    if (!Define)
    {
        return false;
    }

    const GameplayTagContainer& OwnerTags = ASC.GetOwnedGameplayTags();

    // ActivationRequiredTags: ASC must have all of these
    if (Define->ActivationRequiredTags.IsValid() && !OwnerTags.HasAll(Define->ActivationRequiredTags))
    {
        return false;
    }

    // ActivationBlockedTags: ASC must have none of these
    if (Define->ActivationBlockedTags.IsValid() && OwnerTags.HasAny(Define->ActivationBlockedTags))
    {
        return false;
    }

    // SourceRequiredTags: ASC must have all of these
    if (Define->SourceRequiredTags.IsValid() && !OwnerTags.HasAll(Define->SourceRequiredTags))
    {
        return false;
    }

    // SourceBlockedTags: ASC must have none of these
    if (Define->SourceBlockedTags.IsValid() && OwnerTags.HasAny(Define->SourceBlockedTags))
    {
        return false;
    }

    // TargetRequiredTags: ASC must have all of these
    if (Define->TargetRequiredTags.IsValid() && !OwnerTags.HasAll(Define->TargetRequiredTags))
    {
        return false;
    }

    // TargetBlockedTags: ASC must have none of these
    if (Define->TargetBlockedTags.IsValid() && OwnerTags.HasAny(Define->TargetBlockedTags))
    {
        return false;
    }

    return true;
}

void GameplayAbility::SendGameplayEvent(const GameplayTag& EventTag, const GameplayEventData& Payload) const
{
    AbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (!ASC)
    {
        return;
    }

    ASC->HandleGameplayEvent(EventTag, &Payload);
}

int32 GameplayAbility::GetAbilityLevel(const GameplayAbilitySpecHandle Handle) const
{
    if (const GameplayAbilitySpec* Spec = FindAbilitySpec(Handle, CurrentActorInfo))
    {
        return Spec->Level;
    }

    return 0;
}
