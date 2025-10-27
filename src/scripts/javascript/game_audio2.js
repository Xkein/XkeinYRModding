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
const XkeinExt_1 = require("XkeinExt");
const ini_helper_1 = require("./ini_helper");
function ReadWwiseSoundBank(iniReader, section, key) {
    let soundBankName = ini_helper_1.IniHelper.ReadString(iniReader, section, key);
    return soundBankName ? new XkeinExt_1.WwiseSoundBankRef(soundBankName) : null;
}
function ReadWwiseEvent(iniReader, section, key) {
    let eventName = ini_helper_1.IniHelper.ReadString(iniReader, section, key);
    return eventName ? XkeinExt_1.AudioSystem.GetIDFromString(eventName) : null;
}
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
    (0, ini_helper_1.IniComponent)([gameEvents.bulletType, gameEvents.superWeaponType].concat(gameEvents.technoTypeGroupEvents))
], AudioConfig);
