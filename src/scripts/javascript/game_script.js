"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.GetScriptableComponent = GetScriptableComponent;
exports.CreateScriptableComponent = CreateScriptableComponent;
exports.GetAllGetScriptableComponents = GetAllGetScriptableComponents;
exports.getYrObjectBlackboard = getYrObjectBlackboard;
exports.getCustomVariable = getCustomVariable;
exports.setCustomVariable = setCustomVariable;
exports.saveCustomVariables = saveCustomVariables;
exports.loadCustomVariables = loadCustomVariables;
const YrExtCore_1 = require("YrExtCore");
const ini_helper_1 = require("./ini_helper");
const game_event_1 = require("./game_event");
const serialization_1 = require("./serialization");
class GameScripts {
    scriptables;
    constructor() {
        this.scriptables = new Map();
    }
    add(scriptable) {
        this.scriptables.set(scriptable.name, scriptable);
    }
    remove(scriptable) {
        this.scriptables.delete(scriptable.name);
    }
    get(name) {
        return this.scriptables.get(name);
    }
    getOrCreate(name) {
        var scriptable = this.get(name);
        if (scriptable)
            return scriptable;
        try {
            var scriptModule = require(name);
            scriptable = new GameScriptable(name, scriptModule.script);
        }
        catch (error) {
            console.error(error);
        }
        if (!scriptable) {
            console.error("could not load script: " + name);
            return undefined;
        }
        this.add(scriptable);
        return scriptable;
    }
}
const gameScripts = new GameScripts();
class GameScriptable {
    insts;
    name;
    script;
    constructor(name, script) {
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
const emptyComponents = new Map();
function GetScriptableComponent(klass, yrObject) {
    let components = GetAllGetScriptableComponents(yrObject);
    let componentName = klass.name;
    return components[componentName];
}
function CreateScriptableComponent(klass, yrObject) {
    let owner = yrObject;
    let components = owner.__components;
    if (!components) {
        components = owner.__components = new Map();
    }
    let componentName = klass.name;
    let component = new klass();
    components[componentName] = component;
    return component;
}
function GetAllGetScriptableComponents(yrObject) {
    let owner = yrObject;
    return owner.__components ?? emptyComponents;
}
function getYrObjectBlackboard(yrObject) {
    return yrObject;
}
function getCustomVariable(blackboard, name) {
    if (blackboard.__variables) {
        return blackboard.__variables[name];
    }
    return undefined;
}
function setCustomVariable(blackboard, name, value) {
    if (!blackboard.__variables) {
        blackboard.__variables = new Map();
    }
    blackboard.__variables[name] = value;
    return value;
}
function saveCustomVariables(blackboard) {
    if (blackboard.__variables) {
        serialization_1.JsSerialization.SaveNext(blackboard.__variables.size);
        for (const [name, value] of blackboard.__variables) {
            serialization_1.JsSerialization.SaveNext(name);
            serialization_1.JsSerialization.SaveNext(value);
        }
    }
    else {
        serialization_1.JsSerialization.SaveNext(0);
    }
}
function loadCustomVariables(blackboard) {
    let variableCount = serialization_1.JsSerialization.LoadNext();
    if (variableCount > 0) {
        let variables = new Map();
        blackboard.__variables = variables;
        for (let index = 0; index < variableCount; index++) {
            let name = serialization_1.JsSerialization.LoadNext();
            let value = serialization_1.JsSerialization.LoadNext();
            variables[name] = value;
        }
    }
}
let iniReaderXkein = new YrExtCore_1.IniReader("XkeinExt.ini");
let initScriptName = ini_helper_1.IniHelper.ReadString(iniReaderXkein, "Scripting", "InitScript");
if (initScriptName) {
    console.log(`load init script: ${initScriptName}`);
    require(initScriptName);
}
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrRulesLoadAfterTypeDataEvent, (E) => {
    let mapScriptName = ini_helper_1.IniHelper.ReadString(new YrExtCore_1.IniReader(E.m_pIni), "Basic", "JsMapScript");
    if (mapScriptName) {
        var mapScriptable = gameScripts.getOrCreate(mapScriptName);
    }
});
let onLoadType = (yrObjectType, pIni) => {
    let iniReader = new YrExtCore_1.IniReader(pIni);
    let objectScriptName = ini_helper_1.IniHelper.ReadString(iniReader, yrObjectType.m_ID, "JsScript");
    if (objectScriptName) {
        let scriptable = gameScripts.getOrCreate(objectScriptName);
        yrObjectType.__scriptable = scriptable;
        if (scriptable && scriptable.script.onLoadType) {
            scriptable.script.onLoadType(yrObjectType, iniReader);
        }
    }
};
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
};
let scriptable_remove = (yrObject) => {
    let scriptable = get_scriptable(yrObject);
    if (!scriptable)
        return;
    if (scriptable.script.onRemoveInst) {
        scriptable.script.onRemoveInst(yrObject);
    }
    scriptable.removeInst(yrObject);
};
game_event_1.gameEvents.onCtor.unit.add(scriptable_add);
game_event_1.gameEvents.onCtor.infantry.add(scriptable_add);
game_event_1.gameEvents.onCtor.building.add(scriptable_add);
game_event_1.gameEvents.onCtor.aircraft.add(scriptable_add);
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrBulletConstructEvent, (E) => {
    scriptable_add(E.m_pBullet);
});
game_event_1.gameEvents.onCtor.superWeapon.add(scriptable_add);
game_event_1.gameEvents.onCtor.house.add(scriptable_add);
game_event_1.gameEvents.onDtor.unit.add(scriptable_remove);
game_event_1.gameEvents.onDtor.infantry.add(scriptable_remove);
game_event_1.gameEvents.onDtor.building.add(scriptable_remove);
game_event_1.gameEvents.onDtor.aircraft.add(scriptable_remove);
game_event_1.gameEvents.onDtor.bullet.add(scriptable_remove);
game_event_1.gameEvents.onDtor.superWeapon.add(scriptable_remove);
game_event_1.gameEvents.onDtor.house.add(scriptable_remove);
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrTechnoTypeLoadIniEvent, (E) => {
    onLoadType(E.m_pTechnoType, E.m_pIni);
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrBulletTypeLoadIniEvent, (E) => {
    onLoadType(E.m_pBulletType, E.m_pIni);
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSuperWeaponTypeLoadIniEvent, (E) => {
    onLoadType(E.m_pSuperWeaponType, E.m_pIni);
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrHouseTypeLoadIniEvent, (E) => {
    onLoadType(E.m_pHouseType, E.m_pIni);
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSaveGameEndStreamEvent, (E) => {
    for (const scriptable of gameScripts.scriptables.values()) {
        if (scriptable.script.onSave) {
            scriptable.script.onSave();
        }
        for (const yrObject of scriptable.insts) {
            if (scriptable.script.onSaveInst) {
                scriptable.script.onSaveInst(yrObject);
            }
            // serialize components
            let components = GetAllGetScriptableComponents(yrObject);
            serialization_1.JsSerialization.SaveNext(components.size);
            for (const [name, component] of components) {
                serialization_1.JsSerialization.SaveNext(name);
                serialization_1.JsSerialization.SaveNext(component);
            }
            saveCustomVariables(getYrObjectBlackboard(yrObject));
        }
    }
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrLoadGameEndStreamEvent, (E) => {
    for (const scriptable of gameScripts.scriptables.values()) {
        if (scriptable.script.onLoad) {
            scriptable.script.onLoad();
        }
        for (const yrObject of scriptable.insts) {
            if (scriptable.script.onLoadInst) {
                scriptable.script.onLoadInst(yrObject);
            }
            // serialize components
            let size = serialization_1.JsSerialization.LoadNext();
            if (size > 0) {
                let owner = yrObject;
                let components = new Map();
                owner.__components = components;
                for (let index = 0; index < size; index++) {
                    let name = serialization_1.JsSerialization.LoadNext();
                    let component = serialization_1.JsSerialization.LoadNext();
                    components[name] = component;
                }
            }
            loadCustomVariables(getYrObjectBlackboard(yrObject));
        }
    }
});
