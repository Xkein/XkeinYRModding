#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/gameplay_effect_calculation.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include <functional>
#include <vector>

class AbilitySystemComponent;

/**
 * Parameters passed into a GameplayEffectExecutionCalculation's Execute() method.
 * Provides read access to the owning spec and both ability system components,
 * plus any tags or handles that should be ignored during evaluation.
 *
 * All pointers are non-owning — the lifetime is managed externally.
 */
CLASS(BindJs)
struct FGameplayEffectCustomExecutionParameters
{
	/** The gameplay effect spec being executed (non-owning) */
	const GameplayEffectSpec* OwningSpec = nullptr;

	/** The target ability system component receiving the effect (non-owning) */
	AbilitySystemComponent* TargetASC = nullptr;

	/** The source ability system component that created the effect (non-owning) */
	AbilitySystemComponent* SourceASC = nullptr;

	/** Tags passed in from the execution definition for conditional logic */
	GameplayTagContainer PassedInTags;

	/**
	 * Handles of active gameplay effects to ignore when evaluating attributes.
	 * Useful for preventing double-counting of a newly created effect's own modifiers.
	 */
	std::vector<ActiveGameplayEffectHandle> IgnoreHandles;
};

/**
 * Output structure produced by a GameplayEffectExecutionCalculation's Execute() method.
 * Can contain any number of output modifiers that get applied to the target,
 * and flags indicating whether conditional GEs, stack counts, or gameplay cues
 * were handled manually by the execution.
 */
CLASS(BindJs)
struct FGameplayEffectCustomExecutionOutput
{
	/** Modifiers computed by this execution to apply to the target's attributes */
	std::vector<FGameplayModifierEvaluatedData> OutputModifiers;

	/** If true, conditional gameplay effects from the execution definition should be triggered */
	bool bTriggerConditionalGE = false;

	/** If true, the execution has handled stack count logic internally */
	bool bHandledStackCountManually = false;

	/** If true, the execution has handled gameplay cue triggering internally */
	bool bHandledGameplayCuesManually = false;

	/**
	 * Add an evaluated modifier to the output list.
	 * @param Data The modifier data (attribute, op, magnitude) to apply
	 */
	void AddOutputModifier(const FGameplayModifierEvaluatedData& Data)
	{
		OutputModifiers.push_back(Data);
	}
};

/**
 * Base class for gameplay effect custom execution calculations.
 *
 * Override Execute() in a native subclass or bind OnK2_Execute in script
 * to implement custom execution logic that runs when a gameplay effect
 * carrying this execution definition is applied to a target.
 *
 * Has full access to both source and target ASC through the execution parameters,
 * and can produce any number of output modifiers.
 */
CLASS(BindJs)
class GameplayEffectExecutionCalculation : public GameplayEffectCalculation
{
public:
	GameplayEffectExecutionCalculation() = default;
	virtual ~GameplayEffectExecutionCalculation() = default;

	/**
	 * Execute custom logic when this gameplay effect is applied to a target.
	 * Override in native subclasses or leave for script (OnK2_Execute).
	 *
	 * @param ExecutionParams Read-only parameters (spec, source/target ASC, tags, ignored handles)
	 * @param OutExecutionOutput [OUT] Output modifiers and flags produced by this execution
	 */
	virtual void Execute(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;

	/**
	 * Script-side callback for custom execution logic.
	 * If set, this is called by Execute() in preference to the virtual.
	 * Signature: void(const FGameplayEffectCustomExecutionParameters& Params, FGameplayEffectCustomExecutionOutput& Output)
	 */
	PROPERTY()
	std::function<void(const FGameplayEffectCustomExecutionParameters&, FGameplayEffectCustomExecutionOutput&)> OnK2_Execute;
};
