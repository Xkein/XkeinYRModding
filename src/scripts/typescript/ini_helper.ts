import { IniReader, YrBulletTypeLoadIniEvent, YrHouseTypeLoadIniEvent, YrSuperWeaponTypeLoadIniEvent, YrTechnoTypeLoadIniEvent } from "YrExtCore"
import { AbstractType, AbstractTypeClass, CCINIClass } from "YRpp"
import "reflect-metadata"
import { gameEvents } from "./game_event";

type IniReadMethod = (iniReader: IniReader, section: string, key: string) => any;

export class IniHelper {
  static ReadString(iniReader: IniReader, section: string, key: string) {
    if (iniReader.ReadString(section, key) > 0) {
      return iniReader.value().trim();
    }
    return null;
  }

  static ReadBool(iniReader: IniReader, section: string, key: string) {
    if (iniReader.ReadString(section, key) > 0) {
      return iniReader.value().trim();
    }
    return "";
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
    return null;
  }
}

global.IniHelper = IniHelper;

class JsIniManager {
  static components : any[];

  static RegisterIniComponent(klass, componentTargets: AbstractType[]) {
    const onLoadIni = (yrObjectType: AbstractTypeClass, pIni: CCINIClass) => {
      if (!klass.__iniFields)
        return;
      if (componentTargets.indexOf(yrObjectType.WhatAmI()) >= 0) {
        return;
      }
      let iniComponentName = klass.name;
      let iniComponent = yrObjectType[iniComponentName]
      if (!iniComponent) {
        yrObjectType[iniComponentName] = iniComponent = new klass();
      }
      let iniReader = new IniReader(pIni);
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
    gameEvents.registerHookEventHandler(YrTechnoTypeLoadIniEvent, (E) => {
        onLoadIni(E.m_pTechnoType, E.m_pIni);
    });
    gameEvents.registerHookEventHandler(YrBulletTypeLoadIniEvent, (E) => {
        onLoadIni(E.m_pBulletType, E.m_pIni);
    });
    gameEvents.registerHookEventHandler(YrSuperWeaponTypeLoadIniEvent, (E) => {
        onLoadIni(E.m_pSuperWeaponType, E.m_pIni);
    });
    gameEvents.registerHookEventHandler(YrHouseTypeLoadIniEvent, (E) => {
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

export function IniComponent(componentTargets: AbstractType[]) {
  return function (target) {
    JsIniManager.RegisterIniComponent(target, componentTargets);
  }
}

export function IniField(iniKey: string, readMethod: IniReadMethod) {
  return function (target, propertyKey: string) {
    JsIniManager.RegisterIniField(target, propertyKey, iniKey, readMethod);
  }
}

export function GetIniComponent<T>(klass: {new(): T}, yrObjectType: AbstractTypeClass) : T {
  let iniComponentName = klass.name;
  return yrObjectType[iniComponentName];
}
