import { Serialization, YrLoadGameEndEvent, YrLoadGameEndStreamEvent, YrSaveGameBeginStreamEvent, YrSaveGameEndEvent, YrSaveGameEndStreamEvent } from "YrExtCore";
import { gameEvents } from "./game_event";


type SerializedComponentType = {new()};
type SerializeMethod = (obj: any) => void;

export class JsSerialization {
    static _curIdx: number;
    static _data: any;
    static _registeredClasses: SerializedComponentType[] = [];

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

    static RegisterSerializedField(target: SerializedComponentType, propertyKey: string, serializeMethod: SerializeMethod) {

    }

    public static SaveKey(key: string, data: any) {

    }
    public static LoadKey(key: string) {

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

gameEvents.registerHookEventHandler(YrSaveGameEndEvent, (E) => {
    JsSerialization.Finish();
});

gameEvents.registerHookEventHandler(YrLoadGameEndStreamEvent, (E) => {
    JsSerialization.Setup();
});

gameEvents.registerHookEventHandler(YrLoadGameEndEvent, (E) => {
    JsSerialization.Finish();
}); 


function defaultSerializeMethod(obj: any) {
    return JSON.stringify(obj);
}

export function SerializedField(serializeMethod?: SerializeMethod) {
  return function (target, propertyKey: string) {
    JsSerialization.RegisterSerializedField(target, propertyKey, serializeMethod ?? defaultSerializeMethod);
  }
}

