import { GameplayAbilityCreator, ScriptFunctionRegister } from "XkeinExt";
import { StringName } from "YrExtCore";

function gasLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.creator) {
        return new GameplayAbilityCreator(m.creator);
    }
}


export function setupGas() {
    ScriptFunctionRegister.RegisterLoader(gasLoader);
}