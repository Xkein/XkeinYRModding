import { AudioSystem, WwiseSoundBankRef } from "XkeinExt";
import { IniComponent, IniField, IniHelper } from "./ini_helper";
import { IniReader } from "YrExtCore";

function ReadWwiseSoundBank(iniReader: IniReader, section: string, key: string) {
    let soundBankName = IniHelper.ReadString(iniReader, section, key)
    return soundBankName ? new WwiseSoundBankRef(soundBankName) : null
}

function ReadWwiseEvent(iniReader: IniReader, section: string, key: string) {
    let eventName = IniHelper.ReadString(iniReader, section, key)
    return eventName ? AudioSystem.GetIDFromString(eventName) : null
}

@IniComponent([gameEvents.bulletType, gameEvents.superWeaponType].concat(gameEvents.technoTypeGroupEvents))
class AudioConfig {
    @IniField("Audio.SoundBank", ReadWwiseSoundBank)
    soundBank: WwiseSoundBankRef;
    @IniField("Audio.CreateEvent", ReadWwiseEvent)
    createEvent: number;
    @IniField("Audio.DetonateEvent", ReadWwiseEvent)
    detonateEvent: number;
    @IniField("Audio.DamageEvent", ReadWwiseEvent)
    damageEvent: number;
    @IniField("Audio.RemoveEvent", ReadWwiseEvent)
    removeEvent: number;
}