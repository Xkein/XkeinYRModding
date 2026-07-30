#include "xkein/GameplayAbilities/gameplay_effect_execution_calculation.h"

void GameplayEffectExecutionCalculation::Execute(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	if (OnK2_Execute.IsBound())
	{
		OnK2_Execute.Execute(const_cast<GameplayEffectExecutionCalculation*>(this), ExecutionParams, OutExecutionOutput);
		return;
	}

	// Base implementation is a no-op — subclasses override
}
