#include "ge_component_tag_requirements.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "core/tool/delegate.h"

#include <set>

bool TagRequirementsGEComponent::CanGameplayEffectApply(
    const ActiveGameplayEffectsContainer& Container,
    const GameplayEffectSpec& Spec) const
{
    // Check application tag requirements against captured target tags.
    if (!Spec.CapturedTargetTags.HasAll(ApplicationTagRequirements.RequireTags))
    {
        return false;
    }

    if (ApplicationTagRequirements.IgnoreTags.IsValid()
        && Spec.CapturedTargetTags.HasAny(ApplicationTagRequirements.IgnoreTags))
    {
        return false;
    }

    return true;
}

bool TagRequirementsGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    AbilitySystemComponent* ASC = Container.Owner;
    if (!ASC)
    {
        return true;
    }

    const GameplayTagContainer& OwnedTags = ASC->GetOwnedGameplayTags();

    // --- OngoingTagRequirements initial check ---
    if (!OngoingTagRequirements.IsEmpty())
    {
        const bool bMet = OngoingTagRequirements.RequirementsMet(OwnedTags);
        Container.SetActiveGameplayEffectInhibit(Effect.Handle, !bMet);
    }

    // --- RemovalTagRequirements initial check ---
    if (!RemovalTagRequirements.IsEmpty())
    {
        if (RemovalTagRequirements.RequirementsMet(OwnedTags))
        {
            // Requirements already satisfied — remove the effect immediately
            ASC->RemoveActiveGameplayEffect(Effect.Handle);
            return true;
        }
    }

    // --- Collect unique tags to monitor from Ongoing and Removal requirements ---
    // We only need to watch tags referenced by either requirement set.
    std::set<GameplayTag> TagsToMonitor;

    // Collect from OngoingTagRequirements
    for (const auto& Tag : OngoingTagRequirements.RequireTags.GameplayTags)
        TagsToMonitor.insert(Tag);
    for (const auto& Tag : OngoingTagRequirements.IgnoreTags.GameplayTags)
        TagsToMonitor.insert(Tag);

    // Collect from RemovalTagRequirements
    for (const auto& Tag : RemovalTagRequirements.RequireTags.GameplayTags)
        TagsToMonitor.insert(Tag);
    for (const auto& Tag : RemovalTagRequirements.IgnoreTags.GameplayTags)
        TagsToMonitor.insert(Tag);

    if (TagsToMonitor.empty())
    {
        // No ongoing or removal requirements — nothing to monitor
        return true;
    }

    // --- Register tag event callbacks ---
    // Use RegisterAndCallGameplayTagEvent with std::function to avoid entt::sink template constraints.
    // Store (Tag, FDelegateHandle) pairs keyed by effect handle for cleanup on removal.
    ActiveGameplayEffectHandle Handle = Effect.Handle;
    std::vector<std::pair<GameplayTag, FDelegateHandle>> Handles;

    for (const auto& Tag : TagsToMonitor)
    {
        auto Callback = [this, Handle](const GameplayTag& /*ChangedTag*/, int32 /*NewCount*/)
        {
            AbilitySystemComponent* LocalASC = Handle.GetOwningAbilitySystemComponent();
            if (!LocalASC)
                return;

            const GameplayTagContainer& CurrentTags = LocalASC->GetOwnedGameplayTags();

            // Check OngoingTagRequirements: inhibit if unmet, uninhibit if met again
            if (!OngoingTagRequirements.IsEmpty())
            {
                const bool bMet = OngoingTagRequirements.RequirementsMet(CurrentTags);
                LocalASC->SetActiveGameplayEffectInhibit(Handle, !bMet);
            }

            // Check RemovalTagRequirements: remove if requirements become satisfied
            if (!RemovalTagRequirements.IsEmpty())
            {
                if (RemovalTagRequirements.RequirementsMet(CurrentTags))
                {
                    LocalASC->RemoveActiveGameplayEffect(Handle);
                }
            }
        };

        FDelegateHandle FH = ASC->RegisterAndCallGameplayTagEvent(
            Tag, Callback, EGameplayTagEventType::AnyCountChange);
        Handles.push_back({ Tag, FH });
    }

    TagEventHandles[Handle] = std::move(Handles);

    gLogger->info("TagRequirementsGEComponent: registered {} tag event callbacks for handle {}",
        TagsToMonitor.size(), Handle.Handle);
    return true;
}

void TagRequirementsGEComponent::OnActiveGameplayEffectRemoved(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect,
    const FGameplayEffectRemovalInfo& RemovalInfo) const
{
    auto It = TagEventHandles.find(Effect.Handle);
    if (It != TagEventHandles.end())
    {
        // Unregister all tag event callbacks for this effect
        AbilitySystemComponent* ASC = Container.Owner;
        if (ASC)
        {
            for (const auto& Pair : It->second)
            {
                ASC->UnregisterGameplayTagEvent(Pair.first, Pair.second);
            }
        }

        TagEventHandles.erase(It);

        gLogger->info("TagRequirementsGEComponent: unregistered tag event callbacks for handle {}",
            Effect.Handle.Handle);
    }
}
