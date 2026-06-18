#pragma once
#include "core/reflection/reflection.h"
#include "runtime/platform/platform.h"
#include <entt/entity/fwd.hpp>
#include <YRMathVector.h>
#include <GeneralStructures.h>
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include <vector>

/**
 * GameplayAbilityTargetData
 *
 * Base polymorphic type for passing target data into GameplayAbilities.
 * Subclasses define the specific type of target information
 * (single hit, actor array, location, etc).
 */
CLASS(BindJs)
struct GameplayAbilityTargetData
{
	virtual ~GameplayAbilityTargetData() = default;
};

/**
 * GameplayAbilityTargetData_SingleTargetHit
 *
 * Stores the result of a single trace/query hit:
 * the world-space hit location and the entity that was hit.
 */
CLASS(BindJs)
struct GameplayAbilityTargetData_SingleTargetHit : public GameplayAbilityTargetData
{
	PROPERTY()
	CoordStruct HitLocation;

	PROPERTY()
	entt::entity HitActor = entt::null;
};

/**
 * GameplayAbilityTargetData_ActorArray
 *
 * Stores an array of target actors. Used by area-of-effect and
 * multi-target abilities that need to enumerate all affected entities.
 */
CLASS(BindJs)
struct GameplayAbilityTargetData_ActorArray : public GameplayAbilityTargetData
{
	PROPERTY()
	std::vector<entt::entity> TargetActors;
};

/**
 * GameplayAbilityTargetData_LocationInfo
 *
 * Stores a single world-space location as a target.
 * Used by ground-targeted abilities (e.g., artillery strikes).
 */
CLASS(BindJs)
struct GameplayAbilityTargetData_LocationInfo : public GameplayAbilityTargetData
{
	PROPERTY()
	CoordStruct TargetLocation;
};

/**
 * FGameplayAbilityTargetDataFilter
 *
 * Filter used to constrain target data queries.
 * Targets must have all RequiredTags and none of the IgnoreTags.
 * SelfActor can be used to exclude self from results.
 */
CLASS()
struct FGameplayAbilityTargetDataFilter
{
	/** Tags that the target must possess */
	PROPERTY()
	GameplayTagContainer RequiredTags;

	/** Tags that the target must NOT possess */
	PROPERTY()
	GameplayTagContainer IgnoreTags;

	/** The actor performing the query (used for self-exclusion) */
	PROPERTY()
	entt::entity SelfActor = entt::null;
};

/**
 * GameplayAbilityTargetDataHandle
 *
 * Handle that owns a collection of target data pointers.
 * Used to pass target data through the ability activation pipeline.
 * Supports multiple target data entries (e.g., multi-target abilities).
 */
CLASS(BindJs)
struct GameplayAbilityTargetDataHandle
{
	GameplayAbilityTargetDataHandle() : FirstData(nullptr) {}
	GameplayAbilityTargetDataHandle(GameplayAbilityTargetData* DataPtr)
	{
		Data.push_back(DataPtr);
	}

	/** First target data pointer for quick access */
	GameplayAbilityTargetData* FirstData;

	/** All target data pointers owned by this handle */
	std::vector<GameplayAbilityTargetData*> Data;

	/** Resets handle to have no targets */
	void Clear()
	{
		Data.clear();
		FirstData = nullptr;
	}

	/** Returns number of target data entries, not number of actors/targets as target data may contain multiple actors */
	int32 Num() const
	{
		return FirstData ? std::max(1, static_cast<int32>(Data.size())) : 0;
	}

	/** Add target data to this handle. Sets FirstData if this is the first entry. */
	void Add(GameplayAbilityTargetData* NewData);
};
