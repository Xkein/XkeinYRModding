import { AbilitySystemComponent, GameplayAbility, GameplayAbilityDefine, GameplayAbilityCreator, ScriptFunctionRegister, AttributeSet, AttributeSetDefine, AttributeSetCreator, GameplayAbilitySystem, AbilityTask, GameplayCueStaticCreator, GameplayCueNotify_Static, AbilityTaskCreator } from "XkeinExt";
import { StringName } from "YrExtCore";

function abilityLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.ability_creator) {
        return new GameplayAbilityCreator(m.ability_creator as (define: GameplayAbilityDefine, com: AbilitySystemComponent) => GameplayAbility);
    }
}

function attributeSetLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.attribute_set_creator) {
        return new AttributeSetCreator(m.attribute_set_creator as (define: AttributeSetDefine, com: AbilitySystemComponent) => AttributeSet);
    }
}

function cueLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.cue_static_creator) {
        return new GameplayCueStaticCreator(m.cue_static_creator as () => GameplayCueNotify_Static);
    }
    if (m && m.cue_actor_creator) {
        return new GameplayCueStaticCreator(m.cue_actor_creator as () => GameplayCueNotify_Static);
    }
}

function taskLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.ability_task_creator) {
        return new AbilityTaskCreator(m.ability_task_creator as (ability: GameplayAbility, asc: AbilitySystemComponent) => AbilityTask);
    }
}

export function setupGas() {
    ScriptFunctionRegister.RegisterLoader(GameplayAbilitySystem.s_ScriptFunctionCategoryAbility, abilityLoader);
    ScriptFunctionRegister.RegisterLoader(GameplayAbilitySystem.s_ScriptFunctionCategoryAttributeSet, attributeSetLoader);
    ScriptFunctionRegister.RegisterLoader(GameplayAbilitySystem.s_ScriptFunctionCategoryCue, cueLoader);
    ScriptFunctionRegister.RegisterLoader(AbilityTask.s_ScriptFunctionCategory, taskLoader);
}
