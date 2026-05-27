#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"

struct ActiveGameplayEffectsContainer;
struct ActiveGameplayEffect;
struct GameplayEffectSpec;
class AbilitySystemComponent;

/**
 * Base class for GameplayEffect components.
 * Components add modular behavior to GameplayEffects by hooking into lifecycle events.
 * Simplified version of UE5's UGameplayEffectComponent.
 */
CLASS(BindJs)
class GameplayEffectComponent
{
public:
    GameplayEffectComponent() = default;
    virtual ~GameplayEffectComponent() = default;

    /**
     * Called before the GE is applied to check if it can proceed.
     * Return false to block application.
     */
    virtual bool CanGameplayEffectApply(
        const ActiveGameplayEffectsContainer& Container,
        const GameplayEffectSpec& Spec) const { return true; }

    /**
     * Called when a Gameplay Effect is Added to the ActiveGameplayEffectsContainer.
     * GE's are added to that container when they have duration (or are predicting locally).
     * Return true if the effect should remain active, or false to inhibit.
     * Note: Inhibit does not remove the effect (it remains added but dormant, waiting to uninhibit).
     */
    virtual bool OnActiveGameplayEffectAdded(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect) const { return true; }

    /** Called right before the active gameplay effect is removed (Duration/Infinite). */
    virtual void OnActiveGameplayEffectRemoved(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect,
        const FGameplayEffectRemovalInfo& RemovalInfo) const {}

    /**
     * Called when an instant GE executes.
     */
    virtual void OnGameplayEffectExecuted(
        ActiveGameplayEffectsContainer& Container,
        GameplayEffectSpec& Spec) const {}

    /**
     * Called after the GE is successfully applied (any type).
     */
    virtual void OnGameplayEffectApplied(
        ActiveGameplayEffectsContainer& Container,
        GameplayEffectSpec& Spec,
        AbilitySystemComponent& OwningASC) const {}
};
