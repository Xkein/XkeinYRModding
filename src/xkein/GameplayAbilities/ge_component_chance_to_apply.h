#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

/**
 * Random probability check before GE application.
 * Block the effect if ChanceToApplyToTarget rolls below a random threshold.
 * UE equivalent: UChanceToApplyGameplayEffectComponent
 *
 * NOTE: Uses rand() for the probability roll.
 * For deterministic lockstep gameplay, consider replacing with a
 * seed-based random function keyed on effect context.
 */
CLASS(IniComponent, IniAutoLoad)
class ChanceToApplyGEComponent : public GameplayEffectComponent
{
public:
    /** Probability [0..1] of this GE applying to the target. Default 1.0 (always applies). */
    PROPERTY()
    FScalableFloat ChanceToApplyToTarget = 1.0f;

    bool CanGameplayEffectApply(
        const ActiveGameplayEffectsContainer& Container,
        const GameplayEffectSpec& Spec) const override;
};
