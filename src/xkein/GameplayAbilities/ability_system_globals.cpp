#include "ability_system_globals.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

#include <unordered_map>
#include <vector>

namespace
{
std::vector<std::function<GameplayAbility*(AbilitySystemComponent*)>> GAbilityCreators;
std::unordered_map<std::string_view, uint> GAbilityNameToId;
}

void GameplayAbilitySystem::Tick()
{
    float DeltaTime = 1;
    
    // update all ability system components
    for (auto&& [entity, asc] : gEntt->view<AbilitySystemComponent>().each())
    {
        asc.ActiveGameplayEffects.Tick(DeltaTime);
    }
}

void GameplayAbilitySystem::RegisterAbilityCreator(std::string name, std::function<GameplayAbility*(AbilitySystemComponent* component)> creator)
{
	const auto it = GAbilityNameToId.find(std::string_view(name));
	if (it != GAbilityNameToId.end())
	{
		GAbilityCreators[it->second - 1u] = std::move(creator);
		return;
	}
	GAbilityCreators.push_back(std::move(creator));
	const uint id = static_cast<uint>(GAbilityCreators.size());
	GAbilityNameToId.emplace(std::string_view(name), id);
}

uint GameplayAbilitySystem::GetAbilityId(std::string_view name)
{
	const auto it = GAbilityNameToId.find(name);
	return it != GAbilityNameToId.end() ? it->second : 0u;
}

GameplayAbility* GameplayAbilitySystem::CreateAbility(uint id, AbilitySystemComponent* component)
{
	if (id == 0u || id > static_cast<uint>(GAbilityCreators.size()))
	{
		return nullptr;
	}
	return GAbilityCreators[id - 1u](component);
}

#include "yr/yr_all_events.h"

DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent)
{
    GameplayAbilitySystem::Tick();
}