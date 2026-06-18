#pragma once
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"

// Forward declaration for GameplayTagQuery (not yet implemented in the project)
struct GameplayTagQuery;

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

    /** Match effects whose captured source tags contain all of these (parent hierarchy match). */
    GameplayTagContainer SourceTags;

    /** Match effects whose captured target tags contain all of these (parent hierarchy match). */
    GameplayTagContainer TargetTags;

    /** Match effects that granted abilities with these tags. Checked at ASC level. */
    GameplayTagContainer GrantedTags;

    /** Match effects that modify this specific attribute (checks Def->Modifiers). */
    GameplayAttribute ModifyingAttribute;

    /** Complex tag query for the owning ASC. nullptr skips this check. */
    const GameplayTagQuery* OwningTagQuery = nullptr;

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
            && OwningTagQuery == nullptr;
    }
};

inline bool FGameplayEffectQuery::Matches(const ActiveGameplayEffect& ActiveGE) const
{
    return Matches(ActiveGE.Spec);
}

inline bool FGameplayEffectQuery::Matches(const GameplayEffectSpec& Spec) const
{
    // EffectDef check
    if (EffectDef != nullptr && Spec.Def != EffectDef)
        return false;

    // SourceTags check — captured source tags must have all query source tags
    if (SourceTags.IsValid() && !Spec.CapturedSourceTags.HasAll(SourceTags))
        return false;

    // TargetTags check — captured target tags must have all query target tags
    if (TargetTags.IsValid() && !Spec.CapturedTargetTags.HasAll(TargetTags))
        return false;

    // ModifyingAttribute check — the effect definition must have a modifier for this attribute
    if (!ModifyingAttribute.AttributeName.IsEmpty())
    {
        if (!Spec.Def)
            return false;

        bool bFoundAttribute = false;
        for (const auto& Modifier : Spec.Def->Modifiers)
        {
            if (Modifier.Attribute.AttributeName == ModifyingAttribute.AttributeName
                && Modifier.Attribute.AttributeOwner == ModifyingAttribute.AttributeOwner)
            {
                bFoundAttribute = true;
                break;
            }
        }
        if (!bFoundAttribute)
            return false;
    }

    // GrantedTags and OwningTagQuery are ASC-level checks — handled by
    // AbilitySystemComponent::GetActiveEffects(const FGameplayEffectQuery&) overload.

    return true;
}
