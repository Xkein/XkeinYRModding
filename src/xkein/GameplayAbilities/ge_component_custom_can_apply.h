#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component.h"
#include "scripting/common/script_function.h"

/**
 * Custom application requirement type.
 * ScriptFunction that evaluates whether a GE can be applied based on custom logic.
 */
using GameplayEffectCustomApplicationRequirementCreator = ScriptFunction<bool(const GameplayEffectSpec&)>;

/**
 * Custom application requirement via script functions.
 * Iterates registered requirement creators; blocks application if any returns false.
 * UE equivalent: UCustomCanApplyGameplayEffectComponent (custom)
 */
CLASS(IniComponent, IniAutoLoad)
class CustomCanApplyGEComponent : public GameplayEffectComponent
{
public:
    PROPERTY()
    std::vector<StringName> ApplicationRequirementCreators;

    bool CanGameplayEffectApply(
        const ActiveGameplayEffectsContainer& Container,
        const GameplayEffectSpec& Spec) const override;
};
