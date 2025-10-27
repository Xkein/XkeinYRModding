"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.IniHelper = void 0;
exports.IniComponent = IniComponent;
exports.IniField = IniField;
require("reflect-metadata");
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
        gameEvents.addGroupEventHandler(componentTargets, "onLoadIni", (yrObjectType, iniReader) => {
            if (!klass.__iniFields)
                return;
            let iniComponentName = klass.name.charAt(0).toLowerCase() + klass.name.slice(1);
            let iniComponent = yrObjectType[iniComponentName];
            if (!iniComponent) {
                yrObjectType[iniComponentName] = iniComponent = new klass();
            }
            for (const iniField of klass.__iniFields) {
                let iniValue = iniField.readMethod(iniReader, yrObjectType.m_ID, iniField.iniKey);
                if (iniValue !== null && iniValue !== undefined) {
                    if (!iniComponent) {
                        yrObjectType[iniComponentName] = iniComponent = new klass();
                    }
                    iniComponent[iniField.field] = iniValue;
                }
            }
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
        JsIniManager.RegisterIniComponent(target.prototype, componentTargets);
    };
}
function IniField(iniKey, readMethod) {
    return function (target, propertyKey) {
        JsIniManager.RegisterIniField(target, propertyKey, iniKey, readMethod);
    };
}
