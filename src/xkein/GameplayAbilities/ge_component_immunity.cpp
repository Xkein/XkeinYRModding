#include "ge_component_immunity.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include <algorithm>

void ImmunityGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    AbilitySystemComponent* ASC = Effect.Handle.GetOwningAbilitySystemComponent();
    if (!ASC)
    {
        gLogger->error("ImmunityGEComponent: no owning ASC for active effect handle");
        return;
    }

    // Capture queries by value — the component pointer is const and may not outlive the callback
    const std::vector<FGameplayEffectQuery> Queries = ImmunityQueries;
    ActiveGameplayEffectHandle EffectHandle = Effect.Handle;

    // Register an application query that checks incoming specs against immunity queries
    auto CheckFn = [Queries, EffectHandle, ASC](
        const ActiveGameplayEffectsContainer& IncomingContainer,
        const GameplayEffectSpec& IncomingSpec) -> bool
    {
        for (const auto& Query : Queries)
        {
            if (Query.Matches(IncomingSpec))
            {
                // Find the active effect that is providing this immunity
                const ActiveGameplayEffect* ImmunityActiveGE =
                    IncomingContainer.GetActiveGameplayEffect(EffectHandle);

                // Trigger the immunity block delegate on the ASC
                ASC->OnImmunityBlockGameplayEffectDelegate.publish(IncomingSpec, ImmunityActiveGE);

                gLogger->info("ImmunityGEComponent: blocked GE application due to immunity query match");
                return false; // Block application
            }
        }
        return true; // Allow application
    };

    ASC->GameplayEffectApplicationQueries.push_back({ EffectHandle, CheckFn });

    gLogger->info("ImmunityGEComponent: registered {} immunity queries for active effect", Queries.size());
}

void ImmunityGEComponent::OnActiveGameplayEffectRemoved(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect,
    const FGameplayEffectRemovalInfo& RemovalInfo) const
{
    AbilitySystemComponent* ASC = Effect.Handle.GetOwningAbilitySystemComponent();
    if (!ASC)
    {
        return;
    }

    // Remove the application query associated with this effect
    auto& Queries = ASC->GameplayEffectApplicationQueries;
    Queries.erase(
        std::remove_if(Queries.begin(), Queries.end(),
            [&Effect](const FGameplayEffectApplicationQuery& Entry) {
                return Entry.SourceEffectHandle == Effect.Handle;
            }),
        Queries.end());
}
