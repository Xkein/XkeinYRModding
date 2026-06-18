#include "xkein/GameplayAbilities/gameplay_effect_execution_calculation.h"

void GameplayEffectExecutionCalculation::Execute(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	if (OnK2_Execute)
	{
		OnK2_Execute(ExecutionParams, OutExecutionOutput);
		return;
	}

	// Base implementation is a no-op — subclasses override
}
