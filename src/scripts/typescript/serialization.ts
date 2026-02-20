import { ESerializationStep, Serialization, YrLoadGameEndEvent, YrLoadGameEndStreamEvent, YrSaveGameBeginStreamEvent, YrSaveGameEndEvent, YrSaveGameEndStreamEvent } from "YrExtCore";
import { gameEvents } from "./game_event";
import { AbstractClass } from "YRpp";
import { JsCppHelper } from "XkeinExt";

export interface FieldSerializer {
    save(data: any): any;
    load(data: any): any;
    // invoked by AutoTypeSerializer
    getDeferredSaveAction?(data: any, propertyKey: string, inst: any): (() => void) | undefined;
    // invoked by AutoTypeSerializer
    getDeferredLoadAction?(data: any, propertyKey: string, inst: any): (() => void) | undefined;
}

export interface TypeSerializer extends FieldSerializer {
    id: string;
}

const defaultSerializer: FieldSerializer = {
    save: function (data: any) {
        if (data === null || data === undefined) {
            return undefined;
        }
        let serializer: TypeSerializer = data.__typeSerializer;
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
    load: function (data: any) {
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
        let serializer: TypeSerializer = prop.__typeSerializer;
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
}
class AutoTypeSerializer implements TypeSerializer {
    public id: string;
    public klass: { new(): any };
    public serializer: Map<string, FieldSerializer> = new Map();
    constructor(klass: { new(): any }) {
        this.klass = klass;
        this.id = klass.name;
    }
    save(data: any) {
        let wrappedData = {}
        for (const [propertyKey, serializer] of this.serializer) {
            wrappedData[propertyKey] = serializer.save(data[propertyKey]);
            let deferredAction = serializer.getDeferredSaveAction?.(wrappedData, propertyKey, data);
            if (deferredAction) {
                JsSerialization.RegisterDeferredAction(deferredAction);
            }
        }
        return wrappedData;
    }
    load(data: any) {
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

export class JsSerialization {
    static _curIdx: number;
    static _data: any;
    static _typeSerializerMap: Map<string, TypeSerializer> = new Map();
    static _deferredActions: (() => void)[] = [];

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
        for (const action of this._deferredActions) {
            action();
        }
        this._deferredActions = [];

        if (!Serialization.IsLoading()) {
            let data = JSON.stringify(this._data);
            Serialization.SaveKey("__JsSerialization", data);
        }
        this._data = null;
    }

    static GetNextKey() : string {
        return "data_" + this._curIdx++;
    }

    static RegisterDeferredAction(action: () => void) {
        this._deferredActions.push(action);
    }

    static RegisterTypeSerializer<T>(klass: { new(): T }, serializer: TypeSerializer) {
        klass.prototype.__typeSerializer = serializer;
        this._typeSerializerMap.set(serializer.id, serializer);
    }

    static RegisterSerializedField(target, propertyKey: string, serializer: FieldSerializer) {
        let className = target.constructor.name;
        let typeSerializer: TypeSerializer = (target as any).__typeSerializer;
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

    public static SaveKey(key: string, data: any) {
        this._data[key] = defaultSerializer.save(data);
    }
    public static LoadKey(key: string) {
        return defaultSerializer.load(this._data[key]);
    }
    public static SaveNext(data: any) {
        this.SaveKey(this.GetNextKey(), data);
    }
    public static LoadNext() : any {
        return this.LoadKey(this.GetNextKey());
    }
}

Serialization.RegisterStepHandler(ESerializationStep.SaveBegin_Epilogue, () => {
    JsSerialization.Setup();
});
Serialization.RegisterStepHandler(ESerializationStep.SaveEnd_Epilogue, () => {
    JsSerialization.Finish();
});

Serialization.RegisterStepHandler(ESerializationStep.LoadBegin_Epilogue, () => {
    JsSerialization.Setup();
});
Serialization.RegisterStepHandler(ESerializationStep.LoadEnd_Epilogue, () => {
    JsSerialization.Finish();
});

export function SerializedField(serializer?: FieldSerializer) {
  return function (target, propertyKey: string) {
    JsSerialization.RegisterSerializedField(target, propertyKey, serializer ?? defaultSerializer);
  }
}

let delayYrObjs = new Map<number, AbstractClass | null>();
JsSerialization.RegisterTypeSerializer(AbstractClass, {
    id: "AbstractClassJsSerializer",
    save: function (yrObject: AbstractClass) {
        if (!$isValidCppObject(yrObject)) {
            return undefined;
        }
        return yrObject.m_UniqueID;
    },
    load: function (uniqueId: number) {
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
Serialization.RegisterStepHandler(ESerializationStep.LoadEnd_Prologue, () => {
    let yrObjects = AbstractClass.s_Array;
    for (let index = 0; index < yrObjects.Count; index++) {
        const yrObject = yrObjects.GetItem(index);
        if (delayYrObjs.has(yrObject.m_UniqueID)) {
            delayYrObjs.set(yrObject.m_UniqueID, yrObject);
        }
    }
});

Serialization.RegisterStepHandler(ESerializationStep.LoadEnd_Epilogue, () => {
    delayYrObjs.clear();
});
