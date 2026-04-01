import { IniReader } from "YrExtCore";
import { loadSectionScripts } from "./game_script";


let iniReaderXkein = new IniReader("XkeinExt.ini");
loadSectionScripts(iniReaderXkein, "JsScriptList", (scriptable) => {
    console.log(`load init script: ${scriptable.name}`);
});
