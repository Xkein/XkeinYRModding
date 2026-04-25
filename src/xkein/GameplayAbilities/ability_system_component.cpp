#include "ability_system_component.h"
#include "xkein/GameplayAbilities/ge_component.h"
#include <core/tool/container.h>
#include <map>
#include <algorithm>

FOnGameplayTagCountChanged& AbilitySystemComponent::RegisterGameplayTagEvent(const GameplayTag& Tag)
{
    return GameplayTagEventMap[Tag];
}

int32 AbilitySystemComponent::HandleGameplayEvent(const GameplayTag& EventTag, const GameplayEventData* Payload)
{
    int32 NumActivated = 0;
    (void)Payload;

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
    auto It = GameplayTagEventMap.find(Tag);
    if (It != GameplayTagEventMap.end())
    {
        It->second.publish(Tag, NewCount);
    }
}

GameplayAbilitySpecHandle AbilitySystemComponent::GiveAbility(const GameplayAbilitySpec& AbilitySpec)
{
    if (AbilitySpec.Ability == nullptr) {
        
        gLogger->error("GiveAbility called with an invalid Ability Class.");

		return GameplayAbilitySpecHandle();
    }

    ActivatableAbilities.push_back(AbilitySpec);
    GameplayAbilitySpec& OwnedSpec = ActivatableAbilities.back();
    
    // Assign a unique handle
    OwnedSpec.Handle = GameplayAbilitySpecHandle::GenerateNewHandle();

    OnGiveAbility(OwnedSpec);
	MarkAbilitySpecDirty(OwnedSpec, true);

    return OwnedSpec.Handle;
}

void AbilitySystemComponent::OnGiveAbility(GameplayAbilitySpec& Spec)
{
    if (Spec.Ability == nullptr) {
        return;
    }

    const GameplayAbility* SpecAbility = Spec.Ability;

    if (Spec.GameplayEffectHandle.IsValid())
    {
		AbilitySystemComponent* SourceASC = Spec.GameplayEffectHandle.GetOwningAbilitySystemComponent();
		if (SourceASC)
		{
			ActiveGameplayEffect* SourceActiveGE = SourceASC->ActiveGameplayEffects.GetActiveGameplayEffect(Spec.GameplayEffectHandle);
			if (SourceActiveGE)
			{
                std_vector_add_unique(SourceActiveGE->GrantedAbilityHandles, Spec.Handle);
				// SourceASC->ActiveGameplayEffects.MarkItemDirty(*SourceActiveGE);
			}
			else {
				gLogger->error("OnGiveAbility Spec has invalid ActiveGameplayEffect");
			}
		}
        else {
			gLogger->error("OnGiveAbility Spec GameplayEffectHandle has no owning ASC");
        }
    }

    
	for (const AbilityTriggerData& TriggerData : Spec.Ability->AbilityTriggers)
	{
		GameplayTag EventTag = TriggerData.TriggerTag;

		auto& TriggeredAbilityMap = (TriggerData.TriggerSource == EGameplayAbilityTriggerSource::GameplayEvent) ? GameplayEventTriggeredAbilities : OwnedTagTriggeredAbilities;

		if (TriggeredAbilityMap.contains(EventTag))
		{
            std_vector_add_unique(TriggeredAbilityMap[EventTag], Spec.Handle); // Fixme: is this right? Do we want to trigger the ability directly of the spec?
		}
		else
		{
			std::vector<GameplayAbilitySpecHandle> Triggers;
			Triggers.push_back(Spec.Handle);
            TriggeredAbilityMap[EventTag] = Triggers;
		}

		// if (TriggerData.TriggerSource != EGameplayAbilityTriggerSource::GameplayEvent)
		// {
		// 	FOnGameplayEffectTagCountChanged& CountChangedEvent = RegisterGameplayTagEvent(EventTag);
		// 	// Add a change callback if it isn't on it already

		// 	if (!CountChangedEvent.IsBoundToObject(this))
		// 	{
		// 		MonitoredTagChangedDelegateHandle = CountChangedEvent.AddUObject(this, &UAbilitySystemComponent::MonitoredTagChanged);
		// 	}
		// }
	}
}

void AbilitySystemComponent::MarkAbilitySpecDirty(GameplayAbilitySpec& Spec, bool WasAddOrRemove)
{

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
    
    GameplayAbility* Ability = FoundSpec->Ability;
    
    // Build ActorInfo
    GameplayAbilityActorInfo ActorInfo = GameplayAbilityActorInfo::InitFromActor(Owner, Avatar, this);
    
    // Check if ability can be activated
    if (!Ability->CanActivateAbility(AbilityToActivate, &ActorInfo))
    {
        return false;
    }
    
    // Create activation info (authority mode for single-player)
    GameplayAbilityActivationInfo ActivationInfo;
    ActivationInfo.ActivationMode = EGameplayAbilityActivationMode::Authority;
    
    // Call the ability
    Ability->CallActivateAbility(AbilityToActivate, &ActorInfo, ActivationInfo, nullptr, nullptr);
    
    return true;
}

void AbilitySystemComponent::CancelAbility(GameplayAbility* Ability)
{
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

bool AbilitySystemComponent::CheckCooldown(GameplayAbilitySpecHandle Handle) const
{
    // Check if any active effect on this ASC has a matching cooldown tag
    for (const auto* Effect : ActiveGameplayEffects.GetAllActiveEffects())
    {
        if (Effect && Effect->Spec.Def)
        {
            for (auto* Component : Effect->Spec.Def->GEComponents)
            {
                // Future: check for cooldown tag matching via components
            }
        }
    }
    return true; // Assume no cooldown if no matching effect
}

void AbilitySystemComponent::ApplyCooldown(GameplayAbilitySpecHandle Handle, GameplayEffect* CooldownEffect)
{
    if (!CooldownEffect) return;
    
    GameplayEffectContext Context;
    Context.Instigator = Owner;
    Context.AbilityLevel = 1;
    Context.InstigatorAbilitySystemComponent = const_cast<AbilitySystemComponent*>(this);
    
    ApplyGameplayEffectToTarget(CooldownEffect, const_cast<AbilitySystemComponent*>(this), Context);
}

bool AbilitySystemComponent::CheckCost(GameplayAbilitySpecHandle Handle) const
{
    // Simplified: always return true for base implementation
    // Future: check attributes (e.g., has enough mana, stamina, etc.)
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

void AbilitySystemComponent::OnRemoveAbility(GameplayAbilitySpec& Spec)
{
    if (Spec.Ability == nullptr) return;
    
    // Remove from trigger maps
    for (const AbilityTriggerData& TriggerData : Spec.Ability->AbilityTriggers)
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

    AttributeData->SetBaseValue(NewValue);
}

/** Execute an instant effect: apply modifiers directly to base values */
static void ExecuteInstantEffect(AbilitySystemComponent* Target, const GameplayEffectSpec& Spec)
{
    if (!Spec.Def) return;
    
    for (size_t i = 0; i < Spec.Def->Modifiers.size(); i++)
    {
        const auto& Modifier = Spec.Def->Modifiers[i];
        float Magnitude = (i < Spec.ModifierMagnitudes.size()) ? Spec.ModifierMagnitudes[i] : 0.0f;
        
        // Apply to matching attribute sets on the target
        for (auto& AttrSet : Target->SpawnedAttributes)
        {
            ApplyModifierToAttribute(&AttrSet, Modifier.Attribute, Magnitude, Modifier.ModifierOp);
        }
    }
}

/** Check if all GE Components allow the effect to be applied */
static bool CanApplyWithComponents(GameplayEffect* Effect, const GameplayEffectSpec& Spec, 
    const ActiveGameplayEffectsContainer& Container)
{
    if (!Effect) return true;
    
    for (auto* Component : Effect->GEComponents)
    {
        if (Component && !Component->CanGameplayEffectApply(Container, Spec))
        {
            return false;
        }
    }
    return true;
}

/** Notify all GE Components that the effect was added */
static void NotifyComponentsAdded(GameplayEffect* Effect, ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& ActiveEffect)
{
    if (!Effect) return;
    
    for (auto* Component : Effect->GEComponents)
    {
        if (Component)
        {
            Component->OnActiveGameplayEffectAdded(Container, ActiveEffect);
        }
    }
}

/** Notify all GE Components that the effect was executed (instant) */
static void NotifyComponentsExecuted(GameplayEffect* Effect, ActiveGameplayEffectsContainer& Container,
    GameplayEffectSpec& Spec)
{
    if (!Effect) return;
    
    for (auto* Component : Effect->GEComponents)
    {
        if (Component)
        {
            Component->OnGameplayEffectExecuted(Container, Spec);
        }
    }
}

/** Notify all GE Components that the effect was applied */
static void NotifyComponentsApplied(GameplayEffect* Effect, ActiveGameplayEffectsContainer& Container,
    GameplayEffectSpec& Spec)
{
    if (!Effect) return;
    
    for (auto* Component : Effect->GEComponents)
    {
        if (Component)
        {
            Component->OnGameplayEffectApplied(Container, Spec);
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
    
    // Step 1: Component pre-apply check
    if (!CanApplyWithComponents(Effect, Spec, Target->ActiveGameplayEffects))
    {
        Effect->GEComponents; // Components blocked the application
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
        NotifyComponentsExecuted(Effect, Target->ActiveGameplayEffects, Spec);
        
        // Notify components of application
        NotifyComponentsApplied(Effect, Target->ActiveGameplayEffects, Spec);
        
        return ActiveGameplayEffectHandle(-1);
    }
        
    case EGameplayEffectDurationType::Infinite:
    case EGameplayEffectDurationType::HasDuration:
    {
        // Add as active effect
        ActiveGameplayEffectHandle Handle = Target->ActiveGameplayEffects.Add(Spec);
        
        // Apply modifiers to current value for duration effects
        ExecuteInstantEffect(Target, Spec);
        
        // Notify components that the effect was added (tag granting, ability granting, etc.)
        ActiveGameplayEffect* ActiveGE = Target->ActiveGameplayEffects.GetActiveGameplayEffect(Handle);
        if (ActiveGE)
        {
            NotifyComponentsAdded(Effect, Target->ActiveGameplayEffects, *ActiveGE);
        }
        
        // Notify components of application
        NotifyComponentsApplied(Effect, Target->ActiveGameplayEffects, Spec);
        
        return Handle;
    }
    }
    
    return ActiveGameplayEffectHandle();
}

ActiveGameplayEffectHandle AbilitySystemComponent::ApplyGameplayEffectToSelf(
    GameplayEffect* Effect, const GameplayEffectContext& Context)
{
    return ApplyGameplayEffectToTarget(Effect, this, Context);
}

GameplayEffectSpec AbilitySystemComponent::MakeOutgoingSpec(GameplayEffect* Effect, float Level) const
{
    GameplayEffectSpec Spec;
    Spec.Def = Effect;
    Spec.Level = static_cast<int32>(Level);
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

void AbilitySystemComponent::ApplyModToAttribute(const GameplayAttribute& Attribute, EGameplayModOpType ModifierOp, float ModifierMagnitude)
{
    for (auto& AttrSet : SpawnedAttributes)
    {
        ::ApplyModifierToAttribute(&AttrSet, Attribute, ModifierMagnitude, ModifierOp);
    }
}

float AbilitySystemComponent::GetNumericAttribute(const GameplayAttribute& Attribute) const
{
    for (const auto& AttrSet : SpawnedAttributes)
    {
        const auto* Data = AttrSet.FindAttributeData(&Attribute);
        if (Data)
        {
            return Data->GetCurrentValue();
        }
    }
    return 0.0f;
}

void AbilitySystemComponent::ExecuteGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params)
{
    gLogger->info("ExecuteGameplayCue: {}", CueTag.TagName);
}

void AbilitySystemComponent::AddGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params)
{
    gLogger->info("AddGameplayCue: {}", CueTag.TagName);
}

void AbilitySystemComponent::RemoveGameplayCue(const GameplayTag& CueTag)
{
    gLogger->info("RemoveGameplayCue: {}", CueTag.TagName);
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

ActiveGameplayEffectHandle ActiveGameplayEffectsContainer::Add(GameplayEffectSpec& Spec)
{
    auto* NewEffect = new ActiveGameplayEffect();
    NewEffect->Spec = Spec;
    NewEffect->Handle = ActiveGameplayEffectHandle::GenerateNewHandle(nullptr);
    Effects.push_back(NewEffect);
    return NewEffect->Handle;
}

void ActiveGameplayEffectsContainer::Remove(ActiveGameplayEffectHandle Handle)
{
    auto It = std::remove_if(Effects.begin(), Effects.end(), 
        [&Handle](ActiveGameplayEffect* Effect) {
            if (Effect && Effect->Handle == Handle)
            {
                delete Effect;
                return true;
            }
            return false;
        });
    Effects.erase(It, Effects.end());
}

void ActiveGameplayEffectsContainer::RemoveAll()
{
    for (auto* Effect : Effects)
    {
        delete Effect;
    }
    Effects.clear();
}

void ActiveGameplayEffectsContainer::Tick(float DeltaTime)
{
    std::vector<ActiveGameplayEffectHandle> ExpiredEffects;
    
    for (auto* Effect : Effects)
    {
        if (!Effect || !Effect->Spec.Def) continue;
        
        const auto* Def = Effect->Spec.Def;
        
        // Handle duration-based effects
        if (Def->DurationPolicy == EGameplayEffectDurationType::HasDuration)
        {
            // Track start time and duration - simplified: track remaining time in Spec
            // For a full implementation, we'd store StartTime and Duration on ActiveGameplayEffect
            // For now, we handle this via the stacking expiration policy
        }
        
        // Handle periodic effects
        if (Def->Period > 0.0f)
        {
            // Track elapsed time since last period execution
            // Simplified: periodic execution is tracked externally
            // In a full implementation, we'd store LastPeriodTime on ActiveGameplayEffect
        }
    }
    
	// Remove expired effects
	for (const auto& Handle : ExpiredEffects)
	{
		Remove(Handle);
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
    Existing->StackCount++;
    
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

static float GetDeltaTime()
{
    // Get frame delta time from the game
    // In YR, this can be derived from the event context
    // For now, use a fixed step since we don't have direct access to frame time here
    return 1.0f / 60.0f; // ~16ms per frame at 60fps
}

static void Tick()
{
    float DeltaTime = GetDeltaTime();
    
    // update all ability system components
    for (auto&& [entity, asc] : gEntt->view<AbilitySystemComponent>().each())
    {
        asc.ActiveGameplayEffects.Tick(DeltaTime);
    }
}

#include "yr/yr_all_events.h"

DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent)
{
    Tick();
}
