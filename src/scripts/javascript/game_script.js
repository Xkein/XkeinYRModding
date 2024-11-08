
function bindScriptComponent(scriptComponent, inst, funcName) {
    let func = inst[funcName]
    if (typeof func === "function") {
        scriptComponent[`m${funcName}`] = (...args) => func.apply(inst, args)
    }
}
yr.createScriptTemplate = function (scriptName) {
    let scriptExports = require(scriptName)
    let scriptTemplate = scriptExports.ScriptClass
    scriptTemplate.__constructor__ = function (ScriptComponent, YrObject) {
        let inst = new scriptTemplate(YrObject)
        YrObject.scriptInst = inst
        bindScriptComponent(ScriptComponent, inst, "OnDtor")
        bindScriptComponent(ScriptComponent, inst, "OnBeginUpdate")
        bindScriptComponent(ScriptComponent, inst, "OnEndUpdate")
        bindScriptComponent(ScriptComponent, inst, "OnSave")
        bindScriptComponent(ScriptComponent, inst, "OnLoad")
        bindScriptComponent(ScriptComponent, inst, "OnReceiveDamage")
        bindScriptComponent(ScriptComponent, inst, "OnFire")
        bindScriptComponent(ScriptComponent, inst, "OnDetonate")
        bindScriptComponent(ScriptComponent, inst, "OnLaunch")
        bindScriptComponent(ScriptComponent, inst, "OnCollisionEnter")
        bindScriptComponent(ScriptComponent, inst, "OnCollisionPersist")
        bindScriptComponent(ScriptComponent, inst, "OnCollisionExit")
    }
    return scriptTemplate
}