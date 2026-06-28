#include "ge_component_granted_abilities.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

bool GrantedAbilitiesGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    if (Container.IsNetAuthority())
    {
        // Register for removal and inhibition callbacks
        auto* EventSet = Container.Owner->GetActiveEffectEventSet(Effect.Handle);
        if (EventSet)
        {
            Effect.OnRemovedDelegateHandle = EventSet->OnRemoved.Add<&GrantedAbilitiesGEComponent::OnActiveGameplayEffectRemoved>(*this);
            Effect.OnInhibitionChangedDelegateHandle = EventSet->OnInhibitionChanged.Add<&GrantedAbilitiesGEComponent::OnInhibitionChanged>(*this);
        }

        GrantAbilities(Effect.Handle);
    }

    return true;
}

void GrantedAbilitiesGEComponent::OnActiveGameplayEffectRemoved(const FGameplayEffectRemovalInfo& RemovalInfo) const
{
    const ActiveGameplayEffect* ActiveGE = RemovalInfo.ActiveEffect;
    if (!ActiveGE)
    {
        return;
    }

    RemoveAbilities(ActiveGE->Handle);
}

void GrantedAbilitiesGEComponent::OnInhibitionChanged(ActiveGameplayEffectHandle ActiveGEHandle, bool bIsInhibited) const
{
    if (bIsInhibited)
    {
        RemoveAbilities(ActiveGEHandle);
    }
    else
    {
        GrantAbilities(ActiveGEHandle);
    }
}

void GrantedAbilitiesGEComponent::GrantAbilities(ActiveGameplayEffectHandle ActiveGEHandle) const
{
    AbilitySystemComponent* ASC = ActiveGEHandle.GetOwningAbilitySystemComponent();
    if (!ASC)
    {
        return;
    }

    if (ASC->bSuppressGrantAbility)
    {
        return;
    }

    const ActiveGameplayEffect* ActiveGE = ASC->GetActiveGameplayEffect(ActiveGEHandle);
    if (!ActiveGE)
    {
        return;
    }
    const GameplayEffectSpec& ActiveGESpec = ActiveGE->Spec;

    const std::vector<GameplayAbilitySpec>& AllAbilities = ASC->GetActivatableAbilities();
    for (const auto& AbilityConfig : GrantAbilityConfigs)
    {
        if (!AbilityConfig.Ability)
        {
            continue;
        }

        // Only grant if the ability hasn't already been granted by this GE handle
        const bool bAlreadyGranted = std::any_of(AllAbilities.begin(), AllAbilities.end(),
            [&](const GameplayAbilitySpec& Spec) {
                return Spec.Ability == AbilityConfig.Ability && Spec.GameplayEffectHandle == ActiveGEHandle;
            });
        if (bAlreadyGranted)
        {
            continue;
        }

        const int32 Level = static_cast<int32>(AbilityConfig.LevelScalableFloat.GetValueAtLevel(ActiveGESpec.Level));

        // Build the spec with the SourceObject from the effect context
        GameplayAbilitySpec AbilitySpec(AbilityConfig.Ability, Level);
        AbilitySpec.InputID = AbilityConfig.InputID;
        AbilitySpec.SetByCallerTagMagnitudes = ActiveGESpec.SetByCallerMagnitudes;
        // @deprecated: Also copy name-based magnitudes
        AbilitySpec.SetByCallerNameMagnitudes = ActiveGESpec.SetByCallerNameMagnitudes;
        AbilitySpec.GameplayEffectHandle = ActiveGEHandle;

        ASC->GiveAbility(AbilitySpec);
    }
}

void GrantedAbilitiesGEComponent::RemoveAbilities(ActiveGameplayEffectHandle ActiveGEHandle) const
{
    AbilitySystemComponent* ASC = ActiveGEHandle.GetOwningAbilitySystemComponent();
    if (!ASC)
    {
        return;
    }

    FScopedAbilityListLock ScopedAbilityListLock(*ASC);
    const std::vector<const GameplayAbilitySpec*> GrantedAbilities = ASC->FindAbilitySpecsFromGEHandle(
        ScopedAbilityListLock, ActiveGEHandle, EConsiderPending::Yes);
    for (const auto& AbilityConfig : GrantAbilityConfigs)
    {
        if (!AbilityConfig.Ability)
        {
            continue;
        }

        // Find the spec that matches this ability CDO
        auto It = std::find_if(GrantedAbilities.begin(), GrantedAbilities.end(),
            [&](const GameplayAbilitySpec* Spec) { return Spec && Spec->Ability == AbilityConfig.Ability; });
        if (It == GrantedAbilities.end() || !(*It))
        {
            continue;
        }
        const GameplayAbilitySpec& AbilitySpec = **It;

        switch (AbilityConfig.RemovalPolicy)
        {
            case EGameplayEffectGrantedAbilityRemovePolicy::CancelAbilityImmediately:
            {
                ASC->ClearAbility(AbilitySpec.Handle);
                break;
            }
            case EGameplayEffectGrantedAbilityRemovePolicy::RemoveAbilityOnEnd:
            {
                ASC->SetRemoveAbilityOnEnd(AbilitySpec.Handle);
                break;
            }
            default:
            {
                // Do nothing to granted ability
                break;
            }
        }
    }
}