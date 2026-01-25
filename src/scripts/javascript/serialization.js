"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.JsSerialization = void 0;
exports.SerializedField = SerializedField;
const YrExtCore_1 = require("YrExtCore");
const game_event_1 = require("./game_event");
class JsSerialization {
    static _curIdx;
    static _data;
    static _registeredClasses = [];
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
    static RegisterSerializedField(target, propertyKey, serializeMethod) {
    }
    static SaveKey(key, data) {
    }
    static LoadKey(key) {
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
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSaveGameEndEvent, (E) => {
    JsSerialization.Finish();
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrLoadGameEndStreamEvent, (E) => {
    JsSerialization.Setup();
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrLoadGameEndEvent, (E) => {
    JsSerialization.Finish();
});
function defaultSerializeMethod(obj) {
    return JSON.stringify(obj);
}
function SerializedField(serializeMethod) {
    return function (target, propertyKey) {
        JsSerialization.RegisterSerializedField(target, propertyKey, serializeMethod ?? defaultSerializeMethod);
    };
}
