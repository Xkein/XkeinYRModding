#include "xkein/GameplayAbilities/gameplay_effect_calculation.h"

const std::vector<GameplayEffectAttributeCaptureDefinition>& GameplayEffectCalculation::GetAttributeCaptureDefinitions() const
{
	return RelevantAttributesToCapture;
}
