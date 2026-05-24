"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.setupGas = setupGas;
const XkeinExt_1 = require("XkeinExt");
function gasLoader(name) {
    const m = require(name.c_str());
    if (m && m.creator) {
        return new XkeinExt_1.GameplayAbilityCreator(m.creator);
    }
}
function setupGas() {
    XkeinExt_1.ScriptFunctionRegister.RegisterLoader(gasLoader);
}
