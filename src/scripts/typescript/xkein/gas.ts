import { AbilitySystemComponent, GameplayAbility, GameplayAbilityDefine, GameplayAbilityCreator, AttributeSet, AttributeSetDefine, AttributeSetCreator, GameplayAbilitySystem, AbilityTask, GameplayCueNotify_Static, AbilityTaskCreator } from "XkeinExt";
import { ScriptFunctionRegister, StringName } from "YrExtCore";

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

function taskLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.ability_task_creator) {
        let creator = new AbilityTaskCreator(m.ability_task_creator as (ability: GameplayAbility, asc: AbilitySystemComponent) => AbilityTask);
        persistentObjs.push(creator);
        return creator;
    }
}

export function setupGas() {
    ScriptFunctionRegister.RegisterLoader(GameplayAbilitySystem.s_ScriptFunctionCategoryAbility.c_str(), abilityLoader);
    ScriptFunctionRegister.RegisterLoader(GameplayAbilitySystem.s_ScriptFunctionCategoryAttributeSet.c_str(), attributeSetLoader);
    ScriptFunctionRegister.RegisterLoader(AbilityTask.s_ScriptFunctionCategory.c_str(), taskLoader);
}
