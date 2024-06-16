
yr.createScriptTemplate = function (scriptName) {
    let scriptExports = require(scriptName)
    let scriptTemplate = scriptExports.ScriptClass
    scriptTemplate.__constructor__ = function (ScriptComponent, YrObject) {
        let inst = new scriptTemplate(ScriptComponent, YrObject)
        if (typeof inst.OnBeginUpdate === "function") {
            ScriptComponent.BeginUpdate = inst.OnBeginUpdate
        }
        if (typeof inst.OnEndUpdate === "function") {
            ScriptComponent.BeginUpdate = inst.OnEndUpdate
        }
    }
    return scriptTemplate
}