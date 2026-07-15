#pragma once
#include "core/reflection/reflection.h"
#include <entt/entity/fwd.hpp>
#include <YRMathVector.h>
#include <GeneralStructures.h>
#include "xkein/GameplayAbilities/gameplay_ability_target_types.h"
#include "core/tool/delegate.h"

class GameplayAbility;

/**
 * EGameplayTargetingConfirmation
 *
 * Defines how targeting confirmation is handled for a TargetActor.
 */
ENUM(BindJs)
enum class EGameplayTargetingConfirmation : uint8
{
	/** Target is immediately confirmed when a valid target is selected */
	Instant,

	/** Target selection must be explicitly confirmed by the user (e.g., left-click to target, right-click to confirm) */
	UserConfirmed,

	/** Targeting confirmation is handled by custom logic, including script-defined behavior */
	Custom,
};

/**
 * GameplayAbilityTargetActor
 *
 * Base class for actors that handle ability targeting.
 * Spawned by abilities that require player input to select targets.
 * Subclasses implement specific targeting behaviors (line trace, radius, ground placement, etc).
 */
CLASS(BindJs)
class GameplayAbilityTargetActor
{
public:
	virtual ~GameplayAbilityTargetActor() = default;

	/** Begin targeting. Stores the owning ability and prepares targeting state. */
	virtual void StartTargeting(GameplayAbility* Ability);

	/** Confirm the current targeting selection. Collects targets and fires OnTargetDataReady. */
	virtual void ConfirmTargeting();

	/** Cancel targeting without executing the ability. Cleans up state. */
	virtual void CancelTargeting();

	/** Callback fired when target data is ready (either instant or after confirmation).
	 *  Consumed by AbilityTask_WaitTargetData or the owning ability. */
	PROPERTY(Savegame)
	TDelegate<void(const GameplayAbilityTargetDataHandle&)> OnTargetDataReady;

// protected:
	/** The ability that owns this target actor. Set by StartTargeting. */
	PROPERTY()
	GameplayAbility* OwningAbility = nullptr;

	/** Accumulated target data collected during targeting */
	PROPERTY()
	GameplayAbilityTargetDataHandle TargetDataHandle;
};

// ----------------------------------------------------------------------------
//	TargetActor Subclasses
// ----------------------------------------------------------------------------

/**
 * GameplayAbilityTargetActor_LineTrace
 *
 * Performs a ray trace along a direction from the source actor.
 * Hits cells along the trace and returns the first valid target.
 * YR adaptation: traces through the tile grid, checking occupancy.
 */
CLASS(BindJs)
class GameplayAbilityTargetActor_LineTrace : public GameplayAbilityTargetActor
{
public:
	virtual void StartTargeting(GameplayAbility* Ability) override;

	/** Direction of the trace in world space */
	PROPERTY()
	CoordStruct TraceDirection;

	/** Maximum range of the trace (world-space distance) */
	PROPERTY()
	float MaxRange = 10.0f;
};

/**
 * GameplayAbilityTargetActor_Radius
 *
 * Selects all targets within a circular area centered on a point.
 * Radius is specified in cell coordinates (CellStruct distance).
 * YR adaptation: uses the tile-based grid for area queries.
 */
CLASS(BindJs)
class GameplayAbilityTargetActor_Radius : public GameplayAbilityTargetActor
{
public:
	virtual void StartTargeting(GameplayAbility* Ability) override;

	/** Radius of the targeting area, measured in cell coordinates */
	PROPERTY()
	CellStruct Radius;
};

/**
 * GameplayAbilityTargetActor_GroundTrace
 *
 * Performs a ground trace to select a rectangular area on the grid.
 * Used for placement abilities (e.g., building placement, airstrike zones).
 * YR adaptation: selects cells within the defined area on the tile grid.
 */
CLASS(BindJs)
class GameplayAbilityTargetActor_GroundTrace : public GameplayAbilityTargetActor
{
public:
	virtual void StartTargeting(GameplayAbility* Ability) override;

	/** World-space center of the ground selection area */
	PROPERTY()
	CoordStruct GroundLocation;

	/** Half-extents of the selection area in cell coordinates */
	PROPERTY()
	CellStruct AreaExtents;
};

/**
 * GameplayAbilityTargetActor_ActorPlacement
 *
 * Spawns an entity at the target location.
 * Used for summon/construction abilities that create game objects.
 * YR adaptation: places entities at CoordStruct positions in the game world.
 */
CLASS(BindJs)
class GameplayAbilityTargetActor_ActorPlacement : public GameplayAbilityTargetActor
{
public:
	virtual void StartTargeting(GameplayAbility* Ability) override;

	/** World-space location at which to place the actor */
	PROPERTY()
	CoordStruct PlacementLocation;
};
