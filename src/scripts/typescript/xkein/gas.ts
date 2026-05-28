import { AbilitySystemComponent, GameplayAbility, GameplayAbilityDefine, GameplayAbilityCreator, ScriptFunctionRegister } from "XkeinExt";
import { StringName } from "YrExtCore";

function gasLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.creator) {
        return new GameplayAbilityCreator(m.creator as (define: GameplayAbilityDefine, com: AbilitySystemComponent) => GameplayAbility);
    }
}


export function setupGas() {
    ScriptFunctionRegister.RegisterLoader(gasLoader);
}