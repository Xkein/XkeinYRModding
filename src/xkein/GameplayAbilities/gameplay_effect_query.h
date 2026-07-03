#pragma once
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"

/**
 * FGameplayEffectQuery
 * Query struct for flexible active GameplayEffect filtering.
 * All match fields are optional — empty/default fields are skipped.
 * Multiple non-empty criteria combine with AND logic.
 */
CLASS(BindJs)
struct FGameplayEffectQuery
{
    /** Match by specific GameplayEffect definition. nullptr matches all. */
    const GameplayEffect* EffectDef = nullptr;

    /** Match effects whose captured source tags contain all of these (parent hierarchy match).
     *  When bSourceTagsMatchAny is true, uses HasAny instead of HasAll. */
    GameplayTagContainer SourceTags;

    /** Match effects whose captured target tags contain all of these (parent hierarchy match). */
    GameplayTagContainer TargetTags;

    /** Match effects that granted abilities with these tags. Checked at ASC level. */
    GameplayTagContainer GrantedTags;

    /** Match effects that modify this specific attribute (checks Def->Modifiers). */
    GameplayAttribute ModifyingAttribute;

    /** Tag query for the owning ASC. Empty query skips this check.
     *  At the ActiveGE level, checked against DynamicGrantedTags.
     *  At the ASC level, checked against GetOwnedGameplayTags(). */
    GameplayTagQuery OwningTagQuery;

    // ============================================================
    // Phase 7: Enhanced filtering
    // ============================================================

    /** If true, SourceTags uses HasAny matching instead of HasAll. */
    bool bSourceTagsMatchAny = false;

    /** Match effects whose definition's asset tags match these tags (checked via Def->GetAssetTags()). */
    GameplayTagContainer EffectTagsToMatch;

    /** If true, EffectTagsToMatch uses HasAny matching; otherwise uses HasAll. */
    bool bEffectTagsMatchAny = false;

    // ============================================================
    // Phase 9: GameplayTagQuery dimensions
    // ============================================================

    /** Tag query against effect definition's asset tags. Superset of EffectTagsToMatch.
     *  Empty query (= IsEmpty()) skips this check. */
    GameplayTagQuery EffectTagQuery;

    /** Tag query against captured source tags. Superset of SourceTags.
     *  Empty query (= IsEmpty()) skips this check. */
    GameplayTagQuery SourceTagQuery;

    /** Tag query against source's aggregate tags (captured source tags snapshot).
     *  Empty query (= IsEmpty()) skips this check. */
    GameplayTagQuery SourceAggregateTagQuery;

    /** Custom match delegate for project-specific filter logic. Called after all other checks pass. */
    std::function<bool(const ActiveGameplayEffect&)> CustomMatchDelegate;

    /** Ignore these specific effect handles during matching. */
    std::vector<ActiveGameplayEffectHandle> IgnoreHandles;

    /** Check if an active gameplay effect matches this query */
    bool Matches(const ActiveGameplayEffect& ActiveGE) const;

    /** Check if a gameplay effect spec matches this query */
    bool Matches(const GameplayEffectSpec& Spec) const;

    /** Returns true if no match criteria are set */
    bool IsEmpty() const
    {
        return EffectDef == nullptr
            && !SourceTags.IsValid()
            && !TargetTags.IsValid()
            && !GrantedTags.IsValid()
            && ModifyingAttribute.AttributeName.IsEmpty()
            && OwningTagQuery.IsEmpty()
            && !EffectTagsToMatch.IsValid()
            && EffectTagQuery.IsEmpty()
            && SourceTagQuery.IsEmpty()
            && SourceAggregateTagQuery.IsEmpty()
            && !CustomMatchDelegate
            && IgnoreHandles.empty();
    }

    // ============================================================
    // Static factory methods
    // ============================================================

    /** Create a query that matches effects whose captured source tags contain ANY of the given tags. */
    static FGameplayEffectQuery MakeQuery_MatchAnyOwningTags(const GameplayTagContainer& Tags)
    {
        FGameplayEffectQuery Query;
        Query.SourceTags = Tags;
        Query.bSourceTagsMatchAny = true;
        return Query;
    }

    /** Create a query that matches effects whose captured source tags contain ALL of the given tags. */
    static FGameplayEffectQuery MakeQuery_MatchAllOwningTags(const GameplayTagContainer& Tags)
    {
        FGameplayEffectQuery Query;
        Query.SourceTags = Tags;
        Query.bSourceTagsMatchAny = false;
        return Query;
    }

    /** Create a query that matches effects whose definition's asset tags contain ANY of the given tags. */
    static FGameplayEffectQuery MakeQuery_MatchAnyEffectTags(const GameplayTagContainer& Tags)
    {
        FGameplayEffectQuery Query;
        Query.EffectTagsToMatch = Tags;
        Query.bEffectTagsMatchAny = true;
        return Query;
    }

    /** Create a query that matches effects whose definition's asset tags contain ALL of the given tags. */
    static FGameplayEffectQuery MakeQuery_MatchAllEffectTags(const GameplayTagContainer& Tags)
    {
        FGameplayEffectQuery Query;
        Query.EffectTagsToMatch = Tags;
        Query.bEffectTagsMatchAny = false;
        return Query;
    }

    /** Create a query that matches effects whose dynamic granted tags do NOT contain any of the given tags.
     *  Evaluated against ActiveGE.Spec.DynamicGrantedTags via OwningTagQuery. */
    static FGameplayEffectQuery MakeQuery_MatchNoOwningTags(const GameplayTagContainer& Tags)
    {
        FGameplayEffectQuery Query;
        GameplayTagQuery Q;
        Q.TagTokens = Tags.GameplayTags;
        FGameplayTagQueryExpression Expr;
        Expr.ExprType = EGameplayTagQueryExprType::NoTagsMatch;
        Expr.StartIndex = 0;
        Expr.Count = static_cast<int32>(Q.TagTokens.size());
        Q.Expressions.push_back(Expr);
        Query.OwningTagQuery = Q;
        return Query;
    }
};

inline bool FGameplayEffectQuery::Matches(const ActiveGameplayEffect& ActiveGE) const
{
    // Check IgnoreHandles
    if (!IgnoreHandles.empty())
    {
        for (const auto& IgnoreHandle : IgnoreHandles)
        {
            if (IgnoreHandle == ActiveGE.Handle)
                return false;
        }
    }

    // Check spec-level criteria
    if (!Matches(ActiveGE.Spec))
        return false;

    // OwningTagQuery check — expression-tree evaluation against dynamic granted tags
    if (!OwningTagQuery.IsEmpty())
    {
        if (!OwningTagQuery.Matches(ActiveGE.Spec.DynamicGrantedTags))
            return false;
    }

    // Check CustomMatchDelegate
    if (CustomMatchDelegate)
    {
        if (!CustomMatchDelegate(ActiveGE))
            return false;
    }

    return true;
}

inline bool FGameplayEffectQuery::Matches(const GameplayEffectSpec& Spec) const
{
    // EffectDef check
    if (EffectDef != nullptr && Spec.Def != EffectDef)
        return false;

    // SourceTags check — captured source tags must have all/any query source tags
    if (SourceTags.IsValid())
    {
        if (bSourceTagsMatchAny)
        {
            if (!Spec.CapturedSourceTags.HasAny(SourceTags))
                return false;
        }
        else
        {
            if (!Spec.CapturedSourceTags.HasAll(SourceTags))
                return false;
        }
    }

    // TargetTags check — captured target tags must have all query target tags
    if (TargetTags.IsValid() && !Spec.CapturedTargetTags.HasAll(TargetTags))
        return false;

    // ModifyingAttribute check — the effect definition must have a modifier for this attribute
    if (!ModifyingAttribute.AttributeName.IsEmpty())
    {
        if (!Spec.Def)
            return false;

        bool bFoundAttribute = false;
        for (const auto* Modifier : Spec.Def->Modifiers)
        {
            if (Modifier->Attribute.AttributeName == ModifyingAttribute.AttributeName
                && Modifier->Attribute.AttributeOwner == ModifyingAttribute.AttributeOwner)
            {
                bFoundAttribute = true;
                break;
            }
        }
        if (!bFoundAttribute)
            return false;
    }

    // EffectTagsToMatch check — match against the effect definition's cached asset tags
    if (EffectTagsToMatch.IsValid())
    {
        if (!Spec.Def)
            return false;

        if (bEffectTagsMatchAny)
        {
            if (!Spec.Def->GetAssetTags().HasAny(EffectTagsToMatch))
                return false;
        }
        else
        {
            if (!Spec.Def->GetAssetTags().HasAll(EffectTagsToMatch))
                return false;
        }
    }

    // EffectTagQuery check — expression-tree evaluation against asset tags (superset of EffectTagsToMatch)
    if (!EffectTagQuery.IsEmpty())
    {
        if (!Spec.Def)
            return false;
        if (!EffectTagQuery.Matches(Spec.Def->GetAssetTags()))
            return false;
    }

    // SourceTagQuery check — expression-tree evaluation against captured source tags (superset of SourceTags)
    if (!SourceTagQuery.IsEmpty())
    {
        if (!SourceTagQuery.Matches(Spec.CapturedSourceTags))
            return false;
    }

    // SourceAggregateTagQuery check — expression-tree evaluation against captured source tags
    if (!SourceAggregateTagQuery.IsEmpty())
    {
        if (!SourceAggregateTagQuery.Matches(Spec.CapturedSourceTags))
            return false;
    }

    // GrantedTags and OwningTagQuery are ASC-level checks — handled by
    // AbilitySystemComponent::GetActiveEffects(const FGameplayEffectQuery&) overload.

    return true;
}
