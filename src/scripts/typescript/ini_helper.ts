import { IniReader } from "YrExtCore"
import { AbstractTypeClass } from "YRpp"
import "reflect-metadata"

type IniReadMethod = (iniReader: IniReader, section: string, key: string) => any;

export class IniHelper {
  static ReadString(iniReader: IniReader, section: string, key: string) {
    if (iniReader.ReadString(section, key) > 0) {
      return iniReader.value().trim()
    }
    return null
  }

  static ReadBool(iniReader: IniReader, section: string, key: string) {
    if (iniReader.ReadString(section, key) > 0) {
      return iniReader.value().trim()
    }
    return ""
  }

  static ReadStringList(iniReader: IniReader, section: string, key: string) {
    let str = IniHelper.ReadString(iniReader, section, key)
    if (str) {
      let list = str.split(",")
      for (let index = 0; index < list.length; index++) {
        list[index] = list[index].trim();
      }
      return list
    }
    return null
  }
}

global.IniHelper = IniHelper;

class JsIniManager {
  static components : any[];

  static RegisterIniComponent(klass, componentTargets) {
    gameEvents.addGroupEventHandler(componentTargets, "onLoadIni", (yrObjectType: AbstractTypeClass, iniReader: IniReader) => {
      if (!klass.__iniFields)
        return
      let iniComponentName = klass.name;
      let iniComponent = yrObjectType[iniComponentName]
      if (!iniComponent) {
        yrObjectType[iniComponentName] = iniComponent = new klass()
      }
      for (const iniField of klass.__iniFields) {
        let iniValue = iniField.readMethod(iniReader, yrObjectType.m_ID, iniField.iniKey)
        if (iniValue !== null && iniValue !== undefined) {
          if (!iniComponent) {
            yrObjectType[iniComponentName] = iniComponent = new klass()
          }
          iniComponent[iniField.field] = iniValue
        }
      }
    })
  }

  static RegisterIniField(klass, field, iniKey, readMethod) {
    if (!klass.__iniFields) {
      klass.__iniFields = []
    }
    let iniField = {
      field: field,
      iniKey: iniKey,
      readMethod: readMethod
    }
    klass.__iniFields.push(iniField)
  }
}

export function IniComponent(componentTargets) {
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
