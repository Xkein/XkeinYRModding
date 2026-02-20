import { IniReader, YrBulletConstructEvent, YrBulletLoadGameEndEvent, YrBulletSaveGameEndEvent, YrBulletTypeLoadIniEvent, YrHouseLoadGameEndEvent, YrHouseSaveGameEndEvent, YrHouseTypeLoadIniEvent, YrLoadGameBeginStreamEvent, YrLoadGameEndStreamEvent, YrRulesLoadAfterTypeDataEvent, YrSaveGameBeginStreamEvent, YrSaveGameEndStreamEvent, YrSuperLoadGameEndEvent, YrSuperSaveGameEndEvent, YrSuperWeaponTypeLoadIniEvent, YrTechnoLoadGameEndEvent, YrTechnoSaveGameEndEvent, YrTechnoTypeLoadIniEvent } from "YrExtCore"
import { GetIniComponent, IniComponent, IniField, IniHelper } from "./ini_helper"
import { AbstractClass, AbstractType, AbstractTypeClass, CCINIClass } from "YRpp";
import { gameEvents } from "./game_event";
import { JsSerialization } from "./serialization";

class GameScripts {
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

    get(name: string): GameScriptable | undefined {
        return this.scriptables.get(name);
    }

    getOrCreate(name: string): GameScriptable {
        var scriptable = this.get(name);
        if (scriptable)
            return scriptable;

        try {
            scriptable = new GameScriptable(name);
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

export interface IScriptable {
    onAddInst?(yrObject): void;
    onRemoveInst?(yrObject): void;
    onLoadType?(yrObjectType, iniReader: IniReader): void;
    onLoadInst?(yrObject): void;
    onSaveInst?(yrObject): void;
    onSave?(): void;
    onLoad?(): void;
}

class GameScriptable {
    insts: Set<any>;
    name: string;
    script: any;
    constructor(name: string) {
        this.insts = new Set();
        this.name = name;

        let scriptModule = require(name);
        if (scriptModule.script) {
            if (typeof scriptModule.script !== 'function') {
                throw new Error("export script must be class! script name = " + name);
            }
            this.script = new scriptModule.script();
            this.script.scriptable = this;
        }
    }

    addInst(inst) {
        this.insts.add(inst);
    }

    removeInst(inst) {
        this.insts.delete(inst);
    }
}

const emptyComponents = new Map();
const emptyScriptables = [];

interface IComponentOwner {
    // instance owned
    __components: Map<string, any>;
}

export function GetScriptableComponent<T>(klass: { new(): T }, yrObject: AbstractClass): T | undefined {
    let components = GetAllGetScriptableComponents(yrObject);
    let componentName = klass.name;
    return components.get(componentName);
}

export function CreateScriptableComponent<T>(klass: { new(): T }, yrObject: AbstractClass): T {
    let owner = yrObject as any as IComponentOwner;
    let components = owner.__components;
    if (!components) {
        components = owner.__components = new Map();
    }
    let componentName = klass.name;
    let component = new klass();
    components.set(componentName, component);
    return component;
}

export function GetAllGetScriptableComponents(yrObject: AbstractClass): Map<string, any> {
    let owner = yrObject as any as IComponentOwner;
    return owner.__components ?? emptyComponents;
}

export interface GameObjectBlackboard {
    __variables: Map<string, any>;
}

export function getYrObjectBlackboard(yrObject: AbstractClass): GameObjectBlackboard {
    return yrObject as any as GameObjectBlackboard;
}

export function getCustomVariable(blackboard: GameObjectBlackboard, name: string): any {
    if (blackboard.__variables) {
        return blackboard.__variables.get(name);
    }
    return undefined;
}

export function setCustomVariable(blackboard: GameObjectBlackboard, name: string, value: any) {
    if (!blackboard.__variables) {
        blackboard.__variables = new Map();
    }
    blackboard.__variables.set(name, value);
    return value
}

export function saveCustomVariables(blackboard: GameObjectBlackboard) {
    if (blackboard.__variables) {
        JsSerialization.SaveNext(blackboard.__variables.size);
        for (const [name, value] of blackboard.__variables) {
            JsSerialization.SaveNext(name);
            JsSerialization.SaveNext(value);
        }
    }
    else {
        JsSerialization.SaveNext(0);
    }
}

export function loadCustomVariables(blackboard: GameObjectBlackboard) {
    let variableCount = JsSerialization.LoadNext();
    if (variableCount > 0) {
        let variables = new Map();
        blackboard.__variables = variables;
        for (let index = 0; index < variableCount; index++) {
            let name = JsSerialization.LoadNext();
            let value = JsSerialization.LoadNext();
            variables.set(name, value);
        }
    }
}

function loadScripts(iniReader: IniReader, section: string, key: string) {
    let scriptNames = IniHelper.ReadStringList(iniReader, section, key);
    if (scriptNames) {
        let scriptables: GameScriptable[] = [];
        for (const scriptName of scriptNames) {
            let scriptable = gameScripts.getOrCreate(scriptName);
            scriptables.push(scriptable);
        }
        return scriptables;
    }
}

function loadSectionScripts(iniReader: IniReader, section: string, action?: (scriptable: GameScriptable) => void) {
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

let iniReaderXkein = new IniReader("XkeinExt.ini");
loadSectionScripts(iniReaderXkein, "JsScriptList", (scriptable) => {
    console.log(`load init script: ${scriptable.name}`);
});

gameEvents.registerHookEventHandler(YrRulesLoadAfterTypeDataEvent, (E) => {
    loadSectionScripts(new IniReader(E.m_pIni), "JsScriptList", (scriptable) => {
        console.log(`load map script: ${scriptable.name}`);
    });
})


@IniComponent([AbstractType.AircraftType, AbstractType.BuildingType, AbstractType.InfantryType, AbstractType.UnitType,
    AbstractType.BulletType, AbstractType.SuperWeaponType, AbstractType.HouseType], {
        afterLoad(iniReader, yrObjectType, iniComponent: ScriptableConfig) {
            for (const scriptable of iniComponent.scriptables.values()) {
                scriptable.script?.onLoadType?.(yrObjectType, iniReader);
            }
        },
    }
)
class ScriptableConfig {
    @IniField("JsScripts", loadScripts)
    scriptables: GameScriptable[] = emptyScriptables;
}

interface IScriptableInstance {
    m_Type: AbstractTypeClass;
}

function get_scriptables(yrObject: IScriptableInstance) {
    let config = GetIniComponent(ScriptableConfig, yrObject.m_Type);
    return config?.scriptables ?? emptyScriptables;
}

let scriptable_add = (yrObject: IScriptableInstance) => {
    let scriptables = get_scriptables(yrObject);
    for (const scriptable of scriptables) {
        scriptable.script?.onAddInst?.(yrObject);
    
        scriptable.addInst(yrObject);
    }
}

let scriptable_remove = (yrObject: IScriptableInstance) => {
    let scriptables = get_scriptables(yrObject);
    for (const scriptable of scriptables) {
        scriptable.script?.onRemoveInst?.(yrObject);
    
        scriptable.removeInst(yrObject);
    }
}

gameEvents.onCtor.unit.add(scriptable_add);
gameEvents.onCtor.infantry.add(scriptable_add);
gameEvents.onCtor.building.add(scriptable_add);
gameEvents.onCtor.aircraft.add(scriptable_add);
gameEvents.registerHookEventHandler(YrBulletConstructEvent, (E) => {
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

let scriptable_save = function (yrObject: AbstractClass) {
    // serialize scriptables
    let scriptables = get_scriptables(yrObject as any as IScriptableInstance);
    JsSerialization.SaveNext(scriptables.length);
    for (const scriptable of scriptables) {
        JsSerialization.SaveNext(scriptable.name);
        scriptable.script?.onSaveInst?.(yrObject);
    }
    
    // serialize components
    let components = GetAllGetScriptableComponents(yrObject);
    JsSerialization.SaveNext(components.size);
    for (const [componentName, component] of components) {
        JsSerialization.SaveNext(componentName);
        JsSerialization.SaveNext(component);
    }

    saveCustomVariables(getYrObjectBlackboard(yrObject));
}

let scriptable_load = function (yrObject: AbstractClass) {
    // serialize scriptables
    let scriptableCount = JsSerialization.LoadNext();
    for (let index = 0; index < scriptableCount; index++) {
        let scriptName = JsSerialization.LoadNext();
        let scriptable = gameScripts.getOrCreate(scriptName);
        scriptable.addInst(yrObject);
        scriptable.script?.onLoadInst?.(yrObject);
    }

    // serialize components
    let componentCount = JsSerialization.LoadNext();
    if (componentCount > 0) {
        let owner = yrObject as any as IComponentOwner;
        let components = new Map();
        owner.__components = components;
        for (let index = 0; index < componentCount; index++) {
            let componentName = JsSerialization.LoadNext();
            let component = JsSerialization.LoadNext();
            components.set(componentName, component);
        }
    }

    loadCustomVariables(getYrObjectBlackboard(yrObject));
}

gameEvents.registerHookEventHandler(YrTechnoSaveGameEndEvent, (E) => { scriptable_save(E.m_pTechno); });
gameEvents.registerHookEventHandler(YrTechnoLoadGameEndEvent, (E) => { scriptable_load(E.m_pTechno); });
gameEvents.registerHookEventHandler(YrBulletSaveGameEndEvent, (E) => { scriptable_save(E.m_pBullet); });
gameEvents.registerHookEventHandler(YrBulletLoadGameEndEvent, (E) => { scriptable_load(E.m_pBullet); });
gameEvents.registerHookEventHandler(YrSuperSaveGameEndEvent, (E) => { scriptable_save(E.m_pSuper); });
gameEvents.registerHookEventHandler(YrSuperLoadGameEndEvent, (E) => { scriptable_load(E.m_pSuper); });
gameEvents.registerHookEventHandler(YrHouseSaveGameEndEvent, (E) => { scriptable_save(E.m_pHouse); });
gameEvents.registerHookEventHandler(YrHouseLoadGameEndEvent, (E) => { scriptable_load(E.m_pHouse); });

gameEvents.registerHookEventHandler(YrSaveGameBeginStreamEvent, (E) => {
    // save scriptables' name
    JsSerialization.SaveNext(gameScripts.scriptables.size);
    for (const scriptable of gameScripts.scriptables.values()) {
        JsSerialization.SaveNext(scriptable.name);
    }
});

gameEvents.registerHookEventHandler(YrSaveGameEndStreamEvent, (E) => {
    for (const scriptable of gameScripts.scriptables.values()) {
        JsSerialization.SaveNext(scriptable.name);
        scriptable.script?.onSave?.();
    }
});

let loadingScriptableCount = 0;
gameEvents.registerHookEventHandler(YrLoadGameBeginStreamEvent, (E) => {
    loadingScriptableCount = JsSerialization.LoadNext();
    for (let index = 0; index < loadingScriptableCount; index++) {
        let scriptName = JsSerialization.LoadNext();
        let scriptable = gameScripts.getOrCreate(scriptName);
    }
});

gameEvents.registerHookEventHandler(YrLoadGameEndStreamEvent, (E) => {
    for (let index = 0; index < loadingScriptableCount; index++) {
        let scriptName = JsSerialization.LoadNext();
        let scriptable = gameScripts.getOrCreate(scriptName);
        scriptable.script?.onLoad?.();
    }
});
