/// <reference path = "../index.d.ts"/>
declare module "YrExtCore" {
import { CDTimerClass, AbstractClass, CCINIClass } from "YRpp";
class YrInputBlocker
{
    static BlockAllInput() : void;
    s_blockGadgetInput : boolean;
    s_blockUserInterfaceInput : boolean;
    s_blockKeyboardInput : boolean;
    s_blockMouseLeftInput : boolean;
    s_blockMouseRightInput : boolean;
}
class IniReader
{
    GetIni() : CCINIClass;
    value() : string;
    max_size() : number;
    empty() : boolean;
    ReadString(pSection_0 : string, pKey_1 : string) : number;
}
}
