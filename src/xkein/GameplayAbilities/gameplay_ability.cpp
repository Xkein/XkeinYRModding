#include "gameplay_ability.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/ge_component/ge_component_target_tags.h"
#include "xkein/GameplayAbilities/gameplay_cue.h"
#include "xkein/GameplayAbilities/ability_task/ability_task.h"

GameplayAbilitySpec::GameplayAbilitySpec(GameplayAbility* InAbility, int32 InLevel)
    : InputID(-1), SourceObject(entt::null), ActiveCount(0), InputPressed(false), RemoveAfterActivation(false), PendingRemove(false), bActivateOnce(false)
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
    
    // Check all tag requirements (required/blocked tags for activation, source, target)
    if (!DoesAbilitySatisfyTagRequirements(*ActorInfo->AbilitySystemCom))
    {
        return false;
    }

    // Check if this ability's input binding is currently blocked
    const GameplayAbilitySpec* Spec = FindAbilitySpec(Handle, ActorInfo);
    if (Spec && Spec->InputID >= 0 && ActorInfo->AbilitySystemCom->IsAbilityInputBlocked(Spec->InputID))
    {
        return false;
    }

    if (!K2_CanActivateAbility(*ActorInfo, Handle, OptionalRelevantTags))
    {
        return false;
    }

    return true;
}

bool GameplayAbility::ShouldAbilityRespondToEvent(const GameplayAbilityActorInfo* ActorInfo, const GameplayEventData* TriggerEventData) const
{
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
    AbilitySystemComponent* Comp = ActorInfo->AbilitySystemCom;

    if (GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced)
    {
        bIsActive = true;
        bIsBlockingOtherAbilities = true;
        bIsCancelable = true;
    }

    // This must be called before we start applying tags and blocking or canceling other abilities.
    CurrentActorInfo = ActorInfo;
    CurrentSpecHandle = Handle;
    CurrentActivationInfo = ActivationInfo;

    if (TriggerEventData)
    {
        CurrentEventData = *TriggerEventData;
    }

    if (Comp)
    {
        Comp->NotifyAbilityActivated(Handle, this);
    }

    if (Comp && Define)
    {
        if (bIsBlockingOtherAbilities && !Define->BlockAbilitiesWithTag.IsEmpty())
        {
            Comp->BlockAbilitiesWithTags(Define->BlockAbilitiesWithTag);
        }
        if (!Define->CancelAbilitiesWithTag.IsEmpty())
        {
            Comp->CancelAbilities(&Define->CancelAbilitiesWithTag, nullptr, this);
        }

        // Add activation owned tags to the owner
        if (!Define->ActivationOwnedTags.IsEmpty())
        {
            for (const auto& Tag : Define->ActivationOwnedTags.GameplayTags)
            {
                Comp->AddLooseGameplayTag(Tag);
            }
        }
    }

    // Spec's active count must be incremented after applying block/cancel tags,
    // otherwise the ability runs the risk of cancelling itself before it fully activates.
    if (Comp)
    {
        GameplayAbilitySpec* Spec = Comp->FindAbilitySpecFromHandle(Handle);
        if (Spec && Spec->ActiveCount < UINT8_MAX)
        {
            Spec->ActiveCount++;
        }
    }
}

void GameplayAbility::CallActivateAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
    const GameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded* OnGameplayAbilityEndedDelegate,
    const GameplayEventData* TriggerEventData)
{
    PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
    ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
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
    if (!CanBeCanceled())
    {
        return;
    }

    if (ScopeLockCount > 0)
    {
        WaitingToExecute.push_back([this, Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility]() {
            CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
        });
        return;
    }

    if (GameplayAbilitySpec* Spec = FindAbilitySpec(Handle, ActorInfo))
    {
        Spec->OnGameplayAbilityCancelled.Execute();
    }

    // End the ability but don't replicate it separately, we replicate the CancelAbility call directly
    bool bReplicateEndAbility = false;
    bool bWasCancelled = true;
    EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool GameplayAbility::IsEndAbilityValid(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo) const
{
    // Prevent EndAbility from being called multiple times
    if (bIsActive == false || bIsAbilityEnding == true)
    {
        return false;
    }

    // Check if ASC is valid
    AbilitySystemComponent* Comp = ActorInfo ? ActorInfo->AbilitySystemCom : nullptr;
    if (Comp == nullptr)
    {
        return false;
    }

    // Check if spec is still active
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

    if (ScopeLockCount > 0)
    {
        WaitingToExecute.push_back([this, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled]() {
            EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
        });
        return;
    }

    if (GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced)
    {
        bIsAbilityEnding = true;
    }

    // Give blueprint a chance to react
    K2_OnEndAbility(bWasCancelled);

    // Protect against blueprint causing us to EndAbility already
    if (bIsActive == false && GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced)
    {
        return;
    }

    // Broadcast end delegate on the spec
    if (GameplayAbilitySpec* Spec = FindAbilitySpec(Handle, ActorInfo))
    {
        Spec->OnGameplayAbilityEnded.Execute(Spec);
    }

    if (GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced)
    {
        bIsActive = false;
        bIsAbilityEnding = false;
        bIsCancelable = false;
        bIsBlockingOtherAbilities = false;
    }

    // Tell all our tasks that we are finished and they should cleanup
    for (int32 TaskIdx = static_cast<int32>(ActiveTasks.size()) - 1; TaskIdx >= 0; --TaskIdx)
    {
        AbilityTask* Task = ActiveTasks[TaskIdx];
        if (Task)
        {
            Task->OnDestroy(true);
            delete Task;
        }
    }
    ActiveTasks.clear();

    AbilitySystemComponent* const Comp = ActorInfo->AbilitySystemCom;
    if (Comp)
    {
        // Remove tags we added to owner
        if (Define && !Define->ActivationOwnedTags.IsEmpty())
        {
            for (const auto& Tag : Define->ActivationOwnedTags.GameplayTags)
            {
                Comp->RemoveLooseGameplayTag(Tag);
            }
        }

        // Remove tracked GameplayCues that we added
        for (const GameplayTag& CueTag : TrackedGameplayCues)
        {
            Comp->RemoveGameplayCue(CueTag);
        }
        TrackedGameplayCues.clear();

        if (bIsBlockingOtherAbilities && Define && !Define->BlockAbilitiesWithTag.IsEmpty())
        {
            // Unblock abilities
            Comp->UnBlockAbilitiesWithTags(Define->BlockAbilitiesWithTag);
        }

        // Tell owning AbilitySystemComponent that we ended so it can do stuff (including deleting us)
        Comp->NotifyAbilityEnded(Handle, this, bWasCancelled);
    }

    // Reset event data for instanced abilities
    if (GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced)
    {
        CurrentEventData = GameplayEventData{};
    }
}

// ============================================================
// Wave 2 Task 11 - New virtual methods
// ============================================================

void GameplayAbility::ExternalEndAbility()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void GameplayAbility::ExternalCancelAbility()
{
    CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

bool GameplayAbility::IsActive() const
{
	// Only Instanced-Per-Actor abilities persist between activations
	if (GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::InstancedPerActor)
	{
		return bIsActive;
	}

	// this should not be called on NonInstanced warn about it, Should call IsActive on the ability spec instead
	if (GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::NonInstanced)
	{
		// ABILITY_LOG(Warning, TEXT("UGameplayAbility::IsActive() called on %s NonInstanced ability, call IsActive on the Ability Spec instead"), *GetName());
	}

	// NonInstanced and Instanced-Per-Execution abilities are by definition active unless they are pending kill
	// return IsValid(this);
    return true;
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

// ============================================================
// GameplayCue tracking
// ============================================================

void GameplayAbility::K2_AddGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params)
{
    AbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (!ASC)
    {
        return;
    }

    ASC->AddGameplayCue(CueTag, Params);
    TrackedGameplayCues.push_back(CueTag);
}

void GameplayAbility::K2_RemoveGameplayCue(const GameplayTag& CueTag)
{
    AbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (!ASC)
    {
        return;
    }

    ASC->RemoveGameplayCue(CueTag);
    TrackedGameplayCues.erase(
        std::remove(TrackedGameplayCues.begin(), TrackedGameplayCues.end(), CueTag),
        TrackedGameplayCues.end());
}

// ============================================================
// Scope lock
// ============================================================

void GameplayAbility::DecrementListLock() const
{
    if (--ScopeLockCount == 0)
    {
        // execute delayed functions in the order they came in
        // These may end or cancel this ability
        for (auto& Func : WaitingToExecute)
        {
            Func();
        }
        WaitingToExecute.clear();
    }
}
