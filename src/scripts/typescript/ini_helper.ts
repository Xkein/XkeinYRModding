import { IniComponentLoader, IniReader, YrBulletTypeLoadIniEvent, YrHouseTypeLoadIniEvent, YrSuperWeaponTypeLoadIniEvent, YrTechnoTypeLoadIniEvent } from "YrExtCore"
import { AbstractType, AbstractTypeClass, CCINIClass } from "YRpp"
import "reflect-metadata"
import { gameEvents } from "./game_event";

type IniReadMethod = (iniReader: IniReader, section: string, key: string) => any;

export interface IniReadCallbacks {
    beforeLoad?: (iniReader: IniReader, yrObjectType: AbstractTypeClass, iniComponent: any) => void;
    afterLoad?: (iniReader: IniReader, yrObjectType: AbstractTypeClass, iniComponent: any) => void;
}

export class IniHelper {
  static ReadString(iniReader: IniReader, section: string, key: string) {
    if (iniReader.ReadString(section, key) > 0) {
      return iniReader.value().trim();
    }
  }

  static ReadBool(iniReader: IniReader, section: string, key: string) {
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

  static ReadInteger(iniReader: IniReader, section: string, key: string) {
    let str = IniHelper.ReadString(iniReader, section, key);
    if (str) {
      return Number.parseInt(str);
    }
  }

  static ReadFloat(iniReader: IniReader, section: string, key: string) {
    let str = IniHelper.ReadString(iniReader, section, key);
    if (str) {
      return Number.parseFloat(str);
    }
  }

  static ReadStringList(iniReader: IniReader, section: string, key: string) {
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

global.IniHelper = IniHelper;

class JsIniManager {
  static components: any[];

  static RegisterIniComponent(klass, componentTargets: AbstractType[], callbacks?: IniReadCallbacks) {
    const onLoadIni = (iniReader: IniReader, yrObjectType: AbstractTypeClass) => {
      if (!klass.prototype.__iniFields)
        return;
      if (componentTargets.indexOf(yrObjectType.WhatAmI()) < 0) {
        return;
      }
      let iniComponentName = klass.name;
      let iniComponent = yrObjectType[iniComponentName]
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
      IniComponentLoader.RegisterAbstractTypeLoadingFunc(target, onLoadIni);
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

export function IniComponent(componentTargets: AbstractType[], callbacks?: IniReadCallbacks) {
  return function (target) {
    JsIniManager.RegisterIniComponent(target, componentTargets, callbacks);
  }
}

export function IniField(iniKey: string, readMethod: IniReadMethod) {
  return function (target, propertyKey: string) {
    JsIniManager.RegisterIniField(target, propertyKey, iniKey, readMethod);
  }
}

export function GetIniComponent<T>(klass: { new(): T }, yrObjectType: AbstractTypeClass): T | undefined {
  let iniComponentName = klass.name;
  return yrObjectType[iniComponentName];
}
