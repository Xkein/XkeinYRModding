"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.setupGas = setupGas;
const XkeinExt_1 = require("XkeinExt");
const YrExtCore_1 = require("YrExtCore");
const persistentObjs = [];
function abilityLoader(name) {
    const m = require(name.c_str());
    if (m && m.ability_creator) {
        let creator = new XkeinExt_1.GameplayAbilityCreator(m.ability_creator);
        persistentObjs.push(creator);
        return creator;
    }
}
function attributeSetLoader(name) {
    const m = require(name.c_str());
    if (m && m.attribute_set_creator) {
        let creator = new XkeinExt_1.AttributeSetCreator(m.attribute_set_creator);
        persistentObjs.push(creator);
        return creator;
    }
}
function taskLoader(name) {
    const m = require(name.c_str());
    if (m && m.ability_task_creator) {
        let creator = new XkeinExt_1.AbilityTaskCreator(m.ability_task_creator);
        persistentObjs.push(creator);
        return creator;
    }
}
function setupGas() {
    YrExtCore_1.ScriptFunctionRegister.RegisterLoader(XkeinExt_1.GameplayAbilitySystem.s_ScriptFunctionCategoryAbility.c_str(), abilityLoader);
    YrExtCore_1.ScriptFunctionRegister.RegisterLoader(XkeinExt_1.GameplayAbilitySystem.s_ScriptFunctionCategoryAttributeSet.c_str(), attributeSetLoader);
    YrExtCore_1.ScriptFunctionRegister.RegisterLoader(XkeinExt_1.AbilityTask.s_ScriptFunctionCategory.c_str(), taskLoader);
}
