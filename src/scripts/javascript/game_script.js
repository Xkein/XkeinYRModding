
let __JsEvents = XkeinExt.JsEvents

__JsEvents.s_game.m_onRulesLoadAfterTypeData = () => {
    
}

let onLoadType = (yrObjectType, yrIni) => { 


}

function get_scriptable(yrObject) {
    if (yrObject.m_Type)
        return  yrObject.m_Type.__scriptable
    return null
}

let addScriptable = (yrObject) => {
    let scriptable = get_scriptable(yrObject)
    if (!scriptable)
        return

}

let removeScriptable = (yrObject) => {
    let scriptable = get_scriptable(yrObject)
    if (!scriptable)
        return

}

__JsEvents.s_unit.m_onCtor = addScriptable
__JsEvents.s_infantry.m_onCtor = addScriptable
__JsEvents.s_building.m_onCtor = addScriptable
__JsEvents.s_aircraft.m_onCtor = addScriptable
__JsEvents.s_bullet.m_onCtor = addScriptable
__JsEvents.s_superWeapon.m_onCtor = addScriptable
__JsEvents.s_house.m_onCtor = addScriptable

__JsEvents.s_unit.m_onDtor = removeScriptable
__JsEvents.s_infantry.m_onDtor = removeScriptable
__JsEvents.s_building.m_onDtor = removeScriptable
__JsEvents.s_aircraft.m_onDtor = removeScriptable
__JsEvents.s_bullet.m_onDtor = removeScriptable
__JsEvents.s_superWeapon.m_onDtor = removeScriptable
__JsEvents.s_house.m_onDtor = removeScriptable

__JsEvents.s_unitType.m_onLoadIni = onLoadType
__JsEvents.s_infantryType.m_onLoadIni = onLoadType
__JsEvents.s_buildingType.m_onLoadIni = onLoadType
__JsEvents.s_aircraftType.m_onLoadIni = onLoadType
__JsEvents.s_bulletType.m_onLoadIni = onLoadType
__JsEvents.s_superWeaponType.m_onLoadIni = onLoadType
__JsEvents.s_houseType.m_onLoadIni = onLoadType

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
