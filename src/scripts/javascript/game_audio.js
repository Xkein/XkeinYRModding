"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.EMusicState = exports.AK = void 0;
const XkeinExt_1 = require("XkeinExt");
const ini_helper_1 = require("./ini_helper");
const YrExtCore_1 = require("YrExtCore");
const YRpp_1 = require("YRpp");
const game_event_1 = require("./game_event");
function ReadWwiseSoundBank(iniReader, section, key) {
    let soundBankName = ini_helper_1.IniHelper.ReadString(iniReader, section, key);
    return soundBankName ? new XkeinExt_1.WwiseSoundBankRef(soundBankName) : null;
}
function ReadWwiseEvent(iniReader, section, key) {
    let eventName = ini_helper_1.IniHelper.ReadString(iniReader, section, key);
    return eventName ? XkeinExt_1.AudioSystem.GetIDFromString(eventName) : null;
}
var AK;
(function (AK) {
    let EVENTS;
    (function (EVENTS) {
        EVENTS.M_GAMEOVER = 155272345;
        EVENTS.M_INVASION = 4033210584;
        EVENTS.M_NONE = 443355295;
        EVENTS.M_NORMAL = 2309605244;
        EVENTS.M_UNDERATTACK = 2821901421;
        EVENTS.M_WINNING = 3431848355;
    })(EVENTS = AK.EVENTS || (AK.EVENTS = {})); // namespace EVENTS
    let STATES;
    (function (STATES) {
        let MUSIC;
        (function (MUSIC) {
            MUSIC.GROUP = 3991942870;
            let STATE;
            (function (STATE) {
                STATE.GAMEOVER = 4158285989;
                STATE.INVASION = 1335043396;
                STATE.NONE = 748895195;
                STATE.NORMAL = 1160234136;
                STATE.UNDERATTACK = 2862835585;
                STATE.WINNING = 2996998095;
            })(STATE = MUSIC.STATE || (MUSIC.STATE = {})); // namespace STATE
        })(MUSIC = STATES.MUSIC || (STATES.MUSIC = {})); // namespace MUSIC
    })(STATES = AK.STATES || (AK.STATES = {})); // namespace STATES
    let SWITCHES;
    (function (SWITCHES) {
        let SURFACE;
        (function (SURFACE) {
            SURFACE.GROUP = 1834394558;
            let SWITCH;
            (function (SWITCH) {
                SWITCH.BEACH = 4075332698;
                SWITCH.CLEAR = 1754255536;
                SWITCH.ICE = 344481046;
                SWITCH.RAILROAD = 2722214071;
                SWITCH.ROAD = 2110808655;
                SWITCH.ROCK = 2144363834;
                SWITCH.ROUGH = 1262240040;
                SWITCH.TIBERIUM = 3960883458;
                SWITCH.TUNNEL = 3059984139;
                SWITCH.WALL = 2108779961;
                SWITCH.WATER = 2654748154;
                SWITCH.WEEDS = 588027413;
            })(SWITCH = SURFACE.SWITCH || (SURFACE.SWITCH = {})); // namespace SWITCH
        })(SURFACE = SWITCHES.SURFACE || (SWITCHES.SURFACE = {})); // namespace SURFACE
    })(SWITCHES = AK.SWITCHES || (AK.SWITCHES = {})); // namespace SWITCHES
    let GAME_PARAMETERS;
    (function (GAME_PARAMETERS) {
        GAME_PARAMETERS.OBJECTHP = 1335699628;
    })(GAME_PARAMETERS = AK.GAME_PARAMETERS || (AK.GAME_PARAMETERS = {})); // namespace GAME_PARAMETERS
    let BANKS;
    (function (BANKS) {
        BANKS.INIT = 1355168291;
        BANKS.ENGINEUSED = 2066667852;
    })(BANKS = AK.BANKS || (AK.BANKS = {})); // namespace BANKS
    let BUSSES;
    (function (BUSSES) {
        BUSSES._3D_BUS = 2337546123;
        BUSSES.ENVIRONMENT = 1229948536;
        BUSSES.EVA = 932389257;
        BUSSES.MASTER_AUDIO_BUS = 3803692087;
        BUSSES.MUSIC = 3991942870;
        BUSSES.SOUNDS = 1492361653;
        BUSSES.UI = 1551306167;
        BUSSES.UNIT = 1304109583;
        BUSSES.VOICE = 3170124113;
    })(BUSSES = AK.BUSSES || (AK.BUSSES = {})); // namespace BUSSES
    let AUDIO_DEVICES;
    (function (AUDIO_DEVICES) {
        AUDIO_DEVICES.NO_OUTPUT = 2317455096;
        AUDIO_DEVICES.SYSTEM = 3859886410;
    })(AUDIO_DEVICES = AK.AUDIO_DEVICES || (AK.AUDIO_DEVICES = {})); // namespace AUDIO_DEVICES
})(AK || (exports.AK = AK = {})); // namespace AK
let AudioConfig = class AudioConfig {
    soundBank;
    createEvent;
    detonateEvent;
    damageEvent;
    removeEvent;
};
__decorate([
    (0, ini_helper_1.IniField)("Audio.SoundBank", ReadWwiseSoundBank),
    __metadata("design:type", XkeinExt_1.WwiseSoundBankRef)
], AudioConfig.prototype, "soundBank", void 0);
__decorate([
    (0, ini_helper_1.IniField)("Audio.CreateEvent", ReadWwiseEvent),
    __metadata("design:type", Number)
], AudioConfig.prototype, "createEvent", void 0);
__decorate([
    (0, ini_helper_1.IniField)("Audio.DetonateEvent", ReadWwiseEvent),
    __metadata("design:type", Number)
], AudioConfig.prototype, "detonateEvent", void 0);
__decorate([
    (0, ini_helper_1.IniField)("Audio.DamageEvent", ReadWwiseEvent),
    __metadata("design:type", Number)
], AudioConfig.prototype, "damageEvent", void 0);
__decorate([
    (0, ini_helper_1.IniField)("Audio.RemoveEvent", ReadWwiseEvent),
    __metadata("design:type", Number)
], AudioConfig.prototype, "removeEvent", void 0);
AudioConfig = __decorate([
    (0, ini_helper_1.IniComponent)([YRpp_1.AbstractType.BulletType, YRpp_1.AbstractType.SuperWeaponType, YRpp_1.AbstractType.AircraftType, YRpp_1.AbstractType.BuildingType, YRpp_1.AbstractType.InfantryType, YRpp_1.AbstractType.UnitType])
], AudioConfig);
var EMusicState;
(function (EMusicState) {
    EMusicState[EMusicState["None"] = 0] = "None";
    EMusicState[EMusicState["Normal"] = 1] = "Normal";
    EMusicState[EMusicState["GameOver"] = 2] = "GameOver";
    EMusicState[EMusicState["Winning"] = 3] = "Winning";
    EMusicState[EMusicState["UnderAttack"] = 4] = "UnderAttack";
    EMusicState[EMusicState["Invasion"] = 5] = "Invasion";
})(EMusicState || (exports.EMusicState = EMusicState = {}));
class InteractiveMusic {
    static lastTimeBattle;
    static musicState;
    static setMusicState(state) {
        if (InteractiveMusic.musicState == state)
            return;
        InteractiveMusic.musicState = state;
        console.log("set music state" + state);
        let musicEvent;
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
let iniReaderXkein = new YrExtCore_1.IniReader("XkeinExt.ini");
let initSoundBankNames = ini_helper_1.IniHelper.ReadStringList(iniReaderXkein, "Audio", "InitSoundBanks");
if (initSoundBankNames && initSoundBankNames.length) {
    let globalSoundBanks = [];
    for (const soundBank of initSoundBankNames) {
        globalSoundBanks.push(new XkeinExt_1.WwiseSoundBankRef(soundBank));
    }
    global.__globalSoundBanks = globalSoundBanks;
}
let audio_component_add = (yrObject, entity) => {
    let audioConfig = (0, ini_helper_1.GetIniComponent)(AudioConfig, yrObject.m_Type);
    if (!audioConfig)
        return;
    if (!entity)
        entity = XkeinExt_1.JsCppHelper.GetEntityByYrObject(yrObject);
    let audioComponent = XkeinExt_1.AudioComponent.CreateAudioComponent(entity, yrObject);
    yrObject.audioComponent = audioComponent;
};
game_event_1.gameEvents.onCtor.unit.add(audio_component_add);
game_event_1.gameEvents.onCtor.infantry.add(audio_component_add);
game_event_1.gameEvents.onCtor.building.add(audio_component_add);
game_event_1.gameEvents.onCtor.aircraft.add(audio_component_add);
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrBulletConstructEvent, (E) => {
    audio_component_add(E.m_pBullet, null);
});
game_event_1.gameEvents.onCtor.superWeapon.add(audio_component_add);
game_event_1.gameEvents.onCtor.house.add(audio_component_add);
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrBulletDetonateEvent, (E) => {
    let yrObject = E.m_pBullet;
    let audioConfig = (0, ini_helper_1.GetIniComponent)(AudioConfig, yrObject.m_Type);
    if (audioConfig && audioConfig.detonateEvent) {
        let audioComponent = yrObject.audioComponent;
        XkeinExt_1.AudioSystem.SetSwitch(AK.SWITCHES.SURFACE.GROUP, XkeinExt_1.AudioSystem.GetSurfaceID(yrObject.GetCell().m_LandType), audioComponent.m_akGameObjId);
        XkeinExt_1.AudioSystem.PostEvent(audioConfig.detonateEvent, audioComponent.m_akGameObjId);
    }
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrObjectReceiveDamageEvent, (E) => {
    let yrObject = E.m_pObject;
    let audioConfig = (0, ini_helper_1.GetIniComponent)(AudioConfig, yrObject.m_Type);
    if (audioConfig && audioConfig.damageEvent) {
        XkeinExt_1.AudioSystem.SetRTPCValue(AK.GAME_PARAMETERS.OBJECTHP, yrObject.GetHealthPercentage(), yrObject.audioComponent.m_akGameObjId);
        XkeinExt_1.AudioSystem.PostEvent(audioConfig.damageEvent, yrObject.audioComponent.m_akGameObjId);
    }
    let player = YRpp_1.HouseClass.s_CurrentPlayer;
    let isPlayerAttacked = player == yrObject.GetOwningHouse();
    let isPlayerInvasion = player == E.m_pAttackingHouse;
    if (isPlayerAttacked && isPlayerInvasion) {
        // player attack own unit
        return;
    }
    if (isPlayerInvasion) {
        InteractiveMusic.setMusicState(EMusicState.Invasion);
        InteractiveMusic.lastTimeBattle = Date.now();
    }
    else if (isPlayerAttacked) {
        InteractiveMusic.setMusicState(EMusicState.UnderAttack);
        InteractiveMusic.lastTimeBattle = Date.now();
    }
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrObjectUnlimboCheckedEvent, (E) => {
    let yrObject = E.m_pObject;
    if (!yrObject.m_Type)
        return;
    let audioConfig = (0, ini_helper_1.GetIniComponent)(AudioConfig, yrObject.m_Type);
    if (audioConfig && audioConfig.createEvent) {
        XkeinExt_1.AudioSystem.PostEvent(audioConfig.createEvent, yrObject.audioComponent.m_akGameObjId);
    }
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrObjectLimboCheckedEvent, (E) => {
    let yrObject = E.m_pObject;
    if (!yrObject.m_Type)
        return;
    let audioConfig = (0, ini_helper_1.GetIniComponent)(AudioConfig, yrObject.m_Type);
    if (audioConfig && audioConfig.removeEvent) {
        XkeinExt_1.AudioSystem.PostEvent(audioConfig.removeEvent, yrObject.audioComponent.m_akGameObjId);
    }
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSceneEnterEvent, (E) => {
    InteractiveMusic.setMusicState(EMusicState.Normal);
});
game_event_1.gameEvents.registerHookEventHandler(YrExtCore_1.YrSceneExitEvent, (E) => {
    InteractiveMusic.setMusicState(EMusicState.None);
});
game_event_1.gameEvents.game.onEndUpdate.add(() => {
    if (YRpp_1.ScenarioClass.s_Instance) {
        let nextState = InteractiveMusic.musicState;
        if (InteractiveMusic.musicState == EMusicState.Invasion || InteractiveMusic.musicState == EMusicState.UnderAttack) {
            let elapsedTime = (Date.now() - InteractiveMusic.lastTimeBattle) / 1000;
            if (elapsedTime > 10) {
                nextState = EMusicState.Normal;
            }
        }
        let player = YRpp_1.HouseClass.s_CurrentPlayer;
        if (player) {
            if (player.m_IsWinner) {
                nextState = EMusicState.Winning;
            }
            else if (player.m_IsGameOver) {
                nextState = EMusicState.GameOver;
            }
        }
        InteractiveMusic.setMusicState(nextState);
    }
});
