#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/gameplay_effect_aggregator.h"
#include "xkein/GameplayAbilities/gameplay_effect_calculation.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "core/tool/delegate.h"
#include <optional>

class AbilitySystemComponent;

/**
 * Base class for auto-generated magnitude calculations that compute
 * a modifier's magnitude from a captured attribute.
 *
 * Subclass and override CalculateBaseMagnitude() or bind OnK2_CalculateBaseMagnitude
 * in script to provide custom computation.
 *
 * GetCapturedAttributeMagnitude() is a helper that looks up an attribute's
 * current value from the appropriate AbilitySystemComponent via the spec's context.
 */
CLASS(BindJs)
class GameplayModMagnitudeCalculation : public GameplayEffectCalculation
{
public:
	GameplayModMagnitudeCalculation() = default;
	virtual ~GameplayModMagnitudeCalculation() = default;

	/**
	 * Calculate the base magnitude for the gameplay effect spec.
	 * Override in native subclasses or leave for script (OnK2_CalculateBaseMagnitude).
	 *
	 * @param Spec The gameplay effect spec providing context (level, tags, set-by-caller values, etc.)
	 * @return The computed base magnitude
	 */
	virtual float CalculateBaseMagnitude(const GameplayEffectSpec& Spec) const;

	/**
	 * Helper to retrieve the captured magnitude of an attribute from the
	 * appropriate AbilitySystemComponent (source or target) based on the
	 * capture definition's source field.
	 *
	 * Looks up InstigatorAbilitySystemComponent from Spec.EffectContext for Source captures.
	 * For Target captures the target ASC must be provided via the evaluation parameter context
	 * (e.g., through an execution calculation where both ASCs are available).
	 *
	 * @param Def       The attribute capture definition (attribute + source/target)
	 * @param Spec      The gameplay effect spec (provides context for source ASC)
	 * @param EvalParams Evaluation parameters (source/target tag filters)
	 * @param OutMagnitude [OUT] Filled with the captured value, or 0.0f if not found
	 * @return The captured magnitude (same as OutMagnitude)
	 */
	float GetCapturedAttributeMagnitude(
		const GameplayEffectAttributeCaptureDefinition& Def,
		const GameplayEffectSpec& Spec,
		const FAggregatorEvaluateParameters& EvalParams,
		float& OutMagnitude) const;

	/**
	 * Script-side callback for custom magnitude calculation.
	 * If set, this is called by CalculateBaseMagnitude in preference to the virtual.
	 * Signature: float(const GameplayEffectSpec& Spec)
	 */
	PROPERTY(Savegame)
	TDelegate<float(const GameplayEffectSpec&)> OnK2_CalculateBaseMagnitude;

	// ============================================================
	// SetByCaller helpers (Phase 7)
	// ============================================================

	/**
	 * Get a SetByCaller magnitude from the given spec by tag.
	 * Convenience wrapper around Spec.GetSetByCallerMagnitude(Tag, true, 0.f).
	 * @param Spec The gameplay effect spec to query
	 * @param Tag  The tag key to look up
	 * @return The SetByCaller magnitude, or 0.f if not found
	 */
	float GetSetByCallerMagnitudeByTag(const GameplayEffectSpec& Spec, const GameplayTag& Tag) const
	{
		return Spec.GetSetByCallerMagnitude(Tag, true, 0.f);
	}

	/**
	 * Get a SetByCaller magnitude from the given spec by data name.
	 * Convenience wrapper around Spec.GetSetByCallerMagnitude(Name, true, 0.f).
	 * @param Spec The gameplay effect spec to query
	 * @param Name The data name key to look up
	 * @return The SetByCaller magnitude, or 0.f if not found
	 */
	float GetSetByCallerMagnitudeByName(const GameplayEffectSpec& Spec, const StringName& Name) const
	{
		return Spec.GetSetByCallerMagnitude(Name, true, 0.f);
	}
};
