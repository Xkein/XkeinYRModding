import { AbilitySystemComponent, GameplayAbility, GameplayAbilityDefine, GameplayAbilityCreator, ScriptFunctionRegister, AttributeSet, AttributeSetDefine, AttributeSetCreator, GameplayAbilitySystem, AbilityTask, GameplayCueStaticCreator, GameplayCueNotify_Static, AbilityTaskCreator } from "XkeinExt";
import { StringName } from "YrExtCore";

const persistentObjs : any[] = [];

function abilityLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.ability_creator) {
        let creator = new GameplayAbilityCreator(m.ability_creator as (define: GameplayAbilityDefine, com: AbilitySystemComponent) => GameplayAbility);
        persistentObjs.push(creator);
        return creator;
    }
}

function attributeSetLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.attribute_set_creator) {
        let creator = new AttributeSetCreator(m.attribute_set_creator as (define: AttributeSetDefine, com: AbilitySystemComponent) => AttributeSet);
        persistentObjs.push(creator);
        return creator;
    }
}

function cueLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.cue_static_creator) {
        let creator = new GameplayCueStaticCreator(m.cue_static_creator as () => GameplayCueNotify_Static);
        persistentObjs.push(creator);
        return creator;
    }
    if (m && m.cue_actor_creator) {
        let creator = new GameplayCueStaticCreator(m.cue_actor_creator as () => GameplayCueNotify_Static);
        persistentObjs.push(creator);
        return creator;
    }
}

function taskLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.ability_task_creator) {
        let creator = new AbilityTaskCreator(m.ability_task_creator as (ability: GameplayAbility, asc: AbilitySystemComponent) => AbilityTask);
        persistentObjs.push(creator);
        return creator;
    }
}

export function setupGas() {
    ScriptFunctionRegister.RegisterLoader(GameplayAbilitySystem.s_ScriptFunctionCategoryAbility, abilityLoader);
    ScriptFunctionRegister.RegisterLoader(GameplayAbilitySystem.s_ScriptFunctionCategoryAttributeSet, attributeSetLoader);
    ScriptFunctionRegister.RegisterLoader(GameplayAbilitySystem.s_ScriptFunctionCategoryCue, cueLoader);
    ScriptFunctionRegister.RegisterLoader(AbilityTask.s_ScriptFunctionCategory, taskLoader);
}
