const global = this;

// load cpp types
require("yrlazyload")
const YRpp = require("YRpp")
const YrExtCore = require("YrExtCore")
const gainput = require("gainput")
const wwise = require("wwise")
const XkeinExt = require("XkeinExt")

global.getCppTypeName = function (type) {
    return type.__ClassName;
}

require("ini_helper")
require("game_event")
require("game_audio")
require("game_script")
