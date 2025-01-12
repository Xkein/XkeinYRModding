
let __JsEvents = XkeinExt.JsEvents

__JsEvents.game.m_onRulesLoadAfterTypeData = () => {
    
}

let onLoadType = (yrObjectType, yrIni) => { 


}

let addScriptable = (yrObject) => {
    let scriptable
    if (yrObject.m_Type)
        scriptable = yrObject.m_Type.__scriptable
    if (!scriptable)
        return

}

let removeScriptable = (yrObject) => {
    let scriptable
    if (yrObject.m_Type)
        scriptable = yrObject.m_Type.__scriptable
    if (!scriptable)
        return

}

__JsEvents.unit.m_onCtor = addScriptable
__JsEvents.infantry.m_onCtor = addScriptable
__JsEvents.building.m_onCtor = addScriptable
__JsEvents.aircraft.m_onCtor = addScriptable
__JsEvents.bullet.m_onCtor = addScriptable
__JsEvents.superWeapon.m_onCtor = addScriptable
__JsEvents.house.m_onCtor = addScriptable

__JsEvents.unit.m_onDtor = removeScriptable
__JsEvents.infantry.m_onDtor = removeScriptable
__JsEvents.building.m_onDtor = removeScriptable
__JsEvents.aircraft.m_onDtor = removeScriptable
__JsEvents.bullet.m_onDtor = removeScriptable
__JsEvents.superWeapon.m_onDtor = removeScriptable
__JsEvents.house.m_onDtor = removeScriptable

__JsEvents.unitType.m_onLoadIni = onLoadType
__JsEvents.infantryType.m_onLoadIni = onLoadType
__JsEvents.buildingType.m_onLoadIni = onLoadType
__JsEvents.aircraftType.m_onLoadIni = onLoadType
__JsEvents.bulletType.m_onLoadIni = onLoadType
__JsEvents.superWeaponType.m_onLoadIni = onLoadType
__JsEvents.houseType.m_onLoadIni = onLoadType

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
