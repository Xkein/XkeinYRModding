"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.IniHelper = void 0;
exports.IniComponent = IniComponent;
exports.IniField = IniField;
exports.GetIniComponent = GetIniComponent;
const YrExtCore_1 = require("YrExtCore");
require("reflect-metadata");
const game_event_1 = require("./game_event");
class IniHelper {
    static ReadString(iniReader, section, key) {
        if (iniReader.ReadString(section, key) > 0) {
            return iniReader.value().trim();
        }
        return null;
    }
    static ReadBool(iniReader, section, key) {
        if (iniReader.ReadString(section, key) > 0) {
            return iniReader.value().trim();
        }
        return "";
    }
    static ReadStringList(iniReader, section, key) {
        let str = IniHelper.ReadString(iniReader, section, key);
        if (str) {
            let list = str.split(",");
            for (let index = 0; index < list.length; index++) {
                list[index] = list[index].trim();
            }
            return list;
        }
        return null;
    }
}
exports.IniHelper = IniHelper;
global.IniHelper = IniHelper;
class JsIniManager {
    static components;
    static RegisterIniComponent(klass, componentTargets) {
        const onLoadIni = (yrObjectType, pIni) => {
            if (!klass.__iniFields)
                return;
            if (componentTargets.indexOf(yrObjectType.WhatAmI()) >= 0) {
                return;
            }
            let iniComponentName = klass.name;
            let iniComponent = yrObjectType[iniComponentName];
            if (!iniComponent) {
                yrObjectType[iniComponentName] = iniComponent = new klass();
            }
            let iniReader = new YrExtCore_1.IniReader(pIni);
            for (const iniField of klass.__iniFields) {
                let iniValue = iniField.readMethod(iniReader, yrObjectType.m_ID, iniField.iniKey);
                if (iniValue !== null && iniValue !== undefined) {
                    if (!iniComponent) {
                        yrObjectType[iniComponentName] = iniComponent = new klass();
                    }
                    iniComponent[iniField.field] = iniValue;
                }
            }
        };
        game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrTechnoTypeLoadIniEvent, (E) => {
            onLoadIni(E.m_pTechnoType, E.m_pIni);
        });
        game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrBulletTypeLoadIniEvent, (E) => {
            onLoadIni(E.m_pBulletType, E.m_pIni);
        });
        game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSuperWeaponTypeLoadIniEvent, (E) => {
            onLoadIni(E.m_pSuperWeaponType, E.m_pIni);
        });
        game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrHouseTypeLoadIniEvent, (E) => {
            onLoadIni(E.m_pHouseType, E.m_pIni);
        });
    }
    static RegisterIniField(klass, field, iniKey, readMethod) {
        if (!klass.__iniFields) {
            klass.__iniFields = [];
        }
        let iniField = {
            field: field,
            iniKey: iniKey,
            readMethod: readMethod
        };
        klass.__iniFields.push(iniField);
    }
}
function IniComponent(componentTargets) {
    return function (target) {
        JsIniManager.RegisterIniComponent(target, componentTargets);
    };
}
function IniField(iniKey, readMethod) {
    return function (target, propertyKey) {
        JsIniManager.RegisterIniField(target, propertyKey, iniKey, readMethod);
    };
}
function GetIniComponent(klass, yrObjectType) {
    let iniComponentName = klass.name;
    return yrObjectType[iniComponentName];
}
