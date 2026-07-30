#pragma once
#include "core/reflection/reflection.h"
#include "core/tool/delegate.h"
#include "core/string/string_name.h"
#include "yr/serialization/serialization.h"
#include <entt/signal/sigh.hpp>

class AbilitySystemComponent;

CLASS(BindJs, AutoSavegame)
struct GameplayTag
{
    bool IsValid() const
	{
		return !TagName.IsEmpty();
	}

    bool operator==(const GameplayTag& Other) const { return TagName == Other.TagName; }
    bool operator<(const GameplayTag& Other) const { return std::string_view(TagName) < std::string_view(Other.TagName); }

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
        std::string_view ThisView = TagName;
        std::string_view CheckView = TagToCheck.TagName;
        std::string prefix(CheckView);
        prefix += ".";
        if (ThisView.size() > prefix.size())
            return ThisView.substr(0, prefix.size()) == prefix;
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
            for (char c : std::string_view(TagName)) if (c == '.') depth++;
            return depth;
        }
        std::string_view ThisView = TagName;
        std::string_view CheckView = TagToCheck.TagName;
        std::string prefix(CheckView);
        prefix += ".";
        if (ThisView.size() > prefix.size() && ThisView.substr(0, prefix.size()) == prefix)
        {
            int32 depth = 1;
            for (char c : CheckView) if (c == '.') depth++;
            return depth;
        }
        return 0;
    }

    // Tag name - using StringName for pooled string storage and O(1) pointer-based comparison
    PROPERTY(Savegame)
    StringName TagName;
};

CLASS(BindJs, AutoSavegame)
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

    bool IsEmpty() const
    {
        return GameplayTags.empty();
    }

    PROPERTY(Savegame)
	std::vector<GameplayTag> GameplayTags;
};

/** Delegate for tag change events */
using FOnGameplayTagCountChanged = TMulticastDelegate<void(AbilitySystemComponent*, const GameplayTag&, int32 NewCount)>;

/**
 * Structure for inheritable tag containers.
 * Supports parent-child tag inheritance with Added/Removed operations.
 * Combined = Inherited - Removed + Added
 */
CLASS(IniComponent)
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

/** Type of expression node in a GameplayTagQuery expression tree */
ENUM()
enum EGameplayTagQueryExprType : int
{
    /** True if any of the referenced tags match */
    AnyTagsMatch,

    /** True if all of the referenced tags match */
    AllTagsMatch,

    /** True if none of the referenced tags match */
    NoTagsMatch,

    /** True if any of the referenced child expressions match */
    AnyExprMatch,

    /** True if all of the referenced child expressions match */
    AllExprMatch,

    /** True if none of the referenced child expressions match */
    NoExprMatch
};

/**
 * A single node in the GameplayTagQuery expression tree.
 * Leaf nodes (AnyTagsMatch, AllTagsMatch, NoTagsMatch) index into TagTokens.
 * Composite nodes (AnyExprMatch, AllExprMatch, NoExprMatch) index into child expressions.
 */
struct FGameplayTagQueryExpression
{
    EGameplayTagQueryExprType ExprType;
    int32 StartIndex = 0;
    int32 Count = 0;
};

/**
 * Expression tree for complex tag queries.
 * Supports AND/OR/NOT logic that cannot be expressed with RequireTags/IgnoreTags alone.
 * Node types index into TagTokens (leaf) or Expressions (composite) via StartIndex + Count.
 */
CLASS(BindJs)
struct GameplayTagQuery
{
    /** Evaluate this query against the given tag container */
    bool Matches(const GameplayTagContainer& Container) const;

    /** True if this query has no expressions (vacuously matches everything) */
    bool IsEmpty() const
    {
        return Expressions.empty();
    }

    /** Build a query that matches when ANY of InTags is present */
    static GameplayTagQuery MakeQuery_MatchAnyTagsMatch(const GameplayTagContainer& InTags);

    /** Build a query that matches when ALL of InTags are present */
    static GameplayTagQuery MakeQuery_MatchAllTagsMatch(const GameplayTagContainer& InTags);

    friend struct FGameplayEffectQuery;

private:
    bool EvaluateExpression(int32 ExprIndex, const GameplayTagContainer& Container) const;

    /** Pool of all tags referenced by expression nodes */
    std::vector<GameplayTag> TagTokens;

    /** Expression nodes forming the tree. First node is the root. */
    std::vector<FGameplayTagQueryExpression> Expressions;
};

/** Encapsulate require and ignore tags */
CLASS(BindJs, IniComponent, IniAutoLoad)
struct GameplayTagRequirements
{
	/** All of these tags must be present */
	PROPERTY()
	GameplayTagContainer RequireTags;

	/** None of these tags may be present */
	PROPERTY()
	GameplayTagContainer IgnoreTags;

	/** Build up a more complex query that can't be expressed with RequireTags/IgnoreTags alone */
	PROPERTY()
	GameplayTagQuery TagQuery;

	/** True if all required tags and no ignore tags found */
	bool	RequirementsMet(const GameplayTagContainer& Container) const;

	/** True if neither RequireTags or IgnoreTags has any tags */
	bool	IsEmpty() const;
};
