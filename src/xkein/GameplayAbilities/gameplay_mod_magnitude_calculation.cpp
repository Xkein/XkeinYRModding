#include "xkein/GameplayAbilities/gameplay_mod_magnitude_calculation.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

float GameplayModMagnitudeCalculation::CalculateBaseMagnitude(const GameplayEffectSpec& Spec) const
{
	if (OnK2_CalculateBaseMagnitude.IsBound())
	{
		return OnK2_CalculateBaseMagnitude.Execute(Spec);
	}

	// Base implementation returns 0 — subclasses override
	return 0.0f;
}

float GameplayModMagnitudeCalculation::GetCapturedAttributeMagnitude(
	const GameplayEffectAttributeCaptureDefinition& Def,
	const GameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvalParams,
	float& OutMagnitude) const
{
	OutMagnitude = 0.0f;

	// Determine which ASC to read from based on the capture source
	AbilitySystemComponent* TargetASC = nullptr;

	if (Def.AttributeSource == EGameplayEffectAttributeCaptureSource::Source)
	{
		// Source ASC is available from the effect context
		if (Spec.EffectContext.Data)
		{
			TargetASC = Spec.EffectContext.Data->InstigatorAbilitySystemComponent;
		}
	}
	// For Target captures: the target ASC is not stored on the spec itself.
	// Callers (e.g., execution calculations) that have target ASC access should
	// use their own attribute lookup instead.

	if (!TargetASC)
	{
		return 0.0f;
	}

	// Look up the numeric value from the ASC's spawned attribute sets
	float Value = TargetASC->GetNumericAttribute(Def.AttributeToCapture);
	OutMagnitude = Value;
	return Value;
}
