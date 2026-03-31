"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.IsInstanceOfScriptable = IsInstanceOfScriptable;
exports.GetScriptableInstances = GetScriptableInstances;
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
const YRpp_1 = require("YRpp");
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
            scriptable = new GameScriptable(name);
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
    scriptable;
    constructor(name) {
        this.insts = new Set();
        this.name = name;
        let scriptModule = require(name);
        if (scriptModule.script) {
            if (typeof scriptModule.script !== 'function') {
                throw new Error("export script must be class! script name = " + name);
            }
            this.scriptable = new scriptModule.script();
            this.scriptable._gameScriptable_ = this;
        }
    }
    addInst(inst) {
        this.insts.add(inst);
    }
    removeInst(inst) {
        this.insts.delete(inst);
    }
}
function IsInstanceOfScriptable(scriptable, instance) {
    let gameScriptable = scriptable._gameScriptable_;
    if (gameScriptable) {
        return gameScriptable.insts.has(instance);
    }
    return false;
}
const emptySet = new Set();
function GetScriptableInstances(scriptable) {
    let gameScriptable = scriptable._gameScriptable_;
    if (gameScriptable) {
        return gameScriptable.insts;
    }
    return emptySet;
}
const emptyComponents = new Map();
const emptyScriptables = [];
function GetScriptableComponent(klass, yrObject) {
    let components = GetAllGetScriptableComponents(yrObject);
    let componentName = klass.name;
    return components.get(componentName);
}
function CreateScriptableComponent(klass, yrObject) {
    let owner = yrObject;
    let components = owner.__components;
    if (!components) {
        components = owner.__components = new Map();
    }
    let componentName = klass.name;
    let component = new klass();
    components.set(componentName, component);
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
        return blackboard.__variables.get(name);
    }
    return undefined;
}
function setCustomVariable(blackboard, name, value) {
    if (!blackboard.__variables) {
        blackboard.__variables = new Map();
    }
    blackboard.__variables.set(name, value);
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
            variables.set(name, value);
        }
    }
}
function loadScripts(iniReader, section, key) {
    let scriptNames = ini_helper_1.IniHelper.ReadStringList(iniReader, section, key);
    if (scriptNames) {
        let scriptables = [];
        for (const scriptName of scriptNames) {
            let scriptable = gameScripts.getOrCreate(scriptName);
            scriptables.push(scriptable);
        }
        return scriptables;
    }
}
function loadSectionScripts(iniReader, section, action) {
    let ini = iniReader.GetIni();
    let count = ini.GetKeyCount(section);
    for (let index = 0; index < count; index++) {
        let key = ini.GetKeyName(section, index);
        let scriptables = loadScripts(iniReader, section, key);
        if (scriptables) {
            for (const scriptable of scriptables) {
                action?.(scriptable);
            }
        }
    }
}
let iniReaderXkein = new YrExtCore_1.IniReader("XkeinExt.ini");
loadSectionScripts(iniReaderXkein, "JsScriptList", (scriptable) => {
    console.log(`load init script: ${scriptable.name}`);
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrRulesLoadAfterTypeDataEvent, (E) => {
    loadSectionScripts(new YrExtCore_1.IniReader(E.m_pIni), "JsScriptList", (scriptable) => {
        console.log(`load map script: ${scriptable.name}`);
    });
});
let ScriptableConfig = class ScriptableConfig {
    scriptables = emptyScriptables;
};
__decorate([
    (0, ini_helper_1.IniField)("JsScripts", loadScripts),
    __metadata("design:type", Array)
], ScriptableConfig.prototype, "scriptables", void 0);
ScriptableConfig = __decorate([
    (0, ini_helper_1.IniComponent)([YRpp_1.AbstractType.AircraftType, YRpp_1.AbstractType.BuildingType, YRpp_1.AbstractType.InfantryType, YRpp_1.AbstractType.UnitType,
        YRpp_1.AbstractType.BulletType, YRpp_1.AbstractType.SuperWeaponType, YRpp_1.AbstractType.HouseType], {
        afterLoad(iniReader, yrObjectType, iniComponent) {
            for (const scriptable of iniComponent.scriptables.values()) {
                scriptable.scriptable?.onLoadType?.(yrObjectType, iniReader);
            }
        },
    })
], ScriptableConfig);
function get_scriptables(yrObject) {
    let config = (0, ini_helper_1.GetIniComponent)(ScriptableConfig, yrObject.m_Type);
    return config?.scriptables ?? emptyScriptables;
}
let scriptable_add = (yrObject) => {
    let scriptables = get_scriptables(yrObject);
    for (const scriptable of scriptables) {
        scriptable.scriptable?.onAddInst?.(yrObject);
        scriptable.addInst(yrObject);
    }
};
let scriptable_remove = (yrObject) => {
    let scriptables = get_scriptables(yrObject);
    for (const scriptable of scriptables) {
        scriptable.scriptable?.onRemoveInst?.(yrObject);
        scriptable.removeInst(yrObject);
    }
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
let scriptable_save = function (yrObject) {
    // serialize scriptables
    let scriptables = get_scriptables(yrObject);
    serialization_1.JsSerialization.SaveNext(scriptables.length);
    for (const scriptable of scriptables) {
        serialization_1.JsSerialization.SaveNext(scriptable.name);
        scriptable.scriptable?.onSaveInst?.(yrObject);
    }
    // serialize components
    let components = GetAllGetScriptableComponents(yrObject);
    serialization_1.JsSerialization.SaveNext(components.size);
    for (const [componentName, component] of components) {
        serialization_1.JsSerialization.SaveNext(componentName);
        serialization_1.JsSerialization.SaveNext(component);
    }
    saveCustomVariables(getYrObjectBlackboard(yrObject));
};
let scriptable_load = function (yrObject) {
    // serialize scriptables
    let scriptableCount = serialization_1.JsSerialization.LoadNext();
    for (let index = 0; index < scriptableCount; index++) {
        let scriptName = serialization_1.JsSerialization.LoadNext();
        let scriptable = gameScripts.getOrCreate(scriptName);
        scriptable.addInst(yrObject);
        scriptable.scriptable?.onLoadInst?.(yrObject);
    }
    // serialize components
    let componentCount = serialization_1.JsSerialization.LoadNext();
    if (componentCount > 0) {
        let owner = yrObject;
        let components = new Map();
        owner.__components = components;
        for (let index = 0; index < componentCount; index++) {
            let componentName = serialization_1.JsSerialization.LoadNext();
            let component = serialization_1.JsSerialization.LoadNext();
            components.set(componentName, component);
        }
    }
    loadCustomVariables(getYrObjectBlackboard(yrObject));
};
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrTechnoSaveGameEndEvent, (E) => { scriptable_save(E.m_pTechno); });
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrTechnoLoadGameEndEvent, (E) => { scriptable_load(E.m_pTechno); });
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrBulletSaveGameEndEvent, (E) => { scriptable_save(E.m_pBullet); });
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrBulletLoadGameEndEvent, (E) => { scriptable_load(E.m_pBullet); });
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSuperSaveGameEndEvent, (E) => { scriptable_save(E.m_pSuper); });
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSuperLoadGameEndEvent, (E) => { scriptable_load(E.m_pSuper); });
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrHouseSaveGameEndEvent, (E) => { scriptable_save(E.m_pHouse); });
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrHouseLoadGameEndEvent, (E) => { scriptable_load(E.m_pHouse); });
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSaveGameBeginStreamEvent, (E) => {
    // save scriptables' name
    serialization_1.JsSerialization.SaveNext(gameScripts.scriptables.size);
    for (const scriptable of gameScripts.scriptables.values()) {
        serialization_1.JsSerialization.SaveNext(scriptable.name);
    }
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSaveGameEndStreamEvent, (E) => {
    for (const scriptable of gameScripts.scriptables.values()) {
        serialization_1.JsSerialization.SaveNext(scriptable.name);
        scriptable.scriptable?.onSave?.();
    }
});
let loadingScriptableCount = 0;
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrLoadGameBeginStreamEvent, (E) => {
    loadingScriptableCount = serialization_1.JsSerialization.LoadNext();
    for (let index = 0; index < loadingScriptableCount; index++) {
        let scriptName = serialization_1.JsSerialization.LoadNext();
        let scriptable = gameScripts.getOrCreate(scriptName);
    }
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrLoadGameEndStreamEvent, (E) => {
    for (let index = 0; index < loadingScriptableCount; index++) {
        let scriptName = serialization_1.JsSerialization.LoadNext();
        let scriptable = gameScripts.getOrCreate(scriptName);
        scriptable.scriptable?.onLoad?.();
    }
});
