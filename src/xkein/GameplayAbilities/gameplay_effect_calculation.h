#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include <vector>

/**
 * Base class for gameplay effect magnitude calculations that can capture
 * and act on multiple attributes. Subclass and override GetAttributeCaptureDefinitions()
 * to declare which attributes are needed for the calculation.
 */
CLASS(BindJs)
class GameplayEffectCalculation
{
public:
	GameplayEffectCalculation() = default;
	virtual ~GameplayEffectCalculation() = default;

	/** Attributes that this calculation needs to capture from source/target */
	PROPERTY()
	std::vector<GameplayEffectAttributeCaptureDefinition> RelevantAttributesToCapture;

	/** Returns the attribute capture definitions for this calculation */
	virtual const std::vector<GameplayEffectAttributeCaptureDefinition>& GetAttributeCaptureDefinitions() const;
};
