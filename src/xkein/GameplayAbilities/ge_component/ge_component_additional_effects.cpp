#include "ge_component_additional_effects.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

void AdditionalEffectsGEComponent::OnGameplayEffectApplied(
    ActiveGameplayEffectsContainer& Container,
    GameplayEffectSpec& Spec,
    AbilitySystemComponent& OwningASC) const
{
    GameplayEffectContext Context;
    if (Spec.EffectContext.Data)
    {
        Context = *Spec.EffectContext.Data;
    }

    for (auto* Effect : OnApplicationGameplayEffects)
    {
        if (!Effect) continue;
        OwningASC.ApplyGameplayEffectToTarget(Effect, &OwningASC, Context);
    }
}

void AdditionalEffectsGEComponent::OnActiveGameplayEffectRemoved(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect,
    const FGameplayEffectRemovalInfo& RemovalInfo) const
{
    AbilitySystemComponent* TargetASC = Container.Owner;
    if (!TargetASC) return;

    GameplayEffectContext Context;
    if (RemovalInfo.EffectContext.Data)
    {
        Context = *RemovalInfo.EffectContext.Data;
    }

    // OnCompleteAlways fires regardless of removal reason
    for (auto* GE : OnCompleteAlways)
    {
        if (!GE) continue;
        TargetASC->ApplyGameplayEffectToTarget(GE, TargetASC, Context);
    }

    if (RemovalInfo.bPrematureRemoval)
    {
        for (auto* GE : OnCompletePrematurely)
        {
            if (!GE) continue;
            TargetASC->ApplyGameplayEffectToTarget(GE, TargetASC, Context);
        }
    }
    else
    {
        for (auto* GE : OnCompleteNormal)
        {
            if (!GE) continue;
            TargetASC->ApplyGameplayEffectToTarget(GE, TargetASC, Context);
        }
    }
}
