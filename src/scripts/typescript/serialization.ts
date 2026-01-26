import { Serialization, YrLoadGameEndEvent, YrLoadGameEndStreamEvent, YrSaveGameBeginStreamEvent, YrSaveGameEndEvent, YrSaveGameEndStreamEvent } from "YrExtCore";
import { gameEvents } from "./game_event";


type SerializedComponentType = {new()};

class SerializationInfo {
    public typeName: string;
    public serializer: Map<string, FieldSerializer> = new Map();
    constructor(typeName: string) {
        this.typeName = typeName;
    }
}

export class JsSerialization {
    static _curIdx: number;
    static _data: any;
    static _registeredClasses: Map<string, SerializedComponentType> = new Map();

    static Setup() {
        this._curIdx = 0;

        if (Serialization.IsLoading()) {
            let data = Serialization.LoadKey("__JsSerialization");
            this._data = JSON.parse(data);
        }
        else {
            this._data = {};
        }
    }

    static Finish() {
        if (!Serialization.IsLoading()) {
            let data = JSON.stringify(this._data);
            Serialization.SaveKey("__JsSerialization", data);
        }
        this._data = null;
    }

    static GetNextKey() : string {
        return "data_" + this._curIdx;
    }

    static RegisterSerializedField(target: SerializedComponentType, propertyKey: string, serializer: FieldSerializer) {
        this._registeredClasses.set(target.name, target);
        let info: SerializationInfo = (target as any).__serializationInfo;
        if (!info) {
            info = (target as any).__serializationInfo = new SerializationInfo(target.name);
        }
        info.serializer[propertyKey] = serializer;
    }

    public static SaveKey(key: string, data: any) {
        let info: SerializationInfo = data.__serializationInfo;
        if (info) {
            let wrappedData = {
                __type: info.typeName,
            }
            for (const [propertyKey, serializer] of info.serializer) {
                wrappedData[propertyKey] = serializer.save(data[propertyKey]);
            }
            this._data[key] = wrappedData;
        }
        else {
            this._data[key] = data;
        }
    }
    public static LoadKey(key: string) {
        let data = this._data[key];
        if (data.__type) {
            let klass: SerializedComponentType = this._registeredClasses[data.__type];
            let info: SerializationInfo = (klass as any).__serializationInfo;
            let inst = new klass();
            for (const [propertyKey, serializer] of info.serializer) {
                inst[propertyKey] = serializer.load(data[propertyKey]);
            }
            return inst;
        }
        else {
            return data;
        }
    }
    public static SaveNext(data: any) {
        this.SaveKey(this.GetNextKey(), data);
    }
    public static LoadNext() : any {
        return this.LoadKey(this.GetNextKey());
    }
}

gameEvents.registerHookEventHandler(YrSaveGameBeginStreamEvent, (E) => {
    JsSerialization.Setup();
});

gameEvents.registerHookEventHandler(YrSaveGameEndStreamEvent, (E) => {
    JsSerialization.Finish();
});

gameEvents.registerHookEventHandler(YrLoadGameEndStreamEvent, (E) => {
    JsSerialization.Setup();
});

gameEvents.registerHookEventHandler(YrLoadGameEndStreamEvent, (E) => {
    JsSerialization.Finish();
}); 

export interface FieldSerializer {
    save(data: any): any;
    load(data: any): any;
}

const defaultSerializer: FieldSerializer = {
    save: function (data: any) {
        return data;
    },
    load: function (data: any) {
        return data;
    }
}

export function SerializedField(serializer?: FieldSerializer) {
  return function (target, propertyKey: string) {
    JsSerialization.RegisterSerializedField(target, propertyKey, serializer ?? defaultSerializer);
  }
}

