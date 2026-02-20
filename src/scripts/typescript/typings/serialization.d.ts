export interface FieldSerializer {
    save(data: any): any;
    load(data: any): any;
    getDeferredSaveAction?(data: any, propertyKey: string, inst: any): (() => void) | undefined;
    getDeferredLoadAction?(data: any, propertyKey: string, inst: any): (() => void) | undefined;
}
export interface TypeSerializer extends FieldSerializer {
    id: string;
}
export declare class JsSerialization {
    static _curIdx: number;
    static _data: any;
    static _typeSerializerMap: Map<string, TypeSerializer>;
    static _deferredActions: (() => void)[];
    static Setup(): void;
    static Finish(): void;
    static GetNextKey(): string;
    static RegisterDeferredAction(action: () => void): void;
    static RegisterTypeSerializer<T>(klass: {
        new (): T;
    }, serializer: TypeSerializer): void;
    static RegisterSerializedField(target: any, propertyKey: string, serializer: FieldSerializer): void;
    static SaveKey(key: string, data: any): void;
    static LoadKey(key: string): any;
    static SaveNext(data: any): void;
    static LoadNext(): any;
}
export declare function SerializedField(serializer?: FieldSerializer): (target: any, propertyKey: string) => void;
