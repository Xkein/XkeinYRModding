/// <reference path = "../index.d.ts"/>
declare module "YrExtCore" {
import { CDTimerClass, AbstractClass, CCINIClass } from "YRpp";
class IniReader
{
    GetIni() : CCINIClass;
    value() : string;
    max_size() : number;
    empty() : boolean;
    ReadString(pSection_0 : string, pKey_1 : string) : number;
}
}
