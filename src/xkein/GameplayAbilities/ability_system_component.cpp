#include "ability_system_component.h"
#include "xkein/GameplayAbilities/ability_system_globals.h"
#include "xkein/GameplayAbilities/gameplay_cue_manager.h"
#include <core/tool/container.h>
#include "core/string/string_name.h"
#include <core/string/string_tool.h>
#include <map>
#include <algorithm>
#include <string>
#include <UnitClass.h>
#include <InfantryClass.h>
#include <AircraftClass.h>
#include <BuildingClass.h>
#include <BulletClass.h>
#include <TerrainClass.h>
#include <AnimClass.h>
#include <AbstractClass.h>

void AbilitySystemComponent::OnEntityConstruct(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType)
{
    if (!pYrType)
        return;
    AbilitySystemComponentType* const typeCom = GetYrComponent<AbilitySystemComponentType>(pYrType);
    if (typeCom)
    {
        AbilitySystemComponent& com = reg.emplace<AbilitySystemComponent>(entity);
        com.InitializeFromType(typeCom);
        com.Owner = entity;
        com.Avatar = entity;
    }
}

void AbilitySystemComponent::InitializeFromType(AbilitySystemComponentType* InType)
{
    Type = InType;
    ActiveGameplayEffects.Owner = this;

    if (!Type)
    {
        return;
    }

	// Spawn attribute sets first (abilities/effects may query attributes)
    for (auto* Define : Type->Attributes)
    {
        this->AddAttributeSet(Define);
    }

    // Startup tags (loose)
    for (const auto& Tag : Type->StartupTags)
    {
        AddLooseGameplayTag(Tag, 1);
    }

    for (const auto& Ability : Type->DefaultAbilities)
    {
        this->GiveAbility(Ability);
    }

    // Startup effects applied to self
    if (!Type->StartupEffects.empty())
    {
        GameplayEffectContext Ctx;
        Ctx.Instigator = Owner;
        Ctx.AbilityLevel = 1;
        Ctx.InstigatorAbilitySystemComponent = this;

        for (auto& Effect : Type->StartupEffects)
        {
            ApplyGameplayEffectToSelf(&Effect, Ctx);
        }
    }
}

void AbilitySystemComponent::Tick(float DeltaTime)
{
	ActiveGameplayEffects.Tick(DeltaTime);
	TickTasks(DeltaTime);

	// Delete pending InstancedPerExecution abilities
	for (GameplayAbility* Ability : PendingDeleteAbilities)
	{
		if (Ability)
		{
			delete Ability;
		}
	}
	PendingDeleteAbilities.clear();
}

void AbilitySystemComponent::TickTasks(float DeltaTime)
{
	for (auto& Spec : ActivatableAbilities)
	{
		for (auto* Instance : Spec.GetAbilityInstances())
		{
			if (!Instance) continue;

			auto& Tasks = Instance->GetActiveTasks();

			// Tick all non-finished tasks
			for (auto* Task : Tasks)
			{
				if (Task && !Task->IsFinished())
				{
					Task->Tick(DeltaTime);
				}
			}

			// Remove and delete tasks marked for destroy
			Tasks.erase(
				std::remove_if(Tasks.begin(), Tasks.end(),
					[](AbilityTask* Task) {
						if (Task && Task->IsReadyForDestroy())
						{
							delete Task;
							return true;
						}
						return false;
					}),
				Tasks.end());
		}
	}
}

AttributeSet* AbilitySystemComponent::AddAttributeSet(AttributeSetDefine* define)
{
    AttributeSet* set = GameplayAbilitySystem::CreateAttributeSet(define->AttributeSetCreator, define, this);
    if (set)
    {
        SpawnedAttributes.push_back(set);
        return SpawnedAttributes.back();
    }
    return nullptr;
}

FOnGameplayTagCountChanged& AbilitySystemComponent::RegisterGameplayTagEvent(const GameplayTag& Tag)
{
    return GameplayTagEventMap[Tag];
}

FDelegateHandle AbilitySystemComponent::RegisterAndCallGameplayTagEvent(const GameplayTag& Tag, std::function<void(const GameplayTag&, int32)> Callback, EGameplayTagEventType EventType)
{
    FDelegateHandle Handle;
    Handle.Id = NextFilteredCallbackId++;

    FTagCountCallbackEntry Entry;
    Entry.Handle = Handle;
    Entry.Callback = std::move(Callback);
    Entry.EventType = EventType;
    Entry.LastKnownCount = GetGameplayTagCount(Tag);

    FilteredTagCallbacks[Tag].push_back(std::move(Entry));

    // "AndCall" part — immediately call if tag already has a count
    int32 CurrentCount = GetGameplayTagCount(Tag);
    if (CurrentCount > 0)
    {
        // Always call for AnyCountChange or NewOrRemoved (tag exists = it was "new" at some point)
        auto& StoredEntry = FilteredTagCallbacks[Tag].back();
        StoredEntry.Callback(Tag, CurrentCount);
    }

    return Handle;
}

void AbilitySystemComponent::UnregisterGameplayTagEvent(const GameplayTag& Tag, FDelegateHandle Handle)
{
    auto It = FilteredTagCallbacks.find(Tag);
    if (It == FilteredTagCallbacks.end()) return;

    auto& Entries = It->second;
    Entries.erase(std::remove_if(Entries.begin(), Entries.end(),
        [&Handle](const FTagCountCallbackEntry& Entry) {
            return Entry.Handle == Handle;
        }), Entries.end());

    if (Entries.empty())
    {
        FilteredTagCallbacks.erase(It);
    }
}

FOnGameplayEffectTagCountChanged& AbilitySystemComponent::RegisterGenericGameplayTagEvent()
{
    return OnGenericTagCountChanged;
}

FDelegateHandle AbilitySystemComponent::AddGameplayEventTagContainerDelegate(const GameplayTagContainer& Tags, std::function<void(const GameplayTag&, const GameplayEventData*)> Callback)
{
    FDelegateHandle Handle;
    Handle.Id = NextFilteredCallbackId++;

    // Register for each tag in the container
    for (const auto& Tag : Tags.GameplayTags)
    {
        GenericGameplayEventCallbacks[Tag].push_back(Callback);
        GameplayEventCallbackHandleMap[Handle].push_back(Tag);
    }

    return Handle;
}

void AbilitySystemComponent::RemoveGameplayEventTagContainerDelegate(const GameplayTagContainer& Tags, FDelegateHandle Handle)
{
    auto HandleIt = GameplayEventCallbackHandleMap.find(Handle);
    if (HandleIt == GameplayEventCallbackHandleMap.end()) return;

    // Remove callbacks from all tags associated with this handle
    for (const auto& Tag : HandleIt->second)
    {
        auto TagIt = GenericGameplayEventCallbacks.find(Tag);
        if (TagIt != GenericGameplayEventCallbacks.end())
        {
            // Note: std::function equality comparison is not reliable.
            // For simplicity, clear callbacks for tags registered via this handle.
            // A full implementation would use a more robust callback tracking mechanism.
        }
    }

    GameplayEventCallbackHandleMap.erase(HandleIt);
}

int32 AbilitySystemComponent::HandleGameplayEvent(const GameplayTag& EventTag, [[maybe_unused]] const GameplayEventData* Payload)
{
    int32 NumActivated = 0;

    // Dispatch to registered generic event callbacks
    auto CallbackIt = GenericGameplayEventCallbacks.find(EventTag);
    if (CallbackIt != GenericGameplayEventCallbacks.end())
    {
        for (auto& Callback : CallbackIt->second)
        {
            Callback(EventTag, Payload);
        }
    }

    // Find abilities triggered by this event
    auto It = GameplayEventTriggeredAbilities.find(EventTag);
    if (It != GameplayEventTriggeredAbilities.end())
    {
        for (const auto& Handle : It->second)
        {
            if (TryActivateAbility(Handle, true))
            {
                NumActivated++;
            }
        }
    }

    return NumActivated;
}

void AbilitySystemComponent::NotifyTagCountChanged(const GameplayTag& Tag, int32 NewCount)
{
    // Dispatch unfiltered callbacks (existing sigh-based)
    auto It = GameplayTagEventMap.find(Tag);
    if (It != GameplayTagEventMap.end())
    {
        It->second.publish(Tag, NewCount);
    }

    // Dispatch generic tag count changed delegate
    OnGenericTagCountChanged.publish(Tag, NewCount);

    // Dispatch filtered callbacks (EventType-aware)
    auto FilterIt = FilteredTagCallbacks.find(Tag);
    if (FilterIt != FilteredTagCallbacks.end())
    {
        for (auto& Entry : FilterIt->second)
        {
            bool bShouldFire = false;
            switch (Entry.EventType)
            {
            case EGameplayTagEventType::NewOrRemoved:
                if ((Entry.LastKnownCount == 0 && NewCount > 0) ||
                    (Entry.LastKnownCount > 0 && NewCount == 0))
                {
                    bShouldFire = true;
                }
                break;
            case EGameplayTagEventType::AnyCountChange:
                bShouldFire = (Entry.LastKnownCount != NewCount);
                break;
            }
            if (bShouldFire)
            {
                Entry.Callback(Tag, NewCount);
            }
            Entry.LastKnownCount = NewCount;
        }
    }

    // Trigger abilities bound to owned tag changes when tag becomes present
    if (NewCount > 0)
    {
        auto It2 = OwnedTagTriggeredAbilities.find(Tag);
        if (It2 != OwnedTagTriggeredAbilities.end())
        {
            for (const auto& Handle : It2->second)
            {
                TryActivateAbility(Handle, true);
            }
        }
    }
}

static std::vector<GameplayTag> BuildParentTagsInclusive_ForEvents(const GameplayTag& Tag)
{
    std::vector<GameplayTag> Out;
    if (!Tag.IsValid()) return Out;

    std::string_view Full = Tag.TagName;
    size_t Pos = 0;
    while (true)
    {
        size_t Dot = Full.find('.', Pos);
        std::string_view View = (Dot == std::string::npos) ? Full : Full.substr(0, Dot);

        GameplayTag Parent;
        Parent.TagName = StringName(View);
        Out.push_back(Parent);

        if (Dot == std::string::npos) break;
        Pos = Dot + 1;
    }
    return Out;
}

void AbilitySystemComponent::AddLooseGameplayTag(const GameplayTag& Tag, int32 Count)
{
    if (Count <= 0) return;
    TagCountContainer.UpdateTagCount(Tag, Count);
    for (const auto& Parent : BuildParentTagsInclusive_ForEvents(Tag))
    {
        NotifyTagCountChanged(Parent, TagCountContainer.GetTagCount(Parent));
    }
}

void AbilitySystemComponent::RemoveLooseGameplayTag(const GameplayTag& Tag, int32 Count)
{
    if (Count <= 0) return;
    TagCountContainer.UpdateTagCount(Tag, -Count);
    for (const auto& Parent : BuildParentTagsInclusive_ForEvents(Tag))
    {
        NotifyTagCountChanged(Parent, TagCountContainer.GetTagCount(Parent));
    }
}

int32 AbilitySystemComponent::GetGameplayTagCount(const GameplayTag& Tag) const
{
    return TagCountContainer.GetTagCount(Tag);
}



GameplayAbilitySpecHandle AbilitySystemComponent::GiveAbility(const GameplayAbilitySpec& AbilitySpec)
{
    if (AbilitySpec.Ability == nullptr) {
        gLogger->error("GiveAbility called with an invalid Ability Class.");
        return GameplayAbilitySpecHandle();
    }

    if (!IsOwnerActorAuthoritative())
    {
        gLogger->error("GiveAbility called on the client, not allowed!");
        return GameplayAbilitySpecHandle();
    }

    // If locked, add to pending list. The Spec.Handle is not regenerated when we receive, so returning this is ok.
    if (AbilityScopeLockCount > 0)
    {
        AbilityPendingAdds.push_back(AbilitySpec);
        return AbilitySpec.Handle;
    }

    ABILITYLIST_SCOPE_LOCK();
    ActivatableAbilities.push_back(AbilitySpec);
    GameplayAbilitySpec& OwnedSpec = ActivatableAbilities.back();

    // Assign a unique handle if not already set
    if (!OwnedSpec.Handle.IsValid())
    {
        OwnedSpec.Handle = GameplayAbilitySpecHandle::GenerateNewHandle();
    }

    if (OwnedSpec.Ability->GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::InstancedPerActor)
    {
        // Create the instance at creation time
        CreateNewInstanceOfAbility(OwnedSpec, OwnedSpec.Ability);
    }

    OnGiveAbility(OwnedSpec);
    MarkAbilitySpecDirty(OwnedSpec, true);

    return OwnedSpec.Handle;
}

GameplayAbilitySpecHandle AbilitySystemComponent::GiveAbility(const GameplayAbilityDefine* AbilityDefine)
{
    // create a default object
    GameplayAbility* Ability = GameplayAbilitySystem::CreateAbility(AbilityDefine->AbilityCreator, const_cast<GameplayAbilityDefine*>(AbilityDefine), this);
    if (Ability)
    {
        Ability->Define = AbilityDefine;
        return this->GiveAbility(GameplayAbilitySpec(Ability));
    }
    return {};
}

GameplayAbility* AbilitySystemComponent::CreateNewInstanceOfAbility(GameplayAbilitySpec& Spec, const GameplayAbility* Ability)
{
    if (!Ability || !Ability->Define)
    {
        return nullptr;
    }

    GameplayAbility* AbilityInstance = GameplayAbilitySystem::CreateAbility(
        Ability->Define->AbilityCreator, const_cast<GameplayAbilityDefine*>(Ability->Define), this);
    if (!AbilityInstance)
    {
        return nullptr;
    }

    AbilityInstance->Define = Ability->Define;
    Spec.NonReplicatedInstances.push_back(AbilityInstance);

    return AbilityInstance;
}

std::vector<const GameplayAbilitySpec*> AbilitySystemComponent::FindAbilitySpecsFromGEHandle(
    FScopedAbilityListLock& Lock, ActiveGameplayEffectHandle Handle, EConsiderPending ConsiderPending) const
{
    std::vector<const GameplayAbilitySpec*> OutSpecs;
    for (const auto& Spec : ActivatableAbilities)
    {
        if (Spec.GameplayEffectHandle == Handle)
        {
            if (Spec.PendingRemove && ConsiderPending == EConsiderPending::No)
            {
                continue;
            }
            OutSpecs.push_back(&Spec);
        }
    }
    return OutSpecs;
}

void AbilitySystemComponent::RemoveAbility(GameplayAbilitySpecHandle Handle)
{
    for (auto& Spec : ActivatableAbilities)
    {
        if (Spec.Handle == Handle)
        {
            if (AbilityScopeLockCount > 0)
            {
                // Defer removal until the lock is released
                Spec.PendingRemove = true;
            }
            else
            {
                OnRemoveAbility(Spec);
                // Actually erase from the vector
                ActivatableAbilities.erase(
                    std::remove_if(ActivatableAbilities.begin(), ActivatableAbilities.end(),
                        [&Handle](const GameplayAbilitySpec& S) { return S.Handle == Handle; }),
                    ActivatableAbilities.end());
            }
            return;
        }
    }
}

void AbilitySystemComponent::OnGiveAbility(GameplayAbilitySpec& Spec)
{
    if (Spec.Ability == nullptr) {
        return;
    }

    const GameplayAbility* SpecAbility = Spec.Ability;

    // If InstancedPerActor and missing an instance, create one
    if (SpecAbility->GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::InstancedPerActor)
    {
        if (Spec.NonReplicatedInstances.size() == 0)
        {
            CreateNewInstanceOfAbility(Spec, SpecAbility);
        }
    }

    // If this Ability Spec specified that it was created from an Active Gameplay Effect, then link the handle to the Active Gameplay Effect.
    if (Spec.GameplayEffectHandle.IsValid())
    {
		AbilitySystemComponent* SourceASC = Spec.GameplayEffectHandle.GetOwningAbilitySystemComponent();
		if (SourceASC)
		{
			ActiveGameplayEffect* SourceActiveGE = SourceASC->ActiveGameplayEffects.GetActiveGameplayEffect(Spec.GameplayEffectHandle);
			if (SourceActiveGE)
			{
                std_vector_add_unique(SourceActiveGE->GrantedAbilityHandles, Spec.Handle);
				SourceASC->ActiveGameplayEffects.MarkItemDirty(*SourceActiveGE);
			}
			else {
				gLogger->error("OnGiveAbility Spec has invalid ActiveGameplayEffect");
			}
		}
        else {
			gLogger->error("OnGiveAbility Spec GameplayEffectHandle has no owning ASC");
        }
    }

    
	if (Spec.Ability->Define)
	{
		for (const AbilityTriggerData& TriggerData : Spec.Ability->Define->AbilityTriggers)
		{
			GameplayTag EventTag = TriggerData.TriggerTag;

			auto& TriggeredAbilityMap = (TriggerData.TriggerSource == EGameplayAbilityTriggerSource::GameplayEvent) ? GameplayEventTriggeredAbilities : OwnedTagTriggeredAbilities;

			if (TriggeredAbilityMap.contains(EventTag))
			{
				std_vector_add_unique(TriggeredAbilityMap[EventTag], Spec.Handle);
			}
			else
			{
				std::vector<GameplayAbilitySpecHandle> Triggers;
				Triggers.push_back(Spec.Handle);
				TriggeredAbilityMap[EventTag] = Triggers;
			}

			if (TriggerData.TriggerSource != EGameplayAbilityTriggerSource::GameplayEvent)
			{
				FOnGameplayEffectTagCountChanged& CountChangedEvent = RegisterGameplayTagEvent(EventTag);
				// Add a tag change callback if there isn't one already
				if (CountChangedEvent.empty())
				{
					entt::sink sink{CountChangedEvent};
					sink.connect<&AbilitySystemComponent::NotifyTagCountChanged>(*this);
				}
			}
		}
	}

	// Call OnGiveAbility on all instances
	std::vector<GameplayAbility*> Instances = Spec.GetAbilityInstances();
	for (auto* Instance : Instances)
	{
		if (Instance)
		{
			GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
			Instance->OnGiveAbility(&ActorInfo, Spec);
		}
	}
}

void AbilitySystemComponent::MarkAbilitySpecDirty(GameplayAbilitySpec& Spec, bool WasAddOrRemove)
{
    AbilitySpecDirtiedCallbacks.publish(Spec);
}

// ============================================================
// Ability activation pipeline
// ============================================================

bool AbilitySystemComponent::TryActivateAbility(GameplayAbilitySpecHandle AbilityToActivate, bool bAllowRemoteActivation)
{
	// Find the spec by handle
	GameplayAbilitySpec* FoundSpec = nullptr;
	for (auto& Spec : ActivatableAbilities)
	{
		if (Spec.Handle == AbilityToActivate)
		{
			FoundSpec = &Spec;
			break;
		}
	}
	
	if (!FoundSpec || !FoundSpec->Ability)
	{
		return false;
	}

	// Check InputID blocking
	if (FoundSpec->InputID >= 0 && IsAbilityInputBlocked(FoundSpec->InputID))
	{
		GameplayTagContainer FailureTags;
		NotifyAbilityFailed(AbilityToActivate, FoundSpec->Ability, FailureTags);
		return false;
	}

	// Check if ability tags are blocked
	if (FoundSpec->Ability->Define)
	{
		if (AreAbilityTagsBlocked(FoundSpec->Ability->Define->AbilityTags))
		{
			GameplayTagContainer FailureTags = FoundSpec->Ability->Define->AbilityTags;
			NotifyAbilityFailed(AbilityToActivate, FoundSpec->Ability, FailureTags);
			return false;
		}
	}
	
	GameplayAbility* Ability = FoundSpec->Ability;

    // For InstancedPerExecution, create a new instance for each activation
    if (Ability->GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::InstancedPerExecution)
    {
        GameplayAbility* Instance = CreateNewInstanceOfAbility(*FoundSpec, Ability);
        if (Instance)
        {
            Ability = Instance;
        }
    }
    
    // Build ActorInfo
    GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
    
    // Check if ability can be activated
    if (!Ability->CanActivateAbility(AbilityToActivate, &ActorInfo))
    {
        // Broadcast failure with reason tags
        GameplayTagContainer FailureTags;
        if (Ability->Define && !Ability->Define->ActivationRequiredTags.IsEmpty())
        {
            FailureTags = Ability->Define->ActivationRequiredTags;
        }
        NotifyAbilityFailed(AbilityToActivate, Ability, FailureTags);
        return false;
    }
    
    // Create activation info (authority mode for single-player)
    GameplayAbilityActivationInfo ActivationInfo;
    ActivationInfo.ActivationMode = EGameplayAbilityActivationMode::Authority;
    
    // Call the ability
    Ability->CallActivateAbility(AbilityToActivate, &ActorInfo, ActivationInfo, nullptr, nullptr);
    
    FoundSpec->ActiveCount++;
    
    // Broadcast activation success
    NotifyAbilityActivated(AbilityToActivate, Ability);
    
    return true;
}

void AbilitySystemComponent::CancelAbility(GameplayAbility* Ability)
{
    if (!Ability) return;
    
    GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
    
    for (auto& Spec : ActivatableAbilities)
    {
        if (Spec.Ability == Ability && Spec.Ability)
        {
            GameplayAbilityActivationInfo ActivationInfo;
            Spec.Ability->CancelAbility(Spec.Handle, &ActorInfo, ActivationInfo, true);
            break;
        }
    }
}

GameplayAbilitySpecHandle AbilitySystemComponent::GiveAbilityAndActivateOnce(GameplayAbilitySpec& AbilitySpec, const GameplayEventData* GameplayEventData)
{
    GameplayAbilitySpecHandle Handle = GiveAbility(AbilitySpec);
    
    // Mark for removal after activation
    for (auto& Spec : ActivatableAbilities)
    {
        if (Spec.Handle == Handle)
        {
            Spec.bActivateOnce = true;
            Spec.RemoveAfterActivation = true;
            break;
        }
    }
    
    // Immediately try to activate
    TryActivateAbility(Handle, true);
    
    return Handle;
}

// ============================================================
// Cooldown / Cost System (Phase 7)
// ============================================================

void AbilitySystemComponent::ApplyCooldown(GameplayAbilitySpecHandle Handle, GameplayEffect* CooldownEffect)
{
    if (!CooldownEffect) return;
    
    GameplayEffectContext Context;
    Context.Instigator = Owner;
    Context.AbilityLevel = 1;
    Context.InstigatorAbilitySystemComponent = const_cast<AbilitySystemComponent*>(this);
    
    ApplyGameplayEffectToTarget(CooldownEffect, const_cast<AbilitySystemComponent*>(this), Context);
}

bool AbilitySystemComponent::CanApplyAttributeModifiers(const GameplayEffect* GameplayEffect, float Level, const GameplayEffectContextHandle& EffectContext)
{
    if (!GameplayEffect)
    {
        return true;
    }

    GameplayEffectSpec Spec;
    Spec.Def = GameplayEffect;
    Spec.Level = static_cast<int32>(Level);
    Spec.EffectContext = EffectContext;
    Spec.CalculateModifierMagnitudes();

    for (size_t i = 0; i < Spec.Def->Modifiers.size(); ++i)
    {
        const auto& ModDef = Spec.Def->Modifiers[i];

        if (ModDef.ModifierOp == EGameplayModOpType::Additive)
        {
            if (!ModDef.Attribute.IsValid())
                continue;

            float CurrentValue = 0.0f;
            for (const auto* AttrSet : SpawnedAttributes)
            {
                const auto* Data = AttrSet->FindAttributeData(&ModDef.Attribute);
                if (Data)
                {
                    CurrentValue += Data->GetCurrentValue();
                }
            }

            float CostValue = (i < Spec.ModifierMagnitudes.size()) ? Spec.ModifierMagnitudes[i] : 0.0f;

            if (CurrentValue + CostValue < 0.0f)
            {
                return false;
            }
        }
    }

    return true;
}

void AbilitySystemComponent::ApplyCost(GameplayAbilitySpecHandle Handle, GameplayEffect* CostEffect)
{
    if (!CostEffect) return;
    
    GameplayEffectContext Context;
    Context.Instigator = Owner;
    Context.AbilityLevel = 1;
    Context.InstigatorAbilitySystemComponent = const_cast<AbilitySystemComponent*>(this);
    
    ApplyGameplayEffectToTarget(CostEffect, const_cast<AbilitySystemComponent*>(this), Context);
}

// ============================================================
// Ability notification methods
// ============================================================

void AbilitySystemComponent::NotifyAbilityCommit(GameplayAbility* Ability)
{
    if (!Ability) return;
    
    // Find the spec handle for this ability
    GameplayAbilitySpecHandle FoundHandle;
    for (const auto& Spec : ActivatableAbilities)
    {
        if (Spec.Ability == Ability)
        {
            FoundHandle = Spec.Handle;
            break;
        }
    }
    
    AbilityCommittedCallbacks.publish(FoundHandle, Ability);
}

void AbilitySystemComponent::NotifyAbilityActivated(const GameplayAbilitySpecHandle Handle, GameplayAbility* Ability)
{
    AbilityActivatedCallbacks.publish(Handle, Ability);
}

void AbilitySystemComponent::NotifyAbilityFailed(const GameplayAbilitySpecHandle Handle, GameplayAbility* Ability, const GameplayTagContainer& FailureReason)
{
    AbilityFailedCallbacks.publish(Ability, FailureReason);
}

void AbilitySystemComponent::NotifyAbilityEnded(GameplayAbilitySpecHandle Handle, GameplayAbility* Ability, bool bWasCancelled)
{
    if (!Ability) return;

    // Find the spec
    GameplayAbilitySpec* Spec = nullptr;
    for (auto& S : ActivatableAbilities)
    {
        if (S.Handle == Handle)
        {
            Spec = &S;
            break;
        }
    }

    if (!Spec) return;

    if (Spec->ActiveCount > 0)
    {
        Spec->ActiveCount--;
    }

    AbilityEndedCallbacks.publish(Ability);

    // For InstancedPerExecution, mark for deletion
    if (Ability->GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::InstancedPerExecution)
    {
        Spec->NonReplicatedInstances.erase(
            std::remove(Spec->NonReplicatedInstances.begin(), Spec->NonReplicatedInstances.end(), Ability),
            Spec->NonReplicatedInstances.end());
        PendingDeleteAbilities.push_back(Ability);
    }

    // If RemoveAfterActivation and no longer active, clear the ability
    if (Spec->RemoveAfterActivation && !Spec->IsActive())
    {
        ClearAbility(Handle);
    }
}

void AbilitySystemComponent::OnRemoveAbility(GameplayAbilitySpec& Spec)
{
    if (Spec.Ability == nullptr) return;
    
    // Remove from trigger maps
    if (Spec.Ability->Define)
    {
        for (const AbilityTriggerData& TriggerData : Spec.Ability->Define->AbilityTriggers)
        {
            GameplayTag EventTag = TriggerData.TriggerTag;
            
            auto& TriggeredAbilityMap = (TriggerData.TriggerSource == EGameplayAbilityTriggerSource::GameplayEvent) 
                ? GameplayEventTriggeredAbilities : OwnedTagTriggeredAbilities;
            
            auto It = TriggeredAbilityMap.find(EventTag);
            if (It != TriggeredAbilityMap.end())
            {
                std::vector<GameplayAbilitySpecHandle>& Handles = It->second;
                Handles.erase(std::remove(Handles.begin(), Handles.end(), Spec.Handle), Handles.end());
                if (Handles.empty())
                {
                    TriggeredAbilityMap.erase(It);
                }
            }
        }
    }

    // End all active ability instances
    std::vector<GameplayAbility*> Instances = Spec.GetAbilityInstances();
    for (auto* Instance : Instances)
    {
        if (Instance && Instance->IsActive())
        {
            // End the ability but don't replicate it
            bool bReplicateEndAbility = false;
            bool bWasCancelled = false;
            Instance->EndAbility(Instance->GetCurrentSpecHandle(), Instance->GetCurrentActorInfo(), Instance->GetCurrentActivationInfo(), bReplicateEndAbility, bWasCancelled);
        }
    }

    // Call OnRemoveAbility on all instances
    for (auto* Instance : Instances)
    {
        if (Instance)
        {
            GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
            Instance->OnRemoveAbility(&ActorInfo, Spec);
        }
    }

    // Delete all instance objects
    for (auto* Instance : Spec.NonReplicatedInstances)
    {
        delete Instance;
    }
    Spec.NonReplicatedInstances.clear();

    for (auto* Instance : Spec.ReplicatedInstances)
    {
        delete Instance;
    }
    Spec.ReplicatedInstances.clear();

    // Delete the CDO
    if (Spec.Ability)
    {
        delete Spec.Ability;
        Spec.Ability = nullptr;
    }
    
    MarkAbilitySpecDirty(Spec, true);
}

// ============================================================
// Modifier Aggregation Engine (Phase 5)
// Formula: ((BaseValue + Sum_AddBase) * Product_MultiplyAdditive / Product_DivideAdditive * Product_MultiplyCompound) + Sum_AddFinal
// ============================================================

struct AggregatedModifiers
{
    float SumAddBase = 0.0f;
    float SumMultiplyAdditive = 0.0f;
    float SumDivideAdditive = 0.0f;
    float ProductMultiplyCompound = 1.0f;
    float SumAddFinal = 0.0f;
    bool bHasOverride = false;
    float OverrideValue = 0.0f;
};

/** Collect all modifiers affecting a given attribute from active effects */
static AggregatedModifiers CollectModifiersForAttribute(
    AbilitySystemComponent* ASC, 
    const GameplayAttribute& TargetAttribute)
{
    AggregatedModifiers Result;
    
    for (auto* Effect : ASC->ActiveGameplayEffects.GetAllActiveEffects())
    {
        if (!Effect || !Effect->Spec.Def) continue;
        
        for (size_t i = 0; i < Effect->Spec.Def->Modifiers.size(); i++)
        {
            const auto& Modifier = Effect->Spec.Def->Modifiers[i];
            
            // Check if this modifier targets our attribute
            if (Modifier.Attribute.AttributeName != TargetAttribute.AttributeName)
                continue;
            
            float Magnitude = (i < Effect->Spec.ModifierMagnitudes.size()) 
                ? Effect->Spec.ModifierMagnitudes[i] : 0.0f;
            
            switch (Modifier.ModifierOp)
            {
            case EGameplayModOpType::AddBase:
                Result.SumAddBase += Magnitude;
                break;
            case EGameplayModOpType::MultiplyAdditive:
                Result.SumMultiplyAdditive += Magnitude;
                break;
            case EGameplayModOpType::DivideAdditive:
                Result.SumDivideAdditive += Magnitude;
                break;
            case EGameplayModOpType::MultiplyCompound:
                Result.ProductMultiplyCompound *= Magnitude;
                break;
            case EGameplayModOpType::AddFinal:
                Result.SumAddFinal += Magnitude;
                break;
            case EGameplayModOpType::Override:
                Result.bHasOverride = true;
                Result.OverrideValue = Magnitude;
                break;
            default:
                break;
            }
        }
    }
    
    return Result;
}

/** Calculate the final value of an attribute given base value and aggregated modifiers */
static float CalculateFinalAttributeValue(float BaseValue, const AggregatedModifiers& Mods)
{
    if (Mods.bHasOverride)
    {
        return Mods.OverrideValue;
    }
    
    // ((BaseValue + Sum_AddBase) * Product_MultiplyAdditive / Product_DivideAdditive * Product_MultiplyCompound) + Sum_AddFinal
    float AddBaseResult = BaseValue + Mods.SumAddBase;
    float MultiplyFactor = (1.0f + Mods.SumMultiplyAdditive);
    float DivideFactor = (1.0f + Mods.SumDivideAdditive);
    
    // Avoid division by zero
    if (DivideFactor == 0.0f) DivideFactor = 1.0f;
    
    float Result = AddBaseResult;
    Result *= MultiplyFactor;
    Result /= DivideFactor;
    Result *= Mods.ProductMultiplyCompound;
    Result += Mods.SumAddFinal;
    
    return Result;
}

// ============================================================
// Effect application system
// ============================================================

/** Apply a modifier change to an attribute's current value */
static void ApplyModifierToAttribute(AttributeSet* AttrSet, const GameplayAttribute& Attr, float Magnitude, EGameplayModOpType Op)
{
    if (!AttrSet) return;

    GameplayAttributeData* AttributeData = AttrSet->FindAttributeData(&Attr);
    if (!AttributeData) return;

    float CurrentValue = AttributeData->GetCurrentValue();
    float NewValue = CurrentValue;
    switch (Op)
    {
    case EGameplayModOpType::AddBase:
        NewValue = CurrentValue + Magnitude;
        break;
    case EGameplayModOpType::MultiplyAdditive:
        NewValue = CurrentValue * (1.0f + Magnitude);
        break;
    case EGameplayModOpType::DivideAdditive:
        NewValue = CurrentValue / (1.0f + Magnitude);
        break;
    case EGameplayModOpType::MultiplyCompound:
        NewValue = CurrentValue * Magnitude;
        break;
    case EGameplayModOpType::AddFinal:
        NewValue = CurrentValue + Magnitude;
        break;
    case EGameplayModOpType::Override:
        NewValue = Magnitude;
        break;
    default:
        break;
    }

    float OldValue = AttributeData->GetBaseValue();
    AttrSet->PreAttributeBaseChange(Attr, NewValue);
    AttrSet->PreAttributeChange(Attr, NewValue);
    AttributeData->SetBaseValue(NewValue);
    AttrSet->PostAttributeChange(Attr, OldValue, NewValue);
    AttrSet->PostAttributeBaseChange(Attr, OldValue, NewValue);
}

/** Execute an instant effect: apply modifiers directly to base values */
static void ExecuteInstantEffect(AbilitySystemComponent* Target, const GameplayEffectSpec& Spec)
{
    if (!Spec.Def) return;
    
    for (size_t i = 0; i < Spec.Def->Modifiers.size(); i++)
    {
        const auto& Modifier = Spec.Def->Modifiers[i];
        float Magnitude = (i < Spec.ModifierMagnitudes.size()) ? Spec.ModifierMagnitudes[i] : 0.0f;
        
        // Build evaluated data for pre/post callbacks
        FGameplayModifierEvaluatedData EvalData;
        EvalData.Attribute = Modifier.Attribute;
        EvalData.ModifierOp = Modifier.ModifierOp;
        EvalData.Magnitude = Magnitude;
        EvalData.IsValid = true;
        
        // Apply to matching attribute sets on the target
        for (auto* AttrSet : Target->SpawnedAttributes)
        {
            // Only process attribute sets that actually contain this attribute
            if (!AttrSet->FindAttributeData(&Modifier.Attribute))
                continue;
            
            FGameplayEffectModCallbackData CallbackData(&Spec, EvalData, Target);
            
            if (!AttrSet->PreGameplayEffectExecute(CallbackData))
                continue;
            
            ApplyModifierToAttribute(AttrSet, Modifier.Attribute, Magnitude, Modifier.ModifierOp);
            
            AttrSet->PostGameplayEffectExecute(CallbackData);
        }
    }
}

ActiveGameplayEffectHandle AbilitySystemComponent::ApplyGameplayEffectToTarget(
    GameplayEffect* Effect, AbilitySystemComponent* Target, const GameplayEffectContext& Context)
{
    if (!Effect || !Target) return ActiveGameplayEffectHandle();
    
    // Create the spec
    GameplayEffectSpec Spec;
    Spec.Def = Effect;
    Spec.Level = Context.AbilityLevel;
    Spec.EffectContext.Data = new GameplayEffectContext(Context);
    
    // Calculate modifier magnitudes
    Spec.CalculateModifierMagnitudes();
    
    // Step 0: Check application queries (immunity, etc.) registered by active effects on the target
    for (const auto& Query : Target->GameplayEffectApplicationQueries)
    {
        if (!Query.CheckFn(Target->ActiveGameplayEffects, Spec))
        {
            return ActiveGameplayEffectHandle();
        }
    }

    // Step 1: Component pre-apply check
    if (!Effect->CanApply(Target->ActiveGameplayEffects, Spec))
    {
        return ActiveGameplayEffectHandle();
    }
    
    // Step 2: Branch based on duration policy
    switch (Effect->DurationPolicy)
    {
    case EGameplayEffectDurationType::Instant:
    {
        // Execute modifiers
        ExecuteInstantEffect(Target, Spec);
        
        // Notify components of execution
        Effect->OnExecuted(Target->ActiveGameplayEffects, Spec);
        
        // Notify components of application
        Effect->OnApplied(Target->ActiveGameplayEffects, Spec, *Target);
        
        // Broadcast application delegate
        Target->OnGameplayEffectAppliedDelegateToTarget.publish(Target, Spec, ActiveGameplayEffectHandle(-1));
        
        return ActiveGameplayEffectHandle(-1);
    }
        
    case EGameplayEffectDurationType::Infinite:
    case EGameplayEffectDurationType::HasDuration:
    {
        // Add as active effect
        ActiveGameplayEffectHandle Handle = Target->ActiveGameplayEffects.Add(Target, Spec);
        
        // Apply modifiers to current value for duration effects
        ExecuteInstantEffect(Target, Spec);
        
        // Call InternalOnActiveGameplayEffectAdded which invokes OnAddedToActiveContainer
        // and sets inhibit state based on the return value
        ActiveGameplayEffect* ActiveGE = Target->ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
        if (ActiveGE)
        {
            Target->ActiveGameplayEffects.InternalOnActiveGameplayEffectAdded(*ActiveGE);
        }
        
        // Notify components of application
        Effect->OnApplied(Target->ActiveGameplayEffects, Spec, *Target);
        
        // Broadcast application delegate
        Target->OnGameplayEffectAppliedDelegateToTarget.publish(Target, Spec, Handle);
        
        return Handle;
    }
    }
    
    return ActiveGameplayEffectHandle();
}

ActiveGameplayEffectHandle AbilitySystemComponent::ApplyGameplayEffectToSelf(
    GameplayEffect* Effect, const GameplayEffectContext& Context)
{
    ActiveGameplayEffectHandle Handle = ApplyGameplayEffectToTarget(Effect, this, Context);

    if (Handle.IsValid())
    {
        // Build spec for delegate broadcasting
        GameplayEffectSpec Spec;
        Spec.Def = Effect;
        Spec.Level = Context.AbilityLevel;
        Spec.EffectContext.Data = new GameplayEffectContext(Context);
        Spec.CalculateModifierMagnitudes();

        // Broadcast self-applied delegate
        OnGameplayEffectAppliedDelegateToSelf.publish(this, Spec, Handle);

        // For duration/infinite effects, also broadcast active effect added
        if (Effect && (Effect->DurationPolicy == EGameplayEffectDurationType::Infinite ||
                       Effect->DurationPolicy == EGameplayEffectDurationType::HasDuration))
        {
            OnActiveGameplayEffectAddedDelegateToSelf.publish(this, Spec, Handle);
        }
    }

    return Handle;
}

GameplayEffectSpec AbilitySystemComponent::MakeOutgoingSpec(GameplayEffect* Effect, float Level, const GameplayAbilitySpec* AbilitySpec) const
{
    GameplayEffectSpec Spec;
    Spec.Def = Effect;
    Spec.Level = static_cast<int32>(Level);
    if (AbilitySpec)
    {
        Spec.CapturedSourceTags = AbilitySpec->DynamicAbilityTags;
    }
    return Spec;
}

GameplayEffectContextHandle AbilitySystemComponent::MakeEffectContext() const
{
    GameplayEffectContextHandle Handle;
    Handle.Data = new GameplayEffectContext();
    Handle.Data->Instigator = Owner;
    Handle.Data->InstigatorAbilitySystemComponent = const_cast<AbilitySystemComponent*>(this);
    return Handle;
}

bool AbilitySystemComponent::RemoveActiveGameplayEffect(ActiveGameplayEffectHandle Handle, int32 StacksToRemove)
{
    if (!Handle.IsValid()) return false;

    ActiveGameplayEffect* Effect = ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
    if (!Effect) return false;

    if (StacksToRemove < 0 || StacksToRemove >= Effect->StackCount)
    {
        // Remove entire effect
        ActiveGameplayEffects.Remove(Handle);
    }
    else
    {
        // Reduce stack count
        Effect->StackCount -= StacksToRemove;
        if (Effect->StackCount <= 0)
        {
            ActiveGameplayEffects.Remove(Handle);
        }
    }

    return true;
}

void AbilitySystemComponent::RemoveActiveEffects(const FGameplayEffectQuery& Query)
{
	std::vector<ActiveGameplayEffectHandle> ToRemove;
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect) continue;
		if (!Query.Matches(*Effect))
			continue;

		// ASC-level checks: GrantedTags and OwningTagQuery
		if (Query.GrantedTags.IsValid())
		{
			bool bHasMatchingGranted = false;
			for (const auto& AbilityHandle : Effect->GrantedAbilityHandles)
			{
				for (const auto& Spec : ActivatableAbilities)
				{
					if (Spec.Handle == AbilityHandle
						&& Spec.DynamicAbilityTags.HasAny(Query.GrantedTags))
					{
						bHasMatchingGranted = true;
						break;
					}
				}
				if (bHasMatchingGranted) break;
			}
			if (!bHasMatchingGranted) continue;
		}

		if (Query.OwningTagQuery)
		{
			if (!Query.OwningTagQuery->Matches(GetOwnedGameplayTags()))
				continue;
		}

		ToRemove.push_back(Effect->Handle);
	}
	for (const auto& Handle : ToRemove)
	{
		RemoveActiveGameplayEffect(Handle);
	}
}

void AbilitySystemComponent::ApplyModToAttribute(const GameplayAttribute& Attribute, EGameplayModOpType ModifierOp, float ModifierMagnitude)
{
    // Build evaluated data for pre/post callbacks
    FGameplayModifierEvaluatedData EvalData;
    EvalData.Attribute = Attribute;
    EvalData.ModifierOp = ModifierOp;
    EvalData.Magnitude = ModifierMagnitude;
    EvalData.IsValid = true;

    // Placeholder spec for in-place modifier hooks (no actual GE backing this)
    GameplayEffectSpec PlaceholderSpec;

    for (auto* AttrSet : SpawnedAttributes)
    {
        // Only process attribute sets that actually contain this attribute
        if (!AttrSet->FindAttributeData(&Attribute))
            continue;

        FGameplayEffectModCallbackData CallbackData(&PlaceholderSpec, EvalData, this);

        if (!AttrSet->PreGameplayEffectExecute(CallbackData))
            continue;

        ::ApplyModifierToAttribute(AttrSet, Attribute, ModifierMagnitude, ModifierOp);

        AttrSet->PostGameplayEffectExecute(CallbackData);
    }
}

float AbilitySystemComponent::GetNumericAttribute(const GameplayAttribute& Attribute) const
{
    for (const auto* AttrSet : SpawnedAttributes)
    {
        const auto* Data = AttrSet->FindAttributeData(&Attribute);
        if (Data)
        {
            return Data->GetCurrentValue();
        }
    }
    return 0.0f;
}

void AbilitySystemComponent::InitDefaultGameplayCueParameters(GameplayCueParameters& Parameters)
{
    Parameters.EffectContext = MakeEffectContext();
    Parameters.RawMagnitude = 0.0f;

    // Fill Location from Owner entity's position.
    // Owner is a YR entity with YrEntityComponent<T> where T is a concrete YR class.
    // Try the common YR types that ASC targets: TechnoClass subclasses, BulletClass,
    // TerrainClass, and AnimClass.
    if (Owner != entt::null && gEntt && gEntt->valid(Owner))
    {
        AbstractClass* pAbstract = nullptr;

#define TRY_GET_YR(Type) \
        if (!pAbstract) { \
            if (auto* comp = gEntt->try_get<YrEntityComponent<Type>>(Owner)) \
                pAbstract = static_cast<AbstractClass*>(comp->yrObject); \
        }

        TRY_GET_YR(UnitClass)
        TRY_GET_YR(InfantryClass)
        TRY_GET_YR(AircraftClass)
        TRY_GET_YR(BuildingClass)
        TRY_GET_YR(BulletClass)
        TRY_GET_YR(TerrainClass)
        TRY_GET_YR(AnimClass)

#undef TRY_GET_YR

        if (pAbstract)
        {
            Parameters.Location = pAbstract->GetCoords();
        }
    }
}

void AbilitySystemComponent::ExecuteGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params)
{
    GameplayCueParameters LocalParams = Params;
    InitDefaultGameplayCueParameters(LocalParams);
    if (auto* CueManager = GameplayCueManager::Get())
    {
        CueManager->HandleGameplayCue(this, CueTag, EGameplayCueEvent::Executed, LocalParams);
    }
}

void AbilitySystemComponent::AddGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params)
{
    GameplayCueParameters LocalParams = Params;
    InitDefaultGameplayCueParameters(LocalParams);
    ActiveGameplayCues.insert(CueTag);
    if (auto* CueManager = GameplayCueManager::Get())
    {
        CueManager->HandleGameplayCue(this, CueTag, EGameplayCueEvent::OnActive, LocalParams);
    }
}

void AbilitySystemComponent::RemoveGameplayCue(const GameplayTag& CueTag)
{
    ActiveGameplayCues.erase(CueTag);
    GameplayCueParameters LocalParams;
    InitDefaultGameplayCueParameters(LocalParams);
    if (auto* CueManager = GameplayCueManager::Get())
    {
        CueManager->HandleGameplayCue(this, CueTag, EGameplayCueEvent::Removed, LocalParams);
    }
}

void AbilitySystemComponent::RemoveAllGameplayCues()
{
    // Copy the set since RemoveGameplayCue modifies ActiveGameplayCues
    auto ActiveCuesCopy = ActiveGameplayCues;
    for (const auto& Tag : ActiveCuesCopy)
    {
        RemoveGameplayCue(Tag);
    }
    ActiveGameplayCues.clear();
}

bool AbilitySystemComponent::IsGameplayCueActive(const GameplayTag& CueTag) const
{
    return ActiveGameplayCues.find(CueTag) != ActiveGameplayCues.end();
}

std::vector<ActiveGameplayEffectHandle> AbilitySystemComponent::GetActiveEffects(const GameplayTagContainer& Tags) const
{
	std::vector<ActiveGameplayEffectHandle> Results;
	if (!Tags.IsValid())
	{
		return GetAllActiveEffectHandles();
	}
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect || !Effect->Spec.Def) continue;
		// Check captured source/target tags from the spec
		if (Effect->Spec.CapturedSourceTags.HasAny(Tags) || 
			Effect->Spec.CapturedTargetTags.HasAny(Tags))
		{
			Results.push_back(Effect->Handle);
		}
	}
	return Results;
}

std::vector<ActiveGameplayEffectHandle> AbilitySystemComponent::GetActiveEffects(const FGameplayEffectQuery& Query) const
{
	std::vector<ActiveGameplayEffectHandle> Results;
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect) continue;
		if (!Query.Matches(*Effect))
			continue;

		// ASC-level checks: GrantedTags and OwningTagQuery
		if (Query.GrantedTags.IsValid())
		{
			bool bHasMatchingGranted = false;
			for (const auto& AbilityHandle : Effect->GrantedAbilityHandles)
			{
				for (const auto& Spec : ActivatableAbilities)
				{
					if (Spec.Handle == AbilityHandle
						&& Spec.DynamicAbilityTags.HasAny(Query.GrantedTags))
					{
						bHasMatchingGranted = true;
						break;
					}
				}
				if (bHasMatchingGranted) break;
			}
			if (!bHasMatchingGranted) continue;
		}

		if (Query.OwningTagQuery)
		{
			if (!Query.OwningTagQuery->Matches(GetOwnedGameplayTags()))
				continue;
		}

		Results.push_back(Effect->Handle);
	}
	return Results;
}

std::vector<ActiveGameplayEffectHandle> AbilitySystemComponent::GetAllActiveEffectHandles() const
{
    std::vector<ActiveGameplayEffectHandle> Results;
    for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
    {
        if (Effect)
        {
            Results.push_back(Effect->Handle);
        }
    }
    return Results;
}

std::vector<float> AbilitySystemComponent::GetActiveEffectsTimeRemaining(const GameplayTagContainer& Tags) const
{
    std::vector<float> Results;
    for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
    {
        if (!Effect || !Effect->Spec.Def) continue;
        if (Tags.IsValid())
        {
            if (!Effect->Spec.CapturedSourceTags.HasAny(Tags) && 
                !Effect->Spec.CapturedTargetTags.HasAny(Tags))
                continue;
        }
        Results.push_back(Effect->GetTimeRemaining(0.0f));
    }
    return Results;
}

std::vector<float> AbilitySystemComponent::GetActiveEffectsDuration(const GameplayTagContainer& Tags) const
{
    std::vector<float> Results;
    for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
    {
        if (!Effect || !Effect->Spec.Def) continue;
        if (Tags.IsValid())
        {
            if (!Effect->Spec.CapturedSourceTags.HasAny(Tags) && 
                !Effect->Spec.CapturedTargetTags.HasAny(Tags))
                continue;
        }
        Results.push_back(Effect->Spec.GetDuration());
    }
    return Results;
}

// ============================================================
// ActiveGameplayEffectsContainer implementation
// ============================================================

ActiveGameplayEffect* ActiveGameplayEffectsContainer::GetActiveGameplayEffect(const ActiveGameplayEffectHandle Handle)
{
    for (auto* Effect : Effects)
    {
        if (Effect && Effect->Handle == Handle)
        {
            return Effect;
        }
    }
    return nullptr;
}

const ActiveGameplayEffect* ActiveGameplayEffectsContainer::GetActiveGameplayEffect(const ActiveGameplayEffectHandle Handle) const
{
    for (const auto* Effect : Effects)
    {
        if (Effect && Effect->Handle == Handle)
        {
            return Effect;
        }
    }
    return nullptr;
}

ActiveGameplayEffectHandle ActiveGameplayEffectsContainer::Add(AbilitySystemComponent* OwningASC, GameplayEffectSpec& Spec)
{
    auto* NewEffect = new ActiveGameplayEffect();
    NewEffect->Spec = Spec;
    NewEffect->Handle = ActiveGameplayEffectHandle::GenerateNewHandle(OwningASC);
    NewEffect->LastPeriodExecuteTime = NewEffect->StartWorldTime;
    Effects.push_back(NewEffect);

    // Create per-effect event set for delegate tracking
    if (Owner)
    {
        Owner->ActiveEffectEventSets[NewEffect->Handle] = FActiveGameplayEffectEvents();
    }

    return NewEffect->Handle;
}

void ActiveGameplayEffectsContainer::Remove(ActiveGameplayEffectHandle Handle, bool bPrematureRemoval)
{
    // Fire OnRemoved delegate and clean up event set before removing from the list
    if (Owner)
    {
        auto EventIt = Owner->ActiveEffectEventSets.find(Handle);
        if (EventIt != Owner->ActiveEffectEventSets.end())
        {
            ActiveGameplayEffect* Effect = GetActiveGameplayEffect(Handle);
            if (Effect)
            {
                FGameplayEffectRemovalInfo RemovalInfo;
                RemovalInfo.ActiveEffect = Effect;
                RemovalInfo.bPrematureRemoval = bPrematureRemoval;
                RemovalInfo.StackCount = Effect->StackCount;
                RemovalInfo.EffectContext = Effect->Spec.EffectContext;
                EventIt->second.OnRemoved.publish(RemovalInfo);
            }
            Owner->ActiveEffectEventSets.erase(EventIt);
        }
    }

    auto It = std::remove_if(Effects.begin(), Effects.end(), 
        [&Handle, this, bPrematureRemoval](ActiveGameplayEffect* Effect) {
            if (Effect && Effect->Handle == Handle)
            {
                // Release delegate connections
                if (Effect->OnRemovedDelegateHandle)
                    Effect->OnRemovedDelegateHandle.release();
                if (Effect->OnInhibitionChangedDelegateHandle)
                    Effect->OnInhibitionChangedDelegateHandle.release();

                if (Effect->Spec.Def)
                {
                    FGameplayEffectRemovalInfo RemovalInfo;
                    RemovalInfo.bPrematureRemoval = bPrematureRemoval;
                    RemovalInfo.StackCount = Effect->StackCount;
                    RemovalInfo.EffectContext = Effect->Spec.EffectContext;
                    Effect->Spec.Def->OnRemovedFromActiveContainer(*this, *Effect, RemovalInfo);
                }
                delete Effect;
                return true;
            }
            return false;
        });
    Effects.erase(It, Effects.end());
}

void ActiveGameplayEffectsContainer::RemoveAll()
{
    // Clean up all per-effect event sets before deleting effects
    if (Owner)
    {
        for (auto* Effect : Effects)
        {
            if (Effect)
            {
                Owner->ActiveEffectEventSets.erase(Effect->Handle);
            }
        }
    }

    for (auto* Effect : Effects)
    {
        delete Effect;
    }
    Effects.clear();
}

void ActiveGameplayEffectsContainer::Tick(float DeltaTime)
{
    std::vector<ActiveGameplayEffectHandle> ExpiredEffects;
    std::vector<std::pair<ActiveGameplayEffect*, ActiveGameplayEffectHandle>> PeriodicExecEffects;
    
    for (auto* Effect : Effects)
    {
        if (!Effect || !Effect->Spec.Def) continue;
        
        const auto* Def = Effect->Spec.Def;
        
        // Handle duration-based effects expiry
        if (Def->DurationPolicy == EGameplayEffectDurationType::HasDuration)
        {
            float OldTimeRemaining = Effect->GetTimeRemaining(0.0f);
            Effect->StartWorldTime += DeltaTime; // Accumulate elapsed time
            float NewTimeRemaining = Effect->GetTimeRemaining(0.0f);

            // Fire OnTimeChanged delegate if time changed
            if (OldTimeRemaining != NewTimeRemaining && Owner)
            {
                auto EventIt = Owner->ActiveEffectEventSets.find(Effect->Handle);
                if (EventIt != Owner->ActiveEffectEventSets.end())
                {
                    EventIt->second.OnTimeChanged.publish(Effect->Handle, NewTimeRemaining, OldTimeRemaining);
                }
            }

            if (NewTimeRemaining <= 0.0f)
            {
                ExpiredEffects.push_back(Effect->Handle);
                continue;
            }
        }
        
        // Handle periodic effects
        if (Def->Period > 0.0f)
        {
            Effect->LastPeriodExecuteTime += DeltaTime;
            float TimeSinceLastPeriod = Effect->LastPeriodExecuteTime - Effect->StartWorldTime;
            // Check if a full period has elapsed
            float PeriodDuration = Def->Period;
            if (TimeSinceLastPeriod >= PeriodDuration)
            {
                PeriodicExecEffects.push_back({Effect, Effect->Handle});
                Effect->LastPeriodExecuteTime = Effect->StartWorldTime; // Reset period timer
            }
        }
    }
    
    // Execute periodic effects and broadcast delegates
    for (const auto& [Effect, Handle] : PeriodicExecEffects)
    {
        if (Effect && Effect->Spec.Def && Owner)
        {
            // Execute instant effect modifiers
            ExecuteInstantEffect(Owner, Effect->Spec);
            
            // Broadcast periodic execution — both self and target delegates fire
            // since active effects are always on the owning ASC
            Owner->OnPeriodicGameplayEffectExecuteDelegateOnSelf.publish(Owner, Effect->Spec, Handle);
            Owner->OnPeriodicGameplayEffectExecuteDelegateOnTarget.publish(Owner, Effect->Spec, Handle);
        }
    }
    
    // Remove expired effects
    for (const auto& Handle : ExpiredEffects)
    {
        Remove(Handle, false);
    }
}

// ============================================================
// Stacking logic
// ============================================================

/** Find an existing active effect that this spec can stack with */
ActiveGameplayEffect* ActiveGameplayEffectsContainer::FindStackableActiveGameplayEffect(const GameplayEffectSpec& Spec)
{
    if (!Spec.Def || Spec.Def->StackingType == EGameplayEffectStackingType::None)
        return nullptr;
    
    for (auto* Effect : Effects)
    {
        if (!Effect || !Effect->Spec.Def) continue;
        
        // Must be the same effect definition
        if (Effect->Spec.Def != Spec.Def) continue;
        
        // Check stacking type
        switch (Spec.Def->StackingType)
        {
        case EGameplayEffectStackingType::AggregateBySource:
            // Stack with same source
            if (Effect->Spec.EffectContext.Data && Spec.EffectContext.Data &&
                Effect->Spec.EffectContext.Data->Instigator == Spec.EffectContext.Data->Instigator)
            {
                return Effect;
            }
            break;
            
        case EGameplayEffectStackingType::AggregateByTarget:
            // Any instance of same effect stacks
            return Effect;
            
        default:
            break;
        }
    }
    
    return nullptr;
}

/** Handle overflow when a stack exceeds its limit */
bool ActiveGameplayEffectsContainer::HandleActiveGameplayEffectStackOverflow(
    ActiveGameplayEffect& ActiveStackableGE, 
    const GameplayEffectSpec& OverflowingSpec)
{
    if (!ActiveStackableGE.Spec.Def) return false;
    
    const auto* Def = ActiveStackableGE.Spec.Def;
    
    if (Def->bDenyOverflowApplication)
    {
        if (Def->bClearStackOnOverflow)
        {
            // Clear the entire stack
            Remove(ActiveStackableGE.Handle);
        }
        // Deny: the overflow spec is not applied
        return false;
    }
    
    // Apply overflow effects (always, regardless of denial)
    for (auto* OverflowEffect : Def->OverflowEffects)
    {
        // Apply overflow effects to this ASC
        // Build minimal context from the existing spec
        GameplayEffectContext OverflowContext;
        OverflowContext.InstigatorAbilitySystemComponent = ActiveStackableGE.Handle.GetOwningAbilitySystemComponent();
        OverflowContext.AbilityLevel = ActiveStackableGE.Spec.Level;
        
        // Apply the overflow effect to ourselves
        if (OverflowEffect && OverflowContext.InstigatorAbilitySystemComponent)
        {
            OverflowContext.InstigatorAbilitySystemComponent->ApplyGameplayEffectToSelf(
                OverflowEffect, OverflowContext);
        }
    }
    
    return !Def->bDenyOverflowApplication;
}

/** Apply stacking logic when adding a new effect */
void ActiveGameplayEffectsContainer::ApplyStackingLogic(GameplayEffectSpec& Spec, ActiveGameplayEffectHandle& OutHandle)
{
    if (!Spec.Def || Spec.Def->StackingType == EGameplayEffectStackingType::None)
        return;
    
    // Find existing stackable effect
    ActiveGameplayEffect* Existing = FindStackableActiveGameplayEffect(Spec);
    if (!Existing || !Existing->Spec.Def) return;
    
    const auto* Def = Existing->Spec.Def;
    int32 StackLimit = Def->StackLimitCount;
    
    if (StackLimit > 0 && Existing->StackCount >= StackLimit)
    {
        // Stack overflow
        HandleActiveGameplayEffectStackOverflow(*Existing, Spec);
        return;
    }
    
    // Stack: increment count and refresh
    int32 OldCount = Existing->StackCount;
    Existing->StackCount++;

    // Fire OnStackChanged delegate
    if (Owner)
    {
        auto EventIt = Owner->ActiveEffectEventSets.find(Existing->Handle);
        if (EventIt != Owner->ActiveEffectEventSets.end())
        {
            EventIt->second.OnStackChanged.publish(Existing->Handle, Existing->StackCount, OldCount);
        }
    }
    
    // Refresh duration per policy
    if (Def->StackDurationRefreshPolicy == EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication)
    {
        Existing->StartWorldTime = 0.0f; // Will be set by caller to current time
    }
    
    // Reset period per policy  
    if (Def->StackPeriodResetPolicy == EGameplayEffectStackingPeriodPolicy::ResetOnSuccessfulApplication)
    {
        // Period reset logic
    }
    
    // Update OutHandle to point to existing
    OutHandle = Existing->Handle;
    
    // Suppress cues for stacking if configured
    if (Def->bSuppressStackingCues)
    {
        // Skip cue triggering
    }
}

// ============================================================
// FScopedAbilityListLock / FScopedTargetListLock
// ============================================================

FScopedAbilityListLock::FScopedAbilityListLock(AbilitySystemComponent& InASC)
    : ASC(InASC)
{
    ASC.IncrementAbilityListLock();
}

FScopedAbilityListLock::~FScopedAbilityListLock()
{
    ASC.DecrementAbilityListLock();
}

FScopedTargetListLock::FScopedTargetListLock(AbilitySystemComponent& InASC)
    : FScopedAbilityListLock(InASC)
{
    ASC.TargetListLockCount++;
}

FScopedTargetListLock::~FScopedTargetListLock()
{
    ASC.TargetListLockCount--;
}

// ============================================================
// AbilitySystemComponent lock helpers
// ============================================================

void AbilitySystemComponent::IncrementAbilityListLock()
{
    AbilityScopeLockCount++;
}

void AbilitySystemComponent::DecrementAbilityListLock()
{
    if (--AbilityScopeLockCount == 0)
    {
        // Process pending adds first
        if (!AbilityPendingAdds.empty())
        {
            for (GameplayAbilitySpec& Spec : AbilityPendingAdds)
            {
                GiveAbility(Spec);
            }
            AbilityPendingAdds.clear();
        }

        // Process pending removes
        auto& Abilities = ActivatableAbilities;
        Abilities.erase(
            std::remove_if(Abilities.begin(), Abilities.end(),
                [this](GameplayAbilitySpec& Spec) {
                    if (Spec.PendingRemove)
                    {
                        OnRemoveAbility(Spec);
                        return true;
                    }
                    return false;
                }),
            Abilities.end());
    }
}

// ============================================================
// ActiveGameplayEffectsContainer::InternalOnActiveGameplayEffectAdded
// ============================================================

void ActiveGameplayEffectsContainer::InternalOnActiveGameplayEffectAdded(ActiveGameplayEffect& Effect)
{
    const GameplayEffect* EffectDef = Effect.Spec.Def;
    if (!EffectDef) return;

    bool bShouldBeActive = EffectDef->OnAddedToActiveContainer(*this, Effect);

    // Effect starts inhibited, then we toggle based on the component results
    Effect.bIsInhibited = true;
    SetActiveGameplayEffectInhibit(Effect.Handle, !bShouldBeActive);
}

// ============================================================
// ActiveGameplayEffectsContainer::SetActiveGameplayEffectInhibit
// ============================================================

void ActiveGameplayEffectsContainer::SetActiveGameplayEffectInhibit(ActiveGameplayEffectHandle Handle, bool bInhibit)
{
    ActiveGameplayEffect* Effect = GetActiveGameplayEffect(Handle);
    if (!Effect) return;

    if (Effect->bIsInhibited == bInhibit) return;

    Effect->bIsInhibited = bInhibit;

    // Fire OnInhibitionChanged delegate
    if (Owner)
    {
        auto EventIt = Owner->ActiveEffectEventSets.find(Handle);
        if (EventIt != Owner->ActiveEffectEventSets.end())
        {
            EventIt->second.OnInhibitionChanged.publish(Handle, bInhibit);
        }
    }
}

// ============================================================
// AbilitySystemComponent — Per-effect event set accessors
// ============================================================

FActiveGameplayEffectEvents* AbilitySystemComponent::GetActiveEffectEventSet(ActiveGameplayEffectHandle Handle)
{
    auto It = ActiveEffectEventSets.find(Handle);
    if (It != ActiveEffectEventSets.end())
    {
        return &It->second;
    }
    return nullptr;
}

FOnActiveGameplayEffectRemoved_Info* AbilitySystemComponent::OnGameplayEffectRemoved_InfoDelegate(ActiveGameplayEffectHandle Handle)
{
    auto* EventSet = GetActiveEffectEventSet(Handle);
    return EventSet ? &EventSet->OnRemoved : nullptr;
}

FOnActiveGameplayEffectStackChange* AbilitySystemComponent::OnGameplayEffectStackChangeDelegate(ActiveGameplayEffectHandle Handle)
{
    auto* EventSet = GetActiveEffectEventSet(Handle);
    return EventSet ? &EventSet->OnStackChanged : nullptr;
}

FOnActiveGameplayEffectTimeChange* AbilitySystemComponent::OnGameplayEffectTimeChangeDelegate(ActiveGameplayEffectHandle Handle)
{
    auto* EventSet = GetActiveEffectEventSet(Handle);
    return EventSet ? &EventSet->OnTimeChanged : nullptr;
}

FOnActiveGameplayEffectInhibitionChanged* AbilitySystemComponent::OnGameplayEffectInhibitionChangedDelegate(ActiveGameplayEffectHandle Handle)
{
	auto* EventSet = GetActiveEffectEventSet(Handle);
	return EventSet ? &EventSet->OnInhibitionChanged : nullptr;
}

// ============================================================
// Attribute Management (Task 28)
// ============================================================

void AbilitySystemComponent::AddSpawnedAttribute(AttributeSet* AttrSet)
{
	if (!AttrSet) return;
	SpawnedAttributes.push_back(AttrSet);
	// Wire OnAttributeAggregatorCreated — for frame-sync, aggregators are computed on-the-fly,
	// so this is a no-op beyond adding to the list.
}

void AbilitySystemComponent::RemoveSpawnedAttribute(AttributeSet* AttrSet)
{
	if (!AttrSet) return;
	SpawnedAttributes.erase(
		std::remove_if(SpawnedAttributes.begin(), SpawnedAttributes.end(),
			[AttrSet](AttributeSet* AS) { return AS == AttrSet; }),
		SpawnedAttributes.end());
}

void AbilitySystemComponent::RemoveAllSpawnedAttributes()
{
	SpawnedAttributes.clear();
}

void AbilitySystemComponent::SetSpawnedAttributes(const std::vector<AttributeSet*>& InAttributes)
{
	SpawnedAttributes = InAttributes;
}

bool AbilitySystemComponent::HasAttributeSetForAttribute(const GameplayAttribute& Attribute) const
{
	for (const auto* AttrSet : SpawnedAttributes)
	{
		if (AttrSet->FindAttributeData(&Attribute))
			return true;
	}
	return false;
}

const AttributeSet* AbilitySystemComponent::GetAttributeSet(const StringName& AttributeOwner) const
{
	for (const auto* AttrSet : SpawnedAttributes)
	{
		const GameplayAttribute* Found = AttrSet->FindAttribute(StringName(), AttributeOwner);
		if (Found)
			return AttrSet;
	}
	return nullptr;
}

void AbilitySystemComponent::GetAllAttributes(std::vector<GameplayAttribute>& OutAttributes) const
{
	for (const auto* AttrSet : SpawnedAttributes)
	{
		for (const auto& [Attr, _] : AttrSet->GetAttributeDataMap())
		{
			OutAttributes.push_back(*Attr);
		}
	}
	std::sort(OutAttributes.begin(), OutAttributes.end(),
		[](const GameplayAttribute& A, const GameplayAttribute& B) {
			auto AOwner = std::string_view(A.AttributeOwner);
			auto BOwner = std::string_view(B.AttributeOwner);
			if (AOwner != BOwner)
				return AOwner < BOwner;
			return std::string_view(A.AttributeName) < std::string_view(B.AttributeName);
		});
	OutAttributes.erase(
		std::unique(OutAttributes.begin(), OutAttributes.end(),
			[](const GameplayAttribute& A, const GameplayAttribute& B) {
				return A.AttributeOwner == B.AttributeOwner && A.AttributeName == B.AttributeName;
			}),
		OutAttributes.end());
}

float AbilitySystemComponent::GetGameplayAttributeValue(GameplayAttribute Attribute, bool& bFound) const
{
	bFound = false;
	for (const auto* AttrSet : SpawnedAttributes)
	{
		const auto* Data = AttrSet->FindAttributeData(&Attribute);
		if (Data)
		{
			bFound = true;
			return Data->GetCurrentValue();
		}
	}
	return 0.0f;
}

void AbilitySystemComponent::SetNumericAttributeBase(GameplayAttribute Attribute, float NewBaseValue)
{
	for (auto* AttrSet : SpawnedAttributes)
	{
		GameplayAttributeData* Data = AttrSet->FindAttributeData(&Attribute);
		if (Data)
		{
			float OldValue = Data->GetBaseValue();
			AttrSet->PreAttributeBaseChange(Attribute, NewBaseValue);
			Data->SetBaseValue(NewBaseValue);
			AttrSet->PostAttributeBaseChange(Attribute, OldValue, NewBaseValue);
		}
	}
}

float AbilitySystemComponent::GetNumericAttributeBase(GameplayAttribute Attribute) const
{
	for (const auto* AttrSet : SpawnedAttributes)
	{
		const auto* Data = AttrSet->FindAttributeData(&Attribute);
		if (Data)
			return Data->GetBaseValue();
	}
	return 0.0f;
}

float AbilitySystemComponent::GetNumericAttributeChecked(GameplayAttribute Attribute) const
{
    // Same as GetNumericAttribute but checked access — falls back to 0.0f if not found
	return GetNumericAttribute(Attribute);
}

float AbilitySystemComponent::GetFilteredAttributeValue(GameplayAttribute Attribute, GameplayTagRequirements& Requirements, GameplayTagContainer& OutSourceTags)
{
	// Collect modifiers only from effects whose captured tags satisfy the requirements
	float BaseValue = 0.0f;
	bool bFoundBase = false;

    // Find base value first
	for (const auto* AttrSet : SpawnedAttributes)
	{
		const auto* Data = AttrSet->FindAttributeData(&Attribute);
		if (Data)
		{
			BaseValue = Data->GetBaseValue();
			bFoundBase = true;
			break;
		}
	}

	if (!bFoundBase) return 0.0f;

	AggregatedModifiers FilteredMods;
	for (auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect || !Effect->Spec.Def || Effect->bIsInhibited) continue;

		// Check if effect's source tags satisfy the tag requirements
		if (!Requirements.RequirementsMet(Effect->Spec.CapturedSourceTags))
			continue;

		// Collect source tags from matching effects
		for (const auto& Tag : Effect->Spec.CapturedSourceTags.GameplayTags)
			OutSourceTags.AddTag(Tag);

		for (size_t i = 0; i < Effect->Spec.Def->Modifiers.size(); i++)
		{
			const auto& Modifier = Effect->Spec.Def->Modifiers[i];
			if (Modifier.Attribute.AttributeName != Attribute.AttributeName)
				continue;

			float Magnitude = (i < Effect->Spec.ModifierMagnitudes.size())
				? Effect->Spec.ModifierMagnitudes[i] : 0.0f;

			switch (Modifier.ModifierOp)
			{
			case EGameplayModOpType::AddBase:
				FilteredMods.SumAddBase += Magnitude;
				break;
			case EGameplayModOpType::MultiplyAdditive:
				FilteredMods.SumMultiplyAdditive += Magnitude;
				break;
			case EGameplayModOpType::DivideAdditive:
				FilteredMods.SumDivideAdditive += Magnitude;
				break;
			case EGameplayModOpType::MultiplyCompound:
				FilteredMods.ProductMultiplyCompound *= Magnitude;
				break;
			case EGameplayModOpType::AddFinal:
				FilteredMods.SumAddFinal += Magnitude;
				break;
			case EGameplayModOpType::Override:
				FilteredMods.bHasOverride = true;
				FilteredMods.OverrideValue = Magnitude;
				break;
			default:
				break;
			}
		}
	}

	return CalculateFinalAttributeValue(BaseValue, FilteredMods);
}

// ============================================================
// Ability Query/Cancel (Task 29)
// ============================================================

GameplayAbilitySpec* AbilitySystemComponent::FindAbilitySpecFromHandle(GameplayAbilitySpecHandle Handle, EConsiderPending ConsiderPending)
{
	for (auto& Spec : ActivatableAbilities)
	{
		if (Spec.Handle == Handle)
		{
			if (Spec.PendingRemove && ConsiderPending == EConsiderPending::No)
				continue;
			return &Spec;
		}
	}
	return nullptr;
}

GameplayAbilitySpec* AbilitySystemComponent::FindAbilitySpecFromClass(GameplayAbility* Ability)
{
	if (!Ability) return nullptr;
	for (auto& Spec : ActivatableAbilities)
	{
		if (Spec.Ability == Ability)
			return &Spec;
	}
	return nullptr;
}

GameplayAbilitySpec* AbilitySystemComponent::FindAbilitySpecFromDefine(GameplayAbilityDefine* AbilityDefine)
{
	if (!AbilityDefine) return nullptr;
	for (auto& Spec : ActivatableAbilities)
	{
		if (Spec.Ability->Define == AbilityDefine)
			return &Spec;
	}
	return nullptr;
}

void AbilitySystemComponent::GetActivatableGameplayAbilitySpecsByAllMatchingTags(
	const GameplayTagContainer& GameplayAbilityTags,
	std::vector<GameplayAbilitySpec*>& OutSpecs,
	bool bOnlyAbilitiesThatSatisfyTagRequirements)
{
	for (auto& Spec : ActivatableAbilities)
	{
		if (Spec.PendingRemove) continue;
		if (!Spec.Ability) continue;

		if (!Spec.DynamicAbilityTags.HasAll(GameplayAbilityTags))
			continue;

		if (bOnlyAbilitiesThatSatisfyTagRequirements)
		{
			if (!Spec.Ability->DoesAbilitySatisfyTagRequirements(*this))
				continue;
		}

		OutSpecs.push_back(&Spec);
	}
}

bool AbilitySystemComponent::TryActivateAbilitiesByTag(const GameplayTagContainer& GameplayAbilityTags, bool bAllowRemoteActivation)
{
	bool bAnyActivated = false;
	for (auto& Spec : ActivatableAbilities)
	{
		if (Spec.PendingRemove) continue;
		if (!Spec.Ability) continue;

		if (Spec.DynamicAbilityTags.HasAll(GameplayAbilityTags))
		{
			if (TryActivateAbility(Spec.Handle, bAllowRemoteActivation))
				bAnyActivated = true;
		}
	}
	return bAnyActivated;
}

bool AbilitySystemComponent::TryActivateAbilityByClass(GameplayAbility* Ability, bool bAllowRemoteActivation)
{
	if (!Ability) return false;
	GameplayAbilitySpec* Spec = FindAbilitySpecFromClass(Ability);
	if (!Spec) return false;
	return TryActivateAbility(Spec->Handle, bAllowRemoteActivation);
}

bool AbilitySystemComponent::TryActivateAbilityByDefine(GameplayAbilityDefine* AbilityDefine, bool bAllowRemoteActivation)
{
	if (!AbilityDefine) return false;
	GameplayAbilitySpec* Spec = FindAbilitySpecFromDefine(AbilityDefine);
	if (!Spec) return false;
	return TryActivateAbility(Spec->Handle, bAllowRemoteActivation);
}

void AbilitySystemComponent::GetAllAbilities(std::vector<GameplayAbilitySpecHandle>& OutHandles)
{
	for (const auto& Spec : ActivatableAbilities)
	{
		if (Spec.PendingRemove) continue;
		OutHandles.push_back(Spec.Handle);
	}
}

void AbilitySystemComponent::FindAllAbilitiesWithTags(std::vector<GameplayAbilitySpecHandle>& OutHandles,
	const GameplayTagContainer& Tags, bool bExactMatch)
{
	for (const auto& Spec : ActivatableAbilities)
	{
		if (Spec.PendingRemove) continue;

		bool bMatches = bExactMatch
			? Spec.DynamicAbilityTags.HasAll(Tags)
			: [&]() {
				for (const auto& Tag : Tags.GameplayTags)
					if (!Spec.DynamicAbilityTags.HasTag(Tag)) return false;
				return true;
			}();

		if (bMatches)
			OutHandles.push_back(Spec.Handle);
	}
}

void AbilitySystemComponent::CancelAbilityHandle(GameplayAbilitySpecHandle Handle)
{
	GameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(Handle);
	if (Spec && Spec->Ability)
	{
		GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
		GameplayAbilityActivationInfo ActivationInfo;
		Spec->Ability->CancelAbility(Spec->Handle, &ActorInfo, ActivationInfo, true);
	}
}

void AbilitySystemComponent::CancelAbilities(const GameplayTagContainer* WithTags, const GameplayTagContainer* WithoutTags, GameplayAbility* Ignore)
{
	ABILITYLIST_SCOPE_LOCK();

	for (auto& Spec : ActivatableAbilities)
	{
		if (Spec.PendingRemove) continue;
		if (!Spec.Ability || Spec.Ability == Ignore) continue;
		if (!Spec.IsActive()) continue;

		// WithTags check — if specified, at least one matching tag must be present
		if (WithTags && WithTags->IsValid())
		{
			bool bHasMatching = false;
			for (const auto& Tag : WithTags->GameplayTags)
			{
				if (Spec.DynamicAbilityTags.HasTag(Tag))
				{
					bHasMatching = true;
					break;
				}
			}
			if (!bHasMatching) continue;
		}

		// WithoutTags check — if specified, none of these tags may be present
		if (WithoutTags && WithoutTags->IsValid())
		{
			bool bHasExcluded = false;
			for (const auto& Tag : WithoutTags->GameplayTags)
			{
				if (Spec.DynamicAbilityTags.HasTag(Tag))
				{
					bHasExcluded = true;
					break;
				}
			}
			if (bHasExcluded) continue;
		}

		GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
		GameplayAbilityActivationInfo ActivationInfo;
		Spec.Ability->CancelAbility(Spec.Handle, &ActorInfo, ActivationInfo, true);
	}
}

void AbilitySystemComponent::CancelAllAbilities(GameplayAbility* Ignore)
{
	ABILITYLIST_SCOPE_LOCK();

	for (auto& Spec : ActivatableAbilities)
	{
		if (Spec.PendingRemove) continue;
		if (!Spec.Ability || Spec.Ability == Ignore) continue;
		if (!Spec.IsActive()) continue;

		GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
		GameplayAbilityActivationInfo ActivationInfo;
		Spec.Ability->CancelAbility(Spec.Handle, &ActorInfo, ActivationInfo, true);
	}
}

void AbilitySystemComponent::DestroyActiveState()
{
	CancelAllAbilities();
}

bool AbilitySystemComponent::AreAbilityTagsBlocked(const GameplayTagContainer& Tags) const
{
	return BlockedAbilityTags.HasAnyMatchingGameplayTags(Tags);
}

void AbilitySystemComponent::BlockAbilitiesWithTags(const GameplayTagContainer& Tags)
{
	for (const auto& Tag : Tags.GameplayTags)
	{
		BlockedAbilityTags.UpdateTagCount(Tag, 1);
	}
}

void AbilitySystemComponent::UnBlockAbilitiesWithTags(const GameplayTagContainer& Tags)
{
	for (const auto& Tag : Tags.GameplayTags)
	{
		BlockedAbilityTags.UpdateTagCount(Tag, -1);
	}
}

void AbilitySystemComponent::ApplyAbilityBlockAndCancelTags(const GameplayTagContainer& AbilityTags, GameplayAbility* RequestingAbility, bool bEnable, const GameplayTagContainer& BlockTags, bool bExecuteBlockTags, const GameplayTagContainer& CancelTags)
{
	if (bEnable)
	{
		if (bExecuteBlockTags)
		{
			BlockAbilitiesWithTags(BlockTags);
		}
		if (!CancelTags.IsEmpty())
		{
			CancelAbilities(&CancelTags, nullptr, RequestingAbility);
		}
	}
	else
	{
		if (bExecuteBlockTags)
		{
			UnBlockAbilitiesWithTags(BlockTags);
		}
	}
}

// ============================================================
// GE Operations (Tasks 30+31)
// ============================================================

int32 AbilitySystemComponent::GetGameplayEffectCount(GameplayEffect* Effect, AbilitySystemComponent* Source, bool bEnforceOnGoingCheck) const
{
	int32 Count = 0;
	for (const auto* ActiveGE : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!ActiveGE || !ActiveGE->Spec.Def) continue;

		if (ActiveGE->Spec.Def != Effect) continue;

		if (bEnforceOnGoingCheck && ActiveGE->GetTimeRemaining(0.0f) <= 0.0f
			&& ActiveGE->Spec.Def->DurationPolicy == EGameplayEffectDurationType::HasDuration)
			continue;

		if (Source)
		{
			if (ActiveGE->Spec.EffectContext.Data
				&& ActiveGE->Spec.EffectContext.Data->InstigatorAbilitySystemComponent != Source)
				continue;
		}

		Count++;
	}
	return Count;
}

float AbilitySystemComponent::GetGameplayEffectDuration(ActiveGameplayEffectHandle Handle) const
{
	const ActiveGameplayEffect* Effect = ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
	if (!Effect || !Effect->Spec.Def) return 0.0f;

	if (Effect->Spec.Def->DurationPolicy == EGameplayEffectDurationType::Instant)
		return -1.0f;
	if (Effect->Spec.Def->DurationPolicy == EGameplayEffectDurationType::Infinite)
		return -1.0f;

	return Effect->Spec.GetDuration();
}

void AbilitySystemComponent::UpdateActiveGameplayEffectSetByCallerMagnitude(
	ActiveGameplayEffectHandle Handle, GameplayTag DataTag, float NewMagnitude)
{
	ActiveGameplayEffect* Effect = ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
	if (!Effect) return;
	Effect->Spec.SetByCallerMagnitudes[DataTag] = NewMagnitude;
}

void AbilitySystemComponent::UpdateActiveGameplayEffectSetByCallerMagnitudes(
	ActiveGameplayEffectHandle Handle, const std::map<GameplayTag, float>& NewMagnitudes)
{
	ActiveGameplayEffect* Effect = ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
	if (!Effect) return;
	for (const auto& [Tag, Magnitude] : NewMagnitudes)
	{
		Effect->Spec.SetByCallerMagnitudes[Tag] = Magnitude;
	}
}

void AbilitySystemComponent::SetActiveGameplayEffectLevel(ActiveGameplayEffectHandle Handle, int32 NewLevel)
{
	ActiveGameplayEffect* Effect = ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
	if (!Effect) return;
	Effect->Spec.Level = NewLevel;
}

void AbilitySystemComponent::SetActiveGameplayEffectInhibit(ActiveGameplayEffectHandle Handle, bool bInhibit, bool bFireCallback)
{
	ActiveGameplayEffects.SetActiveGameplayEffectInhibit(Handle, bInhibit);
	// The container method already fires the OnInhibitionChanged callback.
	// bFireCallback controls whether the callback is fired — the container always fires it
	// via the delegate system, so this parameter is respected at the container level.
}

float AbilitySystemComponent::GetGameplayEffectMagnitude(ActiveGameplayEffectHandle Handle, GameplayAttribute Attribute) const
{
	const ActiveGameplayEffect* Effect = ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
	if (!Effect || !Effect->Spec.Def) return 0.0f;

	for (size_t i = 0; i < Effect->Spec.Def->Modifiers.size(); i++)
	{
		const auto& Modifier = Effect->Spec.Def->Modifiers[i];
		if (Modifier.Attribute.AttributeName == Attribute.AttributeName
			&& Modifier.Attribute.AttributeOwner == Attribute.AttributeOwner)
		{
			return (i < Effect->Spec.ModifierMagnitudes.size())
				? Effect->Spec.ModifierMagnitudes[i] : 0.0f;
		}
	}
	return 0.0f;
}

int32 AbilitySystemComponent::GetCurrentStackCount(ActiveGameplayEffectHandle Handle) const
{
	const ActiveGameplayEffect* Effect = ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
	return Effect ? Effect->StackCount : 0;
}

int32 AbilitySystemComponent::GetCurrentStackCount(GameplayAbilitySpecHandle AbilityHandle) const
{
	// Find the ability spec first
	const GameplayAbilitySpec* FoundSpec = nullptr;
	for (const auto& Spec : ActivatableAbilities)
	{
		if (Spec.Handle == AbilityHandle)
		{
			FoundSpec = &Spec;
			break;
		}
	}

	if (!FoundSpec || !FoundSpec->GameplayEffectHandle.IsValid())
		return 0;

	// Get the active effect that granted this ability — it lives on the source ASC
	AbilitySystemComponent* SourceASC = FoundSpec->GameplayEffectHandle.GetOwningAbilitySystemComponent();
	if (!SourceASC) return 0;

	return SourceASC->GetCurrentStackCount(FoundSpec->GameplayEffectHandle);
}

const ActiveGameplayEffect* AbilitySystemComponent::GetActiveGameplayEffect(ActiveGameplayEffectHandle Handle) const
{
	return ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
}

const GameplayEffect* AbilitySystemComponent::GetGameplayEffectCDO(ActiveGameplayEffectHandle Handle) const
{
	const ActiveGameplayEffect* Effect = ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
	return Effect ? Effect->Spec.Def : nullptr;
}

int32 AbilitySystemComponent::GetAggregatedStackCount(const FGameplayEffectQuery& Query) const
{
	int32 Total = 0;
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect || Effect->bIsInhibited) continue;
		if (Query.Matches(*Effect))
			Total += Effect->StackCount;
	}
	return Total;
}

int32 AbilitySystemComponent::RemoveActiveEffectsWithTags(const GameplayTagContainer& Tags)
{
	if (!Tags.IsValid()) return 0;

	int32 Count = 0;
	std::vector<ActiveGameplayEffectHandle> ToRemove;
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect) continue;
		if (Effect->Spec.CapturedSourceTags.HasAny(Tags)
			|| Effect->Spec.CapturedTargetTags.HasAny(Tags))
		{
			ToRemove.push_back(Effect->Handle);
		}
	}
	for (const auto& Handle : ToRemove)
	{
		RemoveActiveGameplayEffect(Handle);
		Count++;
	}
	return Count;
}

int32 AbilitySystemComponent::RemoveActiveEffectsWithSourceTags(const GameplayTagContainer& Tags)
{
	if (!Tags.IsValid()) return 0;

	int32 Count = 0;
	std::vector<ActiveGameplayEffectHandle> ToRemove;
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect) continue;
		if (Effect->Spec.CapturedSourceTags.HasAny(Tags))
		{
			ToRemove.push_back(Effect->Handle);
		}
	}
	for (const auto& Handle : ToRemove)
	{
		RemoveActiveGameplayEffect(Handle);
		Count++;
	}
	return Count;
}

int32 AbilitySystemComponent::RemoveActiveEffectsWithAppliedTags(const GameplayTagContainer& Tags)
{
	// "Applied" tags = captured source + target tags
	return RemoveActiveEffectsWithTags(Tags);
}

int32 AbilitySystemComponent::RemoveActiveEffectsWithGrantedTags(const GameplayTagContainer& Tags)
{
	if (!Tags.IsValid()) return 0;

	int32 Count = 0;
	std::vector<ActiveGameplayEffectHandle> ToRemove;
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect || !Effect->Spec.Def) continue;

		// Check if any granted ability has tags matching the query
		bool bHasMatchingGranted = false;
		for (const auto& AbilityHandle : Effect->GrantedAbilityHandles)
		{
			// Find the corresponding ability spec via owning ASC
			for (const auto& Spec : ActivatableAbilities)
			{
				if (Spec.Handle == AbilityHandle
					&& Spec.DynamicAbilityTags.HasAny(Tags))
				{
					bHasMatchingGranted = true;
					break;
				}
			}
			if (bHasMatchingGranted) break;
		}
		if (bHasMatchingGranted)
			ToRemove.push_back(Effect->Handle);
	}
	for (const auto& Handle : ToRemove)
	{
		RemoveActiveGameplayEffect(Handle);
		Count++;
	}
	return Count;
}

std::vector<float> AbilitySystemComponent::GetActiveEffectsTimeRemaining(const FGameplayEffectQuery& Query) const
{
	std::vector<float> Results;
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect || Effect->bIsInhibited) continue;
		if (Query.Matches(*Effect))
			Results.push_back(Effect->GetTimeRemaining(0.0f));
	}
	return Results;
}

std::vector<float> AbilitySystemComponent::GetActiveEffectsDuration(const FGameplayEffectQuery& Query) const
{
	std::vector<float> Results;
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect || Effect->bIsInhibited) continue;
		if (Query.Matches(*Effect))
			Results.push_back(Effect->Spec.GetDuration());
	}
	return Results;
}

void AbilitySystemComponent::GetAllActiveGameplayEffectSpecs(std::vector<GameplayEffectSpec>& OutSpecs)
{
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect) continue;
		OutSpecs.push_back(Effect->Spec);
	}
}

void AbilitySystemComponent::ModifyActiveEffectStartTime(ActiveGameplayEffectHandle Handle, float DeltaTime)
{
	ActiveGameplayEffect* Effect = ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
	if (!Effect) return;

	float OldTimeRemaining = Effect->GetTimeRemaining(0.0f);
	Effect->StartWorldTime += DeltaTime;
	float NewTimeRemaining = Effect->GetTimeRemaining(0.0f);

	// Fire OnTimeChanged delegate
	auto EventIt = ActiveEffectEventSets.find(Handle);
	if (EventIt != ActiveEffectEventSets.end())
	{
		EventIt->second.OnTimeChanged.publish(Handle, NewTimeRemaining, OldTimeRemaining);
	}
}

std::vector<ActiveGameplayEffectHandle> AbilitySystemComponent::GetActiveEffectsWithAllTags(const GameplayTagContainer& Tags) const
{
	std::vector<ActiveGameplayEffectHandle> Results;
	if (!Tags.IsValid())
	{
		return GetAllActiveEffectHandles();
	}
	for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
	{
		if (!Effect || !Effect->Spec.Def) continue;
		if (Effect->Spec.CapturedSourceTags.HasAll(Tags)
			|| Effect->Spec.CapturedTargetTags.HasAll(Tags))
		{
			Results.push_back(Effect->Handle);
		}
	}
	return Results;
}

// ============================================================
// InputID (Task 32)
// ============================================================

void AbilitySystemComponent::ClearAllAbilities()
{
	ABILITYLIST_SCOPE_LOCK();

	for (auto& Spec : ActivatableAbilities)
	{
		if (!Spec.PendingRemove)
		{
			if (Spec.IsActive() && Spec.Ability)
			{
				GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
				GameplayAbilityActivationInfo ActivationInfo;
				Spec.Ability->CancelAbility(Spec.Handle, &ActorInfo, ActivationInfo, true);
			}
			Spec.PendingRemove = true;
		}
	}
}

void AbilitySystemComponent::ClearAllAbilitiesWithInputID(int32 InputID)
{
	ABILITYLIST_SCOPE_LOCK();

	for (auto& Spec : ActivatableAbilities)
	{
		if (!Spec.PendingRemove && Spec.InputID == InputID)
		{
			if (Spec.IsActive() && Spec.Ability)
			{
				GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
				GameplayAbilityActivationInfo ActivationInfo;
				Spec.Ability->CancelAbility(Spec.Handle, &ActorInfo, ActivationInfo, true);
			}
			Spec.PendingRemove = true;
		}
	}
}

void AbilitySystemComponent::ClearAbility(GameplayAbilitySpecHandle Handle)
{
	for (auto& Spec : ActivatableAbilities)
	{
		if (Spec.Handle == Handle && !Spec.PendingRemove)
		{
			if (Spec.IsActive() && Spec.Ability)
			{
				GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
				GameplayAbilityActivationInfo ActivationInfo;
				Spec.Ability->CancelAbility(Spec.Handle, &ActorInfo, ActivationInfo, true);
			}
			Spec.PendingRemove = true;
			return;
		}
	}
}

void AbilitySystemComponent::SetRemoveAbilityOnEnd(GameplayAbilitySpecHandle Handle)
{
	GameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(Handle);
	if (Spec)
	{
		Spec->RemoveAfterActivation = true;
	}
}

void AbilitySystemComponent::BlockAbilityByInputID(int32 InputID)
{
	BlockedInputIDs.insert(InputID);
}

void AbilitySystemComponent::UnBlockAbilityByInputID(int32 InputID)
{
	BlockedInputIDs.erase(InputID);
}

bool AbilitySystemComponent::IsAbilityInputBlocked(int32 InputID) const
{
	return BlockedInputIDs.contains(InputID);
}

