"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.IniHelper = void 0;
exports.IniComponent = IniComponent;
exports.IniField = IniField;
exports.GetIniComponent = GetIniComponent;
const YrExtCore_1 = require("YrExtCore");
require("reflect-metadata");
class IniHelper {
    static ReadString(iniReader, section, key) {
        if (iniReader.ReadString(section, key) > 0) {
            return iniReader.value().trim();
        }
    }
    static ReadBool(iniReader, section, key) {
        let str = IniHelper.ReadString(iniReader, section, key);
        if (str) {
            switch (str[0].toUpperCase()) {
                case "1":
                case "T":
                case "Y":
                    return true;
                case "0":
                case "F":
                case "N":
                    return false;
            }
        }
    }
    static ReadInteger(iniReader, section, key) {
        let str = IniHelper.ReadString(iniReader, section, key);
        if (str) {
            return Number.parseInt(str);
        }
    }
    static ReadFloat(iniReader, section, key) {
        let str = IniHelper.ReadString(iniReader, section, key);
        if (str) {
            return Number.parseFloat(str);
        }
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
    }
}
exports.IniHelper = IniHelper;
global.IniHelper = IniHelper;
class JsIniManager {
    static components;
    static RegisterIniComponent(klass, componentTargets, callbacks) {
        const onLoadIni = (iniReader, yrObjectType) => {
            if (!klass.prototype.__iniFields)
                return;
            if (componentTargets.indexOf(yrObjectType.WhatAmI()) < 0) {
                return;
            }
            let iniComponentName = klass.name;
            let iniComponent = yrObjectType[iniComponentName];
            if (!iniComponent) {
                yrObjectType[iniComponentName] = iniComponent = new klass();
            }
            callbacks?.beforeLoad?.(iniReader, yrObjectType, iniComponent);
            for (const iniField of klass.prototype.__iniFields) {
                let iniValue = iniField.readMethod(iniReader, yrObjectType.m_ID, iniField.iniKey);
                if (iniValue !== null && iniValue !== undefined) {
                    if (!iniComponent) {
                        yrObjectType[iniComponentName] = iniComponent = new klass();
                    }
                    iniComponent[iniField.field] = iniValue;
                }
            }
            callbacks?.afterLoad?.(iniReader, yrObjectType, iniComponent);
        };
        for (const target of componentTargets) {
            YrExtCore_1.IniComponentLoader.RegisterAbstractTypeLoadingFunc(target, onLoadIni);
        }
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
function IniComponent(componentTargets, callbacks) {
    return function (target) {
        JsIniManager.RegisterIniComponent(target, componentTargets, callbacks);
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
