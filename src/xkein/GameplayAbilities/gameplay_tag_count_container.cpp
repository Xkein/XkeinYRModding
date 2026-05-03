#include "gameplay_tag_count_container.h"
#include <core/string/string_tool.h>
#include <string>

static std::vector<GameplayTag> BuildParentTagsInclusive(const GameplayTag& Tag)
{
    std::vector<GameplayTag> Out;
    if (!Tag.IsValid()) return Out;

    std::string Full(Tag.TagName);
    size_t Pos = 0;
    while (true)
    {
        size_t Dot = Full.find('.', Pos);
        std::string_view View = (Dot == std::string::npos) ? std::string_view(Full) : std::string_view(Full.data(), Dot);

        GameplayTag Parent;
        Parent.TagName = get_pool_string_view(View);
        Out.push_back(Parent);

        if (Dot == std::string::npos) break;
        Pos = Dot + 1;
    }
    return Out;
}

int32 GameplayTagCountContainer::GetTagCount(const GameplayTag& Tag) const
{
    auto It = TagCountMap.find(Tag);
    return (It != TagCountMap.end()) ? It->second : 0;
}

void GameplayTagCountContainer::ApplyDeltaToTagAndParents(const GameplayTag& Tag, int32 Delta)
{
    if (!Tag.IsValid() || Delta == 0) return;

    for (const auto& Parent : BuildParentTagsInclusive(Tag))
    {
        auto It = TagCountMap.find(Parent);
        if (It != TagCountMap.end())
        {
            It->second += Delta;
        }
        else
        {
            TagCountMap[Parent] = Delta;
        }

        int32 NewCount = TagCountMap[Parent];
        if (NewCount < 0) NewCount = 0;
        TagCountMap[Parent] = NewCount;
    }
}

bool GameplayTagCountContainer::UpdateTagCount(const GameplayTag& Tag, int32 Delta)
{
    if (!Tag.IsValid() || Delta == 0) return false;

    int32 OldExplicit = 0;
    auto It = ExplicitTagCountMap.find(Tag);
    if (It != ExplicitTagCountMap.end())
    {
        OldExplicit = It->second;
        It->second += Delta;
    }
    else
    {
        ExplicitTagCountMap[Tag] = Delta;
    }

    int32 NewExplicit = ExplicitTagCountMap[Tag];
    if (NewExplicit < 0) NewExplicit = 0;
    ExplicitTagCountMap[Tag] = NewExplicit;

    // Maintain explicit tag list
    if (OldExplicit <= 0 && NewExplicit > 0)
    {
        ExplicitTags.AddTag(Tag);
    }
    else if (OldExplicit > 0 && NewExplicit <= 0)
    {
        ExplicitTags.RemoveTag(Tag);
    }

    // Apply delta to full count map for tag + parents.
    // Note: we apply the raw Delta, then clamp counts. This matches our simplified deterministic needs.
    ApplyDeltaToTagAndParents(Tag, Delta);

    return OldExplicit != NewExplicit;
}

void GameplayTagCountContainer::SetTagCount(const GameplayTag& Tag, int32 NewCount)
{
    if (!Tag.IsValid()) return;
    if (NewCount < 0) NewCount = 0;

    int32 OldCount = 0;
    auto It = ExplicitTagCountMap.find(Tag);
    if (It != ExplicitTagCountMap.end())
    {
        OldCount = It->second;
    }

    int32 Delta = NewCount - OldCount;
    if (Delta == 0) return;

    UpdateTagCount(Tag, Delta);
}

bool GameplayTagCountContainer::HasMatchingGameplayTag(const GameplayTag& TagToCheck) const
{
    return GetTagCount(TagToCheck) > 0;
}

bool GameplayTagCountContainer::HasAllMatchingGameplayTags(const GameplayTagContainer& TagContainer) const
{
    if (!TagContainer.IsValid()) return true;
    for (const auto& Tag : TagContainer.GameplayTags)
    {
        if (!HasMatchingGameplayTag(Tag)) return false;
    }
    return true;
}

bool GameplayTagCountContainer::HasAnyMatchingGameplayTags(const GameplayTagContainer& TagContainer) const
{
    if (!TagContainer.IsValid()) return false;
    for (const auto& Tag : TagContainer.GameplayTags)
    {
        if (HasMatchingGameplayTag(Tag)) return true;
    }
    return false;
}

