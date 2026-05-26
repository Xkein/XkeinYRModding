#include "gameplay_tag.h"

void GameplayTagContainer::AddTag(const GameplayTag& TagToAdd)
{
    // add unique - use exact match for deduplication
    if (!HasTagExact(TagToAdd))
    {
        GameplayTags.push_back(TagToAdd);
    }
}

bool GameplayTagContainer::RemoveTag(const GameplayTag& TagToRemove)
{
    auto iter = std::find(GameplayTags.begin(), GameplayTags.end(), TagToRemove);
    if (iter != GameplayTags.end())
    {
        GameplayTags.erase(iter);
        return true;
    }
    return false;
}

bool GameplayTagRequirements::RequirementsMet(const GameplayTagContainer& Container) const
{
    const bool bAllRequiredTagsPresent = std::all_of(
        RequireTags.GameplayTags.begin(),
        RequireTags.GameplayTags.end(),
        [&Container](const GameplayTag& Tag)
        {
            return Container.HasTag(Tag);
        });

    if (!bAllRequiredTagsPresent)
    {
        return false;
    }

    const bool bAnyIgnoredTagPresent = std::any_of(
        IgnoreTags.GameplayTags.begin(),
        IgnoreTags.GameplayTags.end(),
        [&Container](const GameplayTag& Tag)
        {
            return Container.HasTag(Tag);
        });

    if (bAnyIgnoredTagPresent)
    {
        return false;
    }

    // TagQuery provides complex AND/OR/NOT logic on top of RequireTags/IgnoreTags
    if (!TagQuery.Matches(Container))
    {
        return false;
    }

    return true;
}

bool GameplayTagRequirements::IsEmpty() const
{
    return RequireTags.GameplayTags.empty() && IgnoreTags.GameplayTags.empty();
}

// ---- GameplayTagQuery ----

bool GameplayTagQuery::EvaluateExpression(int32 ExprIndex, const GameplayTagContainer& Container) const
{
    if (ExprIndex < 0 || ExprIndex >= static_cast<int32>(Expressions.size()))
        return true; // empty or out-of-range vacuously matches

    const auto& Expr = Expressions[ExprIndex];

    switch (Expr.ExprType)
    {
    // --- Leaf nodes: check against TagTokens ---
    case EGameplayTagQueryExprType::AnyTagsMatch:
        for (int32 i = 0; i < Expr.Count; ++i)
            if (Container.HasTag(TagTokens[Expr.StartIndex + i]))
                return true;
        return Expr.Count == 0; // empty range matches

    case EGameplayTagQueryExprType::AllTagsMatch:
        for (int32 i = 0; i < Expr.Count; ++i)
            if (!Container.HasTag(TagTokens[Expr.StartIndex + i]))
                return false;
        return true;

    case EGameplayTagQueryExprType::NoTagsMatch:
        for (int32 i = 0; i < Expr.Count; ++i)
            if (Container.HasTag(TagTokens[Expr.StartIndex + i]))
                return false;
        return true;

    // --- Composite nodes: recurse into child expressions ---
    case EGameplayTagQueryExprType::AnyExprMatch:
        for (int32 i = 0; i < Expr.Count; ++i)
            if (EvaluateExpression(Expr.StartIndex + i, Container))
                return true;
        return Expr.Count == 0; // empty range matches

    case EGameplayTagQueryExprType::AllExprMatch:
        for (int32 i = 0; i < Expr.Count; ++i)
            if (!EvaluateExpression(Expr.StartIndex + i, Container))
                return false;
        return true;

    case EGameplayTagQueryExprType::NoExprMatch:
        for (int32 i = 0; i < Expr.Count; ++i)
            if (EvaluateExpression(Expr.StartIndex + i, Container))
                return false;
        return true;
    }

    return false;
}

bool GameplayTagQuery::Matches(const GameplayTagContainer& Container) const
{
    if (Expressions.empty())
        return true; // empty query always matches

    // Root is always the first expression
    return EvaluateExpression(0, Container);
}

GameplayTagQuery GameplayTagQuery::MakeQuery_MatchAnyTagsMatch(const GameplayTagContainer& InTags)
{
    GameplayTagQuery Query;
    Query.TagTokens = InTags.GameplayTags;

    FGameplayTagQueryExpression Expr;
    Expr.ExprType = EGameplayTagQueryExprType::AnyTagsMatch;
    Expr.StartIndex = 0;
    Expr.Count = static_cast<int32>(Query.TagTokens.size());
    Query.Expressions.push_back(Expr);

    return Query;
}

GameplayTagQuery GameplayTagQuery::MakeQuery_MatchAllTagsMatch(const GameplayTagContainer& InTags)
{
    GameplayTagQuery Query;
    Query.TagTokens = InTags.GameplayTags;

    FGameplayTagQueryExpression Expr;
    Expr.ExprType = EGameplayTagQueryExprType::AllTagsMatch;
    Expr.StartIndex = 0;
    Expr.Count = static_cast<int32>(Query.TagTokens.size());
    Query.Expressions.push_back(Expr);

    return Query;
}
