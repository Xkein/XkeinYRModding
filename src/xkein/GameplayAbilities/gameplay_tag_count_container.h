#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include <map>

/**
 * Simplified equivalent of UE's FGameplayTagCountContainer.
 *
 * Design goals (mirrors UE layout/semantics as much as possible):
 * - Maintain an explicit tag container (exact tags that were added).
 * - Maintain a count map that includes parent tag propagation, so MatchesTag works.
 * - Expose query helpers similar to IGameplayTagAssetInterface usage in ASC.
 */
CLASS()
struct GameplayTagCountContainer final
{
    /** Returns explicit tags (no parent expansion). */
    [[nodiscard]] const GameplayTagContainer& GetExplicitGameplayTags() const { return ExplicitTags; }

    /** Returns number of instances for Tag (includes parent propagation). */
    int32 GetTagCount(const GameplayTag& Tag) const;

    /** Set explicit tag count to exact value (used for "SetLooseGameplayTagCount" style operations). */
    void SetTagCount(const GameplayTag& Tag, int32 NewCount);

    /** Update explicit tag count by Delta; returns true if any count changed. */
    bool UpdateTagCount(const GameplayTag& Tag, int32 Delta);

    /** Tag queries that consider parent matching, like UE. */
    bool HasMatchingGameplayTag(const GameplayTag& TagToCheck) const;
    bool HasAllMatchingGameplayTags(const GameplayTagContainer& TagContainer) const;
    bool HasAnyMatchingGameplayTags(const GameplayTagContainer& TagContainer) const;

private:
    /** Explicit tag counts (no parent expansion). */
    std::map<GameplayTag, int32> ExplicitTagCountMap;

    /** Full tag counts including parent propagation. */
    std::map<GameplayTag, int32> TagCountMap;

    /** Explicit tags with count > 0. */
    GameplayTagContainer ExplicitTags;

    /** Internal: recompute TagCountMap for Tag based on ExplicitTagCountMap deltas. */
    void ApplyDeltaToTagAndParents(const GameplayTag& Tag, int32 Delta);
};

