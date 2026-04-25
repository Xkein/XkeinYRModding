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

    return !bAnyIgnoredTagPresent;
}

bool GameplayTagRequirements::IsEmpty() const
{
    return RequireTags.GameplayTags.empty() && IgnoreTags.GameplayTags.empty();
}
