/// <reference path = "../index.d.ts"/>
declare module "YrExtCore" {
import { CDTimerClass, AbstractClass, CCINIClass, LandType } from "YRpp";
import { AKRESULT } from "wwise";
class YrInputBlocker
{
    static BlockAllInput() : void;
    static s_blockGadgetInput : boolean;
    static s_blockUserInterfaceInput : boolean;
    static s_blockKeyboardInput : boolean;
    static s_blockMouseLeftInput : boolean;
    static s_blockMouseRightInput : boolean;
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
