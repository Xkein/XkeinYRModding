"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.JsSerialization = void 0;
exports.SerializedField = SerializedField;
const YrExtCore_1 = require("YrExtCore");
const game_event_1 = require("./game_event");
class SerializationInfo {
    typeName;
    serializer = new Map();
    constructor(typeName) {
        this.typeName = typeName;
    }
}
class JsSerialization {
    static _curIdx;
    static _data;
    static _registeredClasses = new Map();
    static Setup() {
        this._curIdx = 0;
        if (YrExtCore_1.Serialization.IsLoading()) {
            let data = YrExtCore_1.Serialization.LoadKey("__JsSerialization");
            this._data = JSON.parse(data);
        }
        else {
            this._data = {};
        }
    }
    static Finish() {
        if (!YrExtCore_1.Serialization.IsLoading()) {
            let data = JSON.stringify(this._data);
            YrExtCore_1.Serialization.SaveKey("__JsSerialization", data);
        }
        this._data = null;
    }
    static GetNextKey() {
        return "data_" + this._curIdx;
    }
    static RegisterSerializedField(target, propertyKey, serializer) {
        this._registeredClasses.set(target.name, target);
        let info = target.__serializationInfo;
        if (!info) {
            info = target.__serializationInfo = new SerializationInfo(target.name);
        }
        info.serializer[propertyKey] = serializer;
    }
    static SaveKey(key, data) {
        let info = data.__serializationInfo;
        if (info) {
            let wrappedData = {
                __type: info.typeName,
            };
            for (const [propertyKey, serializer] of info.serializer) {
                wrappedData[propertyKey] = serializer.save(data[propertyKey]);
            }
            this._data[key] = wrappedData;
        }
        else {
            this._data[key] = data;
        }
    }
    static LoadKey(key) {
        let data = this._data[key];
        if (data.__type) {
            let klass = this._registeredClasses[data.__type];
            let info = klass.__serializationInfo;
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
    static SaveNext(data) {
        this.SaveKey(this.GetNextKey(), data);
    }
    static LoadNext() {
        return this.LoadKey(this.GetNextKey());
    }
}
exports.JsSerialization = JsSerialization;
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSaveGameBeginStreamEvent, (E) => {
    JsSerialization.Setup();
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSaveGameEndStreamEvent, (E) => {
    JsSerialization.Finish();
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrLoadGameEndStreamEvent, (E) => {
    JsSerialization.Setup();
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrLoadGameEndStreamEvent, (E) => {
    JsSerialization.Finish();
});
const defaultSerializer = {
    save: function (data) {
        return data;
    },
    load: function (data) {
        return data;
    }
};
function SerializedField(serializer) {
    return function (target, propertyKey) {
        JsSerialization.RegisterSerializedField(target, propertyKey, serializer ?? defaultSerializer);
    };
}
