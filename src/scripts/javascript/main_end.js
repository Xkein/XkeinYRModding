"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const YrExtCore_1 = require("YrExtCore");
const game_script_1 = require("./game_script");
const gas_1 = require("./xkein/gas");
let iniReaderXkein = new YrExtCore_1.IniReader("XkeinExt.ini");
(0, game_script_1.loadSectionScripts)(iniReaderXkein, "JsScriptList", (scriptable) => {
    console.log(`load init script: ${scriptable.name}`);
});
(0, gas_1.setupGas)();
