type SerializedComponentType = {
    new (): any;
};
type SerializeMethod = (obj: any) => void;
export declare class JsSerialization {
    static _curIdx: number;
    static _data: any;
    static _registeredClasses: SerializedComponentType[];
    static Setup(): void;
    static Finish(): void;
    static GetNextKey(): string;
    static RegisterSerializedField(target: SerializedComponentType, propertyKey: string, serializeMethod: SerializeMethod): void;
    static SaveKey(key: string, data: any): void;
    static LoadKey(key: string): void;
    static SaveNext(data: any): void;
    static LoadNext(): any;
}
export declare function SerializedField(serializeMethod?: SerializeMethod): (target: any, propertyKey: string) => void;
export {};
