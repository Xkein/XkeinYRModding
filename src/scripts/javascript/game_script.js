
class GameScripts
{
    constructor() {
        this.scriptables = new Map()

    }

    add(scriptable) {
        this.scriptables.set(scriptable.name, scriptable)
    }

    remove(scriptable) {
        this.scriptables.delete(scriptable.name)
    }

    get(name) {
        return this.scriptables.get(name)
    }

    getOrCreate(name) {
        var scriptable = this.get(name)
        if (scriptable)
            return scriptable

        try {
            var scriptModule = require(name)
            scriptable = new GameScriptable(name, scriptModule.script)
        } catch (error) {
            console.error(error)
        }
        if (!scriptable) {
            console.error("could not load script: " + name)
            return
        }
        this.add(scriptable)
        return scriptable
    }
}

const gameScripts = new GameScripts()

class GameScriptable
{
    constructor(name, script) {
        this.insts = new Set()
        this.name = name
        this.script = script
        script.scriptable = this
    }

    addInst(inst) {
        this.insts.add(inst)
    }

    removeInst(inst) {
        this.insts.delete(inst)
    }
}

(function (global) {
    global.gameScripts = gameScripts
    
    let iniReaderXkein = new YrExtCore.IniReader("XkeinExt.ini")
    let initScriptName = IniHelper.ReadString(iniReaderXkein, "Scripting", "InitScript")
    if (initScriptName) {
        require(initScriptName)
    }

    gameEvents.game.onRulesLoadAfterTypeData.add((yrRules, iniReader) => {
        let mapScriptName = IniHelper.ReadString(iniReader, "Basic", "JsMapScript")
        if (mapScriptName) {
            var mapScriptable = gameScripts.getOrCreate(mapScriptName)
        }
    })

    let onLoadType = (yrObjectType, iniReader) => {
        let objectScriptName = IniHelper.ReadString(iniReader, yrObjectType.m_ID, "JsScript")
        if (objectScriptName) {
            let scriptable = gameScripts.getOrCreate(objectScriptName)
            yrObjectType.__scriptable = scriptable
            if (scriptable && scriptable.script.onLoadType) {
                scriptable.script.onLoadType(yrObjectType, iniReader)
            }
        }
    }

    function get_scriptable(yrObject) {
        if (yrObject.m_Type)
            return yrObject.m_Type.__scriptable
        return null
    }

    let scriptable_add = (yrObject) => {
        let scriptable = get_scriptable(yrObject)
        if (!scriptable)
            return
        
        if (scriptable.script.onAddInst) {
            scriptable.script.onAddInst(yrObject)
        }

        scriptable.addInst(yrObject)
    }

    let scriptable_remove = (yrObject) => {
        let scriptable = get_scriptable(yrObject)
        if (!scriptable)
            return

        if (scriptable.script.onRemoveInst) {
            scriptable.script.onRemoveInst(yrObject)
        }

        scriptable.removeInst(yrObject)
    }

    gameEvents.unit.onCtor.add(scriptable_add)
    gameEvents.infantry.onCtor.add(scriptable_add)
    gameEvents.building.onCtor.add(scriptable_add)
    gameEvents.aircraft.onCtor.add(scriptable_add)
    gameEvents.bullet.onConstruct.add(scriptable_add)
    gameEvents.superWeapon.onCtor.add(scriptable_add)
    gameEvents.house.onCtor.add(scriptable_add)

    gameEvents.unit.onDtor.add(scriptable_remove)
    gameEvents.infantry.onDtor.add(scriptable_remove)
    gameEvents.building.onDtor.add(scriptable_remove)
    gameEvents.aircraft.onDtor.add(scriptable_remove)
    gameEvents.bullet.onDtor.add(scriptable_remove)
    gameEvents.superWeapon.onDtor.add(scriptable_remove)
    gameEvents.house.onDtor.add(scriptable_remove)

    gameEvents.unitType.onLoadIni.add(onLoadType)
    gameEvents.infantryType.onLoadIni.add(onLoadType)
    gameEvents.buildingType.onLoadIni.add(onLoadType)
    gameEvents.aircraftType.onLoadIni.add(onLoadType)
    gameEvents.bulletType.onLoadIni.add(onLoadType)
    gameEvents.superWeaponType.onLoadIni.add(onLoadType)
    gameEvents.houseType.onLoadIni.add(onLoadType)
}(global));
