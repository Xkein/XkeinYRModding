import { IniReader, YrBulletConstructEvent, YrBulletTypeLoadIniEvent, YrHouseTypeLoadIniEvent, YrRulesLoadAfterTypeDataEvent, YrSuperWeaponTypeLoadIniEvent, YrTechnoTypeLoadIniEvent } from "YrExtCore"
import { IniHelper } from "./ini_helper"
import { AbstractTypeClass, CCINIClass } from "YRpp";
import { gameEvents } from "./game_event";

class GameScripts
{
    scriptables: Map<string, GameScriptable>;
    constructor() {
        this.scriptables = new Map();

    }

    add(scriptable: GameScriptable) {
        this.scriptables.set(scriptable.name, scriptable);
    }

    remove(scriptable: GameScriptable) {
        this.scriptables.delete(scriptable.name);
    }

    get(name: string) : GameScriptable | undefined {
        return this.scriptables.get(name);
    }

    getOrCreate(name: string): GameScriptable {
        var scriptable = this.get(name);
        if (scriptable)
            return scriptable;

        try {
            var scriptModule = require(name);
            scriptable = new GameScriptable(name, scriptModule.script);
        } catch (error) {
            console.error(error);
        }
        if (!scriptable) {
            console.error("could not load script: " + name);
            return undefined!;
        }
        this.add(scriptable);
        return scriptable;
    }
}

const gameScripts = new GameScripts();

class GameScriptable
{
    insts: Set<unknown>;
    name: string;
    script: any;
    constructor(name: string, script) {
        this.insts = new Set();
        this.name = name;
        this.script = script;
        script.scriptable = this;
    }

    addInst(inst) {
        this.insts.add(inst);
    }

    removeInst(inst) {
        this.insts.delete(inst);
    }
}

let iniReaderXkein = new IniReader("XkeinExt.ini");
let initScriptName = IniHelper.ReadString(iniReaderXkein, "Scripting", "InitScript");
if (initScriptName) {
    console.log(`load init script: ${initScriptName}`);
    require(initScriptName);
}

gameEvents.regitserHookEventHandler(YrRulesLoadAfterTypeDataEvent, (E) => {
    let mapScriptName = IniHelper.ReadString(new IniReader(E.m_pIni), "Basic", "JsMapScript");
    if (mapScriptName) {
        var mapScriptable = gameScripts.getOrCreate(mapScriptName);
    }
})

let onLoadType = (yrObjectType: AbstractTypeClass | any, pIni: CCINIClass) => {
    let iniReader = new IniReader(pIni);
    let objectScriptName = IniHelper.ReadString(iniReader, yrObjectType.m_ID, "JsScript");
    if (objectScriptName) {
        let scriptable = gameScripts.getOrCreate(objectScriptName);
        yrObjectType.__scriptable = scriptable;
        if (scriptable && scriptable.script.onLoadType) {
            scriptable.script.onLoadType(yrObjectType, iniReader);
        }
    }
}

function get_scriptable(yrObject) {
    if (yrObject.m_Type)
        return yrObject.m_Type.__scriptable;
    return null;
}

let scriptable_add = (yrObject) => {
    let scriptable = get_scriptable(yrObject);
    if (!scriptable)
        return;
    
    if (scriptable.script.onAddInst) {
        scriptable.script.onAddInst(yrObject);
    }

    scriptable.addInst(yrObject);
}

let scriptable_remove = (yrObject) => {
    let scriptable = get_scriptable(yrObject);
    if (!scriptable)
        return;

    if (scriptable.script.onRemoveInst) {
        scriptable.script.onRemoveInst(yrObject);
    }

    scriptable.removeInst(yrObject);
}

gameEvents.onCtor.unit.add(scriptable_add);
gameEvents.onCtor.infantry.add(scriptable_add);
gameEvents.onCtor.building.add(scriptable_add);
gameEvents.onCtor.aircraft.add(scriptable_add);
gameEvents.regitserHookEventHandler(YrBulletConstructEvent, (E) => {
    scriptable_add(E.m_pBullet);
});
gameEvents.onCtor.superWeapon.add(scriptable_add);
gameEvents.onCtor.house.add(scriptable_add);

gameEvents.onDtor.unit.add(scriptable_remove);
gameEvents.onDtor.infantry.add(scriptable_remove);
gameEvents.onDtor.building.add(scriptable_remove);
gameEvents.onDtor.aircraft.add(scriptable_remove);
gameEvents.onDtor.bullet.add(scriptable_remove);
gameEvents.onDtor.superWeapon.add(scriptable_remove);
gameEvents.onDtor.house.add(scriptable_remove);

gameEvents.regitserHookEventHandler(YrTechnoTypeLoadIniEvent, (E) => {
    onLoadType(E.m_pTechnoType, E.m_pIni)
});
gameEvents.regitserHookEventHandler(YrBulletTypeLoadIniEvent, (E) => {
    onLoadType(E.m_pBulletType, E.m_pIni)
});
gameEvents.regitserHookEventHandler(YrSuperWeaponTypeLoadIniEvent, (E) => {
    onLoadType(E.m_pSuperWeaponType, E.m_pIni)
});
gameEvents.regitserHookEventHandler(YrHouseTypeLoadIniEvent, (E) => {
    onLoadType(E.m_pHouseType, E.m_pIni)
});
