#include "ability_system_globals.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/gameplay_cue_manager.h"

#include <unordered_map>
#include <vector>

void GameplayAbilitySystem::Tick()
{
    float DeltaTime = 1;
    
    // update all ability system components
    for (auto&& [entity, asc] : gEntt->view<AbilitySystemComponent>().each())
    {
        asc.Tick(DeltaTime);
    }
}

GameplayAbility* GameplayAbilitySystem::CreateAbility(const StringName& name, GameplayAbilityDefine* define, AbilitySystemComponent* component)
{
	GameplayAbilityCreator* creatorFunc = ScriptFunctionRegister::GetFunctionAs<GameplayAbilityCreator>(name);
	if (!creatorFunc) {
		return nullptr;
	}
	return (*creatorFunc)(define, component);
}

AttributeSet* GameplayAbilitySystem::CreateAttributeSet(const StringName& name, AttributeSetDefine* define, AbilitySystemComponent* component)
{
	AttributeSetCreator* creatorFunc = ScriptFunctionRegister::GetFunctionAs<AttributeSetCreator>(name);
	if (!creatorFunc) {
		return nullptr;
	}
	return (*creatorFunc)(define, component);
}

GameplayCueManager* GameplayAbilitySystem::GetCueManager()
{
    return GameplayCueManager::Get();
}

GameplayCueNotify_Static* GameplayAbilitySystem::CreateCueStatic(const StringName& name)
{
    GameplayCueStaticCreator* creatorFunc = ScriptFunctionRegister::GetFunctionAs<GameplayCueStaticCreator>(name);
    if (!creatorFunc) {
        return nullptr;
    }
    return (*creatorFunc)();
}

GameplayCueNotify_Actor* GameplayAbilitySystem::CreateCueActor(const StringName& name)
{
    GameplayCueActorCreator* creatorFunc = ScriptFunctionRegister::GetFunctionAs<GameplayCueActorCreator>(name);
    if (!creatorFunc) {
        return nullptr;
    }
    return (*creatorFunc)();
}

#include "yr/yr_all_events.h"

DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent)
{
    GameplayAbilitySystem::Tick();
}