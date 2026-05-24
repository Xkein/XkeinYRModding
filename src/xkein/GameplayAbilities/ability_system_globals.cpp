#include "ability_system_globals.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

#include <unordered_map>
#include <vector>

void GameplayAbilitySystem::Tick()
{
    float DeltaTime = 1;
    
    // update all ability system components
    for (auto&& [entity, asc] : gEntt->view<AbilitySystemComponent>().each())
    {
        asc.ActiveGameplayEffects.Tick(DeltaTime);
    }
}

GameplayAbility* GameplayAbilitySystem::CreateAbility(const StringName& name, AbilitySystemComponent* component)
{
	GameplayAbilityCreator* creatorFunc = ScriptFunctionRegister::GetFunctionAs<GameplayAbilityCreator>(name);
	if (!creatorFunc) {
		return nullptr;
	}
	return (*creatorFunc)(component);
}

#include "yr/yr_all_events.h"

DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent)
{
    GameplayAbilitySystem::Tick();
}