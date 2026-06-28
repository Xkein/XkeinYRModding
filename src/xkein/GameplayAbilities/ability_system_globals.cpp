#include "ability_system_globals.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/gameplay_cue_manager.h"

#include <unordered_map>
#include <vector>

StringName GameplayAbilitySystem::ScriptFunctionCategoryAbility = "GameplayAbility";
StringName GameplayAbilitySystem::ScriptFunctionCategoryAttributeSet = "AttributeSet";

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
    if (name.IsEmpty()) {
        // this gameplay ability use default creator, which just creates a new instance of the GameplayAbility class.
        // This is useful for simple abilities that don't need custom logic in their constructor.
        return new GameplayAbility();
    }
	GameplayAbilityCreator* creatorFunc = ScriptFunctionRegister::GetFunctionAs<GameplayAbilityCreator>(ScriptFunctionCategoryAbility, name);
	if (!creatorFunc) {
        gLogger->error("[GAS] could not create ability {}, no creator!", define->AbilityCreator.c_str());
		return nullptr;
	}

    // When no owning component is given, the ability is a global template (like a Class Default Object):
    // create it once per creator name and return the cached instance on subsequent calls.
    // When a component is given, always create a fresh per-actor instance and skip the cache.
    if (!component) {
        static std::unordered_map<StringName, GameplayAbility*> GlobalAbilityCache;
        auto it = GlobalAbilityCache.find(name);
        if (it != GlobalAbilityCache.end()) {
            return it->second;
        }
        GameplayAbility* Ability = (*creatorFunc)(define, component);
        GlobalAbilityCache[name] = Ability;
        return Ability;
    }

	return (*creatorFunc)(define, component);
}

AttributeSet* GameplayAbilitySystem::CreateAttributeSet(const StringName& name, AttributeSetDefine* define, AbilitySystemComponent* component)
{
    if (name.IsEmpty()) {
        AttributeSet* NewSet = new AttributeSet();
        for (const GameplayAttribute& Attr : define->Attributes)
        {
            NewSet->AddAttributeData(&Attr);
        }
        return NewSet;
    }
	AttributeSetCreator* creatorFunc = ScriptFunctionRegister::GetFunctionAs<AttributeSetCreator>(ScriptFunctionCategoryAttributeSet, name);
	if (!creatorFunc) {
        gLogger->error("[GAS] could not create attribute set {}, no creator!", define->AttributeSetCreator.c_str());
		return nullptr;
	}
	return (*creatorFunc)(define, component);
}

GameplayCueManager* GameplayAbilitySystem::GetCueManager()
{
    return GameplayCueManager::Get();
}

#include "yr/yr_all_events.h"

DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent)
{
    GameplayAbilitySystem::Tick();
}