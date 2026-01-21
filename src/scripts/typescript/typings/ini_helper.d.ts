import { IniReader } from "YrExtCore";
import { AbstractType, AbstractTypeClass } from "YRpp";
import "reflect-metadata";
type IniReadMethod = (iniReader: IniReader, section: string, key: string) => any;
export declare class IniHelper {
    static ReadString(iniReader: IniReader, section: string, key: string): string | null;
    static ReadBool(iniReader: IniReader, section: string, key: string): string;
    static ReadStringList(iniReader: IniReader, section: string, key: string): string[] | null;
}
export declare function IniComponent(componentTargets: AbstractType[]): (target: any) => void;
export declare function IniField(iniKey: string, readMethod: IniReadMethod): (target: any, propertyKey: string) => void;
export declare function GetIniComponent<T>(klass: {
    new (): T;
}, yrObjectType: AbstractTypeClass): T;
export {};
