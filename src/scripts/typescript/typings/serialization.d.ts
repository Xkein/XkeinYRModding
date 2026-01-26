type SerializedComponentType = {
    new (): any;
};
export declare class JsSerialization {
    static _curIdx: number;
    static _data: any;
    static _registeredClasses: Map<string, SerializedComponentType>;
    static Setup(): void;
    static Finish(): void;
    static GetNextKey(): string;
    static RegisterSerializedField(target: SerializedComponentType, propertyKey: string, serializer: FieldSerializer): void;
    static SaveKey(key: string, data: any): void;
    static LoadKey(key: string): any;
    static SaveNext(data: any): void;
    static LoadNext(): any;
}
export interface FieldSerializer {
    save(data: any): any;
    load(data: any): any;
}
export declare function SerializedField(serializer?: FieldSerializer): (target: any, propertyKey: string) => void;
export {};
