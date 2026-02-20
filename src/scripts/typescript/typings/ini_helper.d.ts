import { IniReader } from "YrExtCore";
import { AbstractType, AbstractTypeClass } from "YRpp";
import "reflect-metadata";
type IniReadMethod = (iniReader: IniReader, section: string, key: string) => any;
export interface IniReadCallbacks {
    beforeLoad?: (iniReader: IniReader, yrObjectType: AbstractTypeClass, iniComponent: any) => void;
    afterLoad?: (iniReader: IniReader, yrObjectType: AbstractTypeClass, iniComponent: any) => void;
}
export declare class IniHelper {
    static ReadString(iniReader: IniReader, section: string, key: string): string | undefined;
    static ReadBool(iniReader: IniReader, section: string, key: string): boolean | undefined;
    static ReadInteger(iniReader: IniReader, section: string, key: string): number | undefined;
    static ReadFloat(iniReader: IniReader, section: string, key: string): number | undefined;
    static ReadStringList(iniReader: IniReader, section: string, key: string): string[] | undefined;
}
export declare function IniComponent(componentTargets: AbstractType[], callbacks?: IniReadCallbacks): (target: any) => void;
export declare function IniField(iniKey: string, readMethod: IniReadMethod): (target: any, propertyKey: string) => void;
export declare function GetIniComponent<T>(klass: {
    new (): T;
}, yrObjectType: AbstractTypeClass): T | undefined;
export {};
