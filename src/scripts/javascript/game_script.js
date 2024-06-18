
function bindScriptComponent(scriptComponent, inst, funcName) {
    let func = inst[funcName]
    if (typeof func === "function") {
        scriptComponent[funcName] = () => func.apply(inst, arguments)
    }
}
yr.createScriptTemplate = function (scriptName) {
    let scriptExports = require(scriptName)
    let scriptTemplate = scriptExports.ScriptClass
    scriptTemplate.__constructor__ = function (ScriptComponent, YrObject) {
        let inst = new scriptTemplate(YrObject)
        bindScriptComponent(ScriptComponent, inst, "OnBeginUpdate")
        bindScriptComponent(ScriptComponent, inst, "OnEndUpdate")
    }
    return scriptTemplate
}