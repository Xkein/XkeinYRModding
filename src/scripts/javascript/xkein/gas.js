"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.setupGas = setupGas;
const XkeinExt_1 = require("XkeinExt");
function abilityLoader(name) {
    const m = require(name.c_str());
    if (m && m.ability_creator) {
        return new XkeinExt_1.GameplayAbilityCreator(m.ability_creator);
    }
}
function attributeSetLoader(name) {
    const m = require(name.c_str());
    if (m && m.attribute_set_creator) {
        return new XkeinExt_1.AttributeSetCreator(m.attribute_set_creator);
    }
}
function cueLoader(name) {
    const m = require(name.c_str());
    if (m && m.cue_static_creator) {
        return new XkeinExt_1.GameplayCueStaticCreator(m.cue_static_creator);
    }
    if (m && m.cue_actor_creator) {
        return new XkeinExt_1.GameplayCueStaticCreator(m.cue_actor_creator);
    }
}
function taskLoader(name) {
    const m = require(name.c_str());
    if (m && m.ability_task_creator) {
        return new XkeinExt_1.AbilityTaskCreator(m.ability_task_creator);
    }
}
function setupGas() {
    XkeinExt_1.ScriptFunctionRegister.RegisterLoader(XkeinExt_1.GameplayAbilitySystem.s_ScriptFunctionCategoryAbility, abilityLoader);
    XkeinExt_1.ScriptFunctionRegister.RegisterLoader(XkeinExt_1.GameplayAbilitySystem.s_ScriptFunctionCategoryAttributeSet, attributeSetLoader);
    XkeinExt_1.ScriptFunctionRegister.RegisterLoader(XkeinExt_1.GameplayAbilitySystem.s_ScriptFunctionCategoryCue, cueLoader);
    XkeinExt_1.ScriptFunctionRegister.RegisterLoader(XkeinExt_1.AbilityTask.s_ScriptFunctionCategory, taskLoader);
}
