"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.JsSerialization = void 0;
exports.SerializedField = SerializedField;
const YrExtCore_1 = require("YrExtCore");
const YRpp_1 = require("YRpp");
const defaultSerializer = {
    save: function (data) {
        if (data === null || data === undefined) {
            return undefined;
        }
        let serializer = data.__typeSerializer;
        if (serializer) {
            let wrappedData = serializer.save(data);
            if (wrappedData === null || wrappedData === undefined) {
                return undefined;
            }
            if (typeof wrappedData === "object") {
                wrappedData._serId_ = serializer.id;
            }
            else {
                wrappedData = { _val_: wrappedData, _serId_: serializer.id };
            }
            return wrappedData;
        }
        return data;
    },
    load: function (data) {
        if (data === null || data === undefined) {
            return undefined;
        }
        if (data._serId_) {
            let serializer = JsSerialization._typeSerializerMap.get(data._serId_);
            if (serializer) {
                if (data._val_ !== undefined && data._val_ !== null) {
                    return serializer.load(data._val_);
                }
                else {
                    return serializer.load(data);
                }
            }
            else {
                console.error(`No type serializer found for id ${data._serId_}`);
            }
        }
        return data;
    },
    getDeferredSaveAction(data, propertyKey, inst) {
        let prop = inst[propertyKey];
        if (prop === null || prop === undefined) {
            return undefined;
        }
        let serializer = prop.__typeSerializer;
        if (serializer) {
            return serializer.getDeferredSaveAction?.(data, propertyKey, inst);
        }
    },
    getDeferredLoadAction(data, propertyKey, inst) {
        let prop = data[propertyKey];
        if (prop === null || prop === undefined) {
            return undefined;
        }
        if (prop._serId_) {
            let serializer = JsSerialization._typeSerializerMap.get(prop._serId_);
            if (serializer) {
                return serializer.getDeferredLoadAction?.(data, propertyKey, inst);
            }
        }
    },
};
class AutoTypeSerializer {
    id;
    klass;
    serializer = new Map();
    constructor(klass) {
        this.klass = klass;
        this.id = klass.name;
    }
    save(data) {
        let wrappedData = {};
        for (const [propertyKey, serializer] of this.serializer) {
            wrappedData[propertyKey] = serializer.save(data[propertyKey]);
            let deferredAction = serializer.getDeferredSaveAction?.(wrappedData, propertyKey, data);
            if (deferredAction) {
                JsSerialization.RegisterDeferredAction(deferredAction);
            }
        }
        return wrappedData;
    }
    load(data) {
        let inst = new this.klass();
        for (const [propertyKey, serializer] of this.serializer) {
            inst[propertyKey] = serializer.load(data[propertyKey]);
            let deferredAction = serializer.getDeferredLoadAction?.(data, propertyKey, inst);
            if (deferredAction) {
                JsSerialization.RegisterDeferredAction(deferredAction);
            }
        }
        return inst;
    }
}
class JsSerialization {
    static _curIdx;
    static _data;
    static _typeSerializerMap = new Map();
    static _deferredActions = [];
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
        for (const action of this._deferredActions) {
            action();
        }
        this._deferredActions = [];
        if (!YrExtCore_1.Serialization.IsLoading()) {
            let data = JSON.stringify(this._data);
            YrExtCore_1.Serialization.SaveKey("__JsSerialization", data);
        }
        this._data = null;
    }
    static GetNextKey() {
        return "data_" + this._curIdx++;
    }
    static RegisterDeferredAction(action) {
        this._deferredActions.push(action);
    }
    static RegisterTypeSerializer(klass, serializer) {
        klass.prototype.__typeSerializer = serializer;
        this._typeSerializerMap.set(serializer.id, serializer);
    }
    static RegisterSerializedField(target, propertyKey, serializer) {
        let className = target.constructor.name;
        let typeSerializer = target.__typeSerializer;
        if (!typeSerializer) {
            this.RegisterTypeSerializer(target.constructor, typeSerializer = new AutoTypeSerializer(target.constructor));
        }
        if (typeSerializer instanceof AutoTypeSerializer) {
            typeSerializer.serializer.set(propertyKey, serializer);
        }
        else {
            throw new Error("Cannot register serialized field for class " + className + " because it has a different type serializer");
        }
    }
    static SaveKey(key, data) {
        this._data[key] = defaultSerializer.save(data);
    }
    static LoadKey(key) {
        return defaultSerializer.load(this._data[key]);
    }
    static SaveNext(data) {
        this.SaveKey(this.GetNextKey(), data);
    }
    static LoadNext() {
        return this.LoadKey(this.GetNextKey());
    }
}
exports.JsSerialization = JsSerialization;
YrExtCore_1.Serialization.RegisterStepHandler(YrExtCore_1.ESerializationStep.SaveBegin_Epilogue, () => {
    JsSerialization.Setup();
});
YrExtCore_1.Serialization.RegisterStepHandler(YrExtCore_1.ESerializationStep.SaveEnd_Epilogue, () => {
    JsSerialization.Finish();
});
YrExtCore_1.Serialization.RegisterStepHandler(YrExtCore_1.ESerializationStep.LoadBegin_Epilogue, () => {
    JsSerialization.Setup();
});
YrExtCore_1.Serialization.RegisterStepHandler(YrExtCore_1.ESerializationStep.LoadEnd_Epilogue, () => {
    JsSerialization.Finish();
});
function SerializedField(serializer) {
    return function (target, propertyKey) {
        JsSerialization.RegisterSerializedField(target, propertyKey, serializer ?? defaultSerializer);
    };
}
let delayYrObjs = new Map();
JsSerialization.RegisterTypeSerializer(YRpp_1.AbstractClass, {
    id: "AbstractClassJsSerializer",
    save: function (yrObject) {
        if (!$isValidCppObject(yrObject)) {
            return undefined;
        }
        return yrObject.m_UniqueID;
    },
    load: function (uniqueId) {
        return uniqueId;
    },
    getDeferredLoadAction(data, propertyKey, inst) {
        let uniqueId = inst[propertyKey];
        delayYrObjs.set(uniqueId, null);
        return () => {
            inst[propertyKey] = delayYrObjs.get(uniqueId);
            if (inst[propertyKey] === null) {
                console.error(`Failed to load AbstractClass with UniqueID ${uniqueId}`);
            }
        };
    },
});
YrExtCore_1.Serialization.RegisterStepHandler(YrExtCore_1.ESerializationStep.LoadEnd_Prologue, () => {
    let yrObjects = YRpp_1.AbstractClass.s_Array;
    for (let index = 0; index < yrObjects.Count; index++) {
        const yrObject = yrObjects.GetItem(index);
        if (delayYrObjs.has(yrObject.m_UniqueID)) {
            delayYrObjs.set(yrObject.m_UniqueID, yrObject);
        }
    }
});
YrExtCore_1.Serialization.RegisterStepHandler(YrExtCore_1.ESerializationStep.LoadEnd_Epilogue, () => {
    delayYrObjs.clear();
});
