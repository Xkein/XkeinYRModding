#pragma once
#include "core/reflection/reflection.h"
#include "core/tool/delegate.h"
#include "yr/serialization/serialization.h"
#include <entt/signal/sigh.hpp>

CLASS(BindJs)
struct GameplayTag
{
    bool IsValid() const
	{
		return !TagName.empty();
	}

    bool operator==(const GameplayTag& Other) const { return TagName == Other.TagName; }
    bool operator<(const GameplayTag& Other) const { return TagName < Other.TagName; }

    /**
     * Check if this tag matches TagToCheck, considering parent hierarchy.
     * "A.1".MatchesTag("A") returns true (parent match).
     * "A".MatchesTag("A.1") returns false.
     */
    bool MatchesTag(const GameplayTag& TagToCheck) const
    {
        if (!TagToCheck.IsValid() || !IsValid())
            return false;
        if (TagName == TagToCheck.TagName)
            return true;
        std::string prefix(TagToCheck.TagName);
        prefix += ".";
        if (TagName.size() > prefix.size())
            return TagName.substr(0, prefix.size()) == prefix;
        return false;
    }

    bool MatchesTagExact(const GameplayTag& TagToCheck) const
    {
        if (!TagToCheck.IsValid())
            return false;
        return TagName == TagToCheck.TagName;
    }

    int32 MatchesTagDepth(const GameplayTag& TagToCheck) const
    {
        if (!TagToCheck.IsValid() || !IsValid())
            return 0;
        if (TagName == TagToCheck.TagName)
        {
            int32 depth = 1;
            for (char c : std::string(TagName)) if (c == '.') depth++;
            return depth;
        }
        std::string prefix(TagToCheck.TagName);
        prefix += ".";
        if (TagName.size() > prefix.size() && TagName.substr(0, prefix.size()) == prefix)
        {
            int32 depth = 1;
            for (char c : std::string(TagToCheck.TagName)) if (c == '.') depth++;
            return depth;
        }
        return 0;
    }

    // Tag name
    PROPERTY()
    std::string_view TagName;
};

CLASS(BindJs)
struct GameplayTagContainer
{
	GameplayTagContainer()
	{
	}

	GameplayTagContainer(GameplayTagContainer const& Other)
	{
		*this = Other;
	}

	/** Explicit to prevent people from accidentally using the wrong type of operation */
	explicit GameplayTagContainer(const GameplayTag& Tag)
	{
		AddTag(Tag);
	}

    void AddTag(const GameplayTag& TagToAdd);

    bool RemoveTag(const GameplayTag& TagToRemove);

    bool HasTag(const GameplayTag& TagToCheck) const
    {
        if (!TagToCheck.IsValid())
            return false;
        for (const auto& OwnedTag : GameplayTags)
            if (OwnedTag.MatchesTag(TagToCheck))
                return true;
        return false;
    }

    bool HasTagExact(const GameplayTag& TagToCheck) const
    {
        if (!TagToCheck.IsValid())
            return false;
        return std::find(GameplayTags.begin(), GameplayTags.end(), TagToCheck) != GameplayTags.end();
    }

    bool HasAll(const GameplayTagContainer& Other) const
    {
        for (const auto& Tag : Other.GameplayTags)
            if (!HasTag(Tag)) return false;
        return true;
    }

    bool HasAny(const GameplayTagContainer& Other) const
    {
        for (const auto& Tag : Other.GameplayTags)
            if (HasTag(Tag)) return true;
        return false;
    }

	bool IsValid() const
	{
		return !GameplayTags.empty();
	}

    PROPERTY()
	std::vector<GameplayTag> GameplayTags;
};

/** Delegate for tag change events */
using FOnGameplayTagCountChanged = TDelegate<void(const GameplayTag&, int32 NewCount)>;

/** Encapsulate require and ignore tags */
CLASS()
struct GameplayTagRequirements
{
	/** All of these tags must be present */
	PROPERTY()
	GameplayTagContainer RequireTags;

	/** None of these tags may be present */
	PROPERTY()
	GameplayTagContainer IgnoreTags;

	/** Build up a more complex query that can't be expressed with RequireTags/IgnoreTags alone */
	// PROPERTY()
	// GameplayTagQuery TagQuery;

	/** True if all required tags and no ignore tags found */
	bool	RequirementsMet(const GameplayTagContainer& Container) const;

	/** True if neither RequireTags or IgnoreTags has any tags */
	bool	IsEmpty() const;
};

/**
 * Structure for inheritable tag containers.
 * Supports parent-child tag inheritance with Added/Removed operations.
 * Combined = Inherited - Removed + Added
 */
CLASS()
struct FInheritedTagContainer
{
    /** Combined tags = Inherited - Removed + Added */
    PROPERTY()
    GameplayTagContainer CombinedTags;

    /** Tags added on top of inherited */
    PROPERTY()
    GameplayTagContainer Added;

    /** Tags removed from inherited */
    PROPERTY()
    GameplayTagContainer Removed;

    /** Apply Added and Removed to base container to produce CombinedTags */
    void UpdateCombinedTags(const GameplayTagContainer& BaseContainer)
    {
        CombinedTags = BaseContainer;
        // Remove tags that should be removed
        for (const auto& Tag : Removed.GameplayTags)
        {
            CombinedTags.RemoveTag(Tag);
        }
        // Add tags that should be added
        for (const auto& Tag : Added.GameplayTags)
        {
            CombinedTags.AddTag(Tag);
        }
    }

    void AddTag(const GameplayTag& TagToAdd) { Added.AddTag(TagToAdd); }
    void RemoveTag(const GameplayTag& TagToRemove) { Removed.AddTag(TagToRemove); }
};
