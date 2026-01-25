import { AudioComponent, AudioSystem, JsCppHelper, WwiseSoundBankRef } from "XkeinExt";
import { GetIniComponent, IniComponent, IniField, IniHelper } from "./ini_helper";
import { IniReader, YrBulletConstructEvent, YrBulletDetonateEvent, YrObjectLimboCheckedEvent, YrObjectReceiveDamageEvent, YrObjectUnlimboCheckedEvent, YrSceneEnterEvent, YrSceneExitEvent } from "YrExtCore";
import { AbstractType, HouseClass, ObjectClass, ScenarioClass } from "YRpp";
import { gameEvents } from "./game_event";

function ReadWwiseSoundBank(iniReader: IniReader, section: string, key: string) {
    let soundBankName = IniHelper.ReadString(iniReader, section, key)
    return soundBankName ? new WwiseSoundBankRef(soundBankName) : null
}

function ReadWwiseEvent(iniReader: IniReader, section: string, key: string) {
    let eventName = IniHelper.ReadString(iniReader, section, key)
    return eventName ? AudioSystem.GetIDFromString(eventName) : null
}

export namespace AK
{
    export namespace EVENTS
    {
        export const M_GAMEOVER = 155272345;
        export const M_INVASION = 4033210584;
        export const M_NONE = 443355295;
        export const M_NORMAL = 2309605244;
        export const M_UNDERATTACK = 2821901421;
        export const M_WINNING = 3431848355;
    } // namespace EVENTS

    export namespace STATES
    {
        export namespace MUSIC
        {
            export const GROUP = 3991942870;

            export namespace STATE
            {
                export const GAMEOVER = 4158285989;
                export const INVASION = 1335043396;
                export const NONE = 748895195;
                export const NORMAL = 1160234136;
                export const UNDERATTACK = 2862835585;
                export const WINNING = 2996998095;
            } // namespace STATE
        } // namespace MUSIC

    } // namespace STATES

    export namespace SWITCHES
    {
        export namespace SURFACE
        {
            export const GROUP = 1834394558;

            export namespace SWITCH
            {
                export const BEACH = 4075332698;
                export const CLEAR = 1754255536;
                export const ICE = 344481046;
                export const RAILROAD = 2722214071;
                export const ROAD = 2110808655;
                export const ROCK = 2144363834;
                export const ROUGH = 1262240040;
                export const TIBERIUM = 3960883458;
                export const TUNNEL = 3059984139;
                export const WALL = 2108779961;
                export const WATER = 2654748154;
                export const WEEDS = 588027413;
            } // namespace SWITCH
        } // namespace SURFACE

    } // namespace SWITCHES

    export namespace GAME_PARAMETERS
    {
        export const OBJECTHP = 1335699628;
    } // namespace GAME_PARAMETERS

    export namespace BANKS
    {
        export const INIT = 1355168291;
        export const ENGINEUSED = 2066667852;
    } // namespace BANKS

    export namespace BUSSES
    {
        export const _3D_BUS = 2337546123;
        export const ENVIRONMENT = 1229948536;
        export const EVA = 932389257;
        export const MASTER_AUDIO_BUS = 3803692087;
        export const MUSIC = 3991942870;
        export const SOUNDS = 1492361653;
        export const UI = 1551306167;
        export const UNIT = 1304109583;
        export const VOICE = 3170124113;
    } // namespace BUSSES

    export namespace AUDIO_DEVICES
    {
        export const NO_OUTPUT = 2317455096;
        export const SYSTEM = 3859886410;
    } // namespace AUDIO_DEVICES

}// namespace AK

@IniComponent([AbstractType.BulletType, AbstractType.SuperWeaponType, AbstractType.AircraftType, AbstractType.BuildingType, AbstractType.InfantryType, AbstractType.UnitType])
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

export enum EMusicState {
    None = 0,
    Normal = 1,
    GameOver = 2,
    Winning = 3,
    UnderAttack = 4,
    Invasion = 5,
}


class InteractiveMusic
{
    static lastTimeBattle;
    static musicState;
    
    static setMusicState(state) {
        if (InteractiveMusic.musicState == state)
            return;
        InteractiveMusic.musicState = state
        console.log("set music state" + state)
        let musicEvent
        switch (state) {
            case EMusicState.Normal:
                musicEvent = AK.EVENTS.M_NORMAL;
                break;
            case EMusicState.GameOver:
                musicEvent = AK.EVENTS.M_GAMEOVER;
                break;
            case EMusicState.Winning:
                musicEvent = AK.EVENTS.M_WINNING;
                break;
            case EMusicState.Invasion:
                musicEvent = AK.EVENTS.M_INVASION;
                break;
            case EMusicState.UnderAttack:
                musicEvent = AK.EVENTS.M_UNDERATTACK;
                break;
            default:
                musicEvent = AK.EVENTS.M_NONE;
                break;
        }
    }
}


let iniReaderXkein = new IniReader("XkeinExt.ini")
let initSoundBankNames = IniHelper.ReadStringList(iniReaderXkein, "Audio", "InitSoundBanks")
if (initSoundBankNames && initSoundBankNames.length) {
    let globalSoundBanks: WwiseSoundBankRef[] = []
    for (const soundBank of initSoundBankNames) {
        globalSoundBanks.push(new WwiseSoundBankRef(soundBank))
    }
    global.__globalSoundBanks = globalSoundBanks
}

let audio_component_add = (yrObject, entity) => {
    if (!yrObject.m_Type.audioConfig)
        return;
    
    if (!entity)
        entity = JsCppHelper.GetEntityByYrObject(yrObject);
    
    let audioComponent = AudioComponent.CreateAudioComponent(entity, yrObject);
    yrObject.audioComponent = audioComponent;
}

gameEvents.onCtor.unit.add(audio_component_add);
gameEvents.onCtor.infantry.add(audio_component_add);
gameEvents.onCtor.building.add(audio_component_add);
gameEvents.onCtor.aircraft.add(audio_component_add);
gameEvents.registerHookEventHandler(YrBulletConstructEvent, (E) => {
    audio_component_add(E.m_pBullet, null);
});
gameEvents.onCtor.superWeapon.add(audio_component_add);
gameEvents.onCtor.house.add(audio_component_add);

gameEvents.registerHookEventHandler(YrBulletDetonateEvent, (E) => {
    let yrObject = E.m_pBullet;
    let audioConfig = GetIniComponent(AudioConfig, yrObject.m_Type);
    if (audioConfig && audioConfig.detonateEvent) {
        let audioComponent = (yrObject as any).audioComponent as AudioComponent;
        AudioSystem.SetSwitch(AK.SWITCHES.SURFACE.GROUP, AudioSystem.GetSurfaceID(yrObject.GetCell().m_LandType), audioComponent.m_akGameObjId);
        AudioSystem.PostEvent(audioConfig.detonateEvent, audioComponent.m_akGameObjId);
    }
});

gameEvents.registerHookEventHandler(YrObjectReceiveDamageEvent, (E) => {
    let yrObject: ObjectClass | any = E.m_pObject;

    let audioConfig = GetIniComponent(AudioConfig, yrObject.m_Type);
    if (audioConfig && audioConfig.damageEvent) {
        AudioSystem.SetRTPCValue(AK.GAME_PARAMETERS.OBJECTHP, yrObject.GetHealthPercentage(), yrObject.audioComponent.m_akGameObjId);
        AudioSystem.PostEvent(audioConfig.damageEvent, yrObject.audioComponent.m_akGameObjId);
    }

    let player = HouseClass.s_CurrentPlayer;
    let isPlayerAttacked = player == yrObject.GetOwningHouse();
    let isPlayerInvasion = player == E.m_pAttackingHouse;
    if (isPlayerAttacked && isPlayerInvasion) {
        // player attack own unit
        return;
    }
    if (isPlayerInvasion) {
        InteractiveMusic.setMusicState(EMusicState.Invasion);
        InteractiveMusic.lastTimeBattle = Date.now();
    } else if (isPlayerAttacked) {
        InteractiveMusic.setMusicState(EMusicState.UnderAttack);
        InteractiveMusic.lastTimeBattle = Date.now();
    }
});
    
gameEvents.registerHookEventHandler(YrObjectUnlimboCheckedEvent, (E) => {
    let yrObject: ObjectClass | any = E.m_pObject;
    let audioConfig = yrObject.m_Type.audioConfig;
    if (audioConfig && audioConfig.createEvent) {
        AudioSystem.PostEvent(audioConfig.createEvent, yrObject.audioComponent.m_akGameObjId);
    }
});
gameEvents.registerHookEventHandler(YrObjectLimboCheckedEvent, (E) => {
    let yrObject: ObjectClass | any = E.m_pObject;
    let audioConfig = yrObject.m_Type.audioConfig;
    if (audioConfig && audioConfig.removeEvent) {
        AudioSystem.PostEvent(audioConfig.removeEvent, yrObject.audioComponent.m_akGameObjId);
    }
});

gameEvents.registerHookEventHandler(YrSceneEnterEvent, (E) => {
    InteractiveMusic.setMusicState(EMusicState.Normal);
});
gameEvents.registerHookEventHandler(YrSceneExitEvent, (E) => {
    InteractiveMusic.setMusicState(EMusicState.None);
});

gameEvents.game.onEndUpdate.add(() => {
    if (ScenarioClass.s_Instance) {
        let nextState = InteractiveMusic.musicState;
        if (InteractiveMusic.musicState == EMusicState.Invasion || InteractiveMusic.musicState == EMusicState.UnderAttack) {
            let elapsedTime = (Date.now() - InteractiveMusic.lastTimeBattle) / 1000;
            if (elapsedTime > 10) {
                nextState = EMusicState.Normal;
            }
        }

        let player = HouseClass.s_CurrentPlayer;
        if (player) {
            if (player.m_IsWinner) {
                nextState = EMusicState.Winning;
            } else if (player.m_IsGameOver) {
                nextState = EMusicState.GameOver;
            }
        }

        InteractiveMusic.setMusicState(nextState);
    }
})
