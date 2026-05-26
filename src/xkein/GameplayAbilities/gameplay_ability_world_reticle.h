#pragma once
#include "core/reflection/reflection.h"
#include <YRMathVector.h>
#include <GeneralStructures.h>

/**
 * GameplayAbilityWorldReticle
 *
 * Visual indicator displayed during ability targeting.
 * Shows the current target location and indicates whether it is valid.
 * Subclasses handle the actual rendering (sprite, decal, particle, etc).
 */
CLASS(BindJs)
class GameplayAbilityWorldReticle
{
public:
	virtual ~GameplayAbilityWorldReticle() = default;

	/** Called when targeting begins. Initialize and show the reticle. */
	virtual void OnTargetingStart();

	/** Called when targeting ends (either confirmed or canceled). Hide and clean up the reticle. */
	virtual void OnTargetingEnd();

	/** Set the reticle's position in world space (CoordStruct).
	 *  Called every frame during targeting to update the visual position. */
	virtual void SetReticleLocation(const CoordStruct& Location);

	/** Set whether the current target location is valid.
	 *  Visual state changes accordingly (e.g., green for valid, red for invalid). */
	virtual void SetReticleValid(bool bValid);
};
