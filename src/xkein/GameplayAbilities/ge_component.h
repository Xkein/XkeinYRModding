#pragma once
#include "core/reflection/reflection.h"

struct ActiveGameplayEffectsContainer;
struct ActiveGameplayEffect;
struct GameplayEffectSpec;

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
     * Called after the GE is added as an active effect (Duration/Infinite types).
     */
    virtual void OnActiveGameplayEffectAdded(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect) const {}

    /** Called right before the active gameplay effect is removed (Duration/Infinite). */
    virtual void OnActiveGameplayEffectRemoved(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect) const {}

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
        GameplayEffectSpec& Spec) const {}
};
