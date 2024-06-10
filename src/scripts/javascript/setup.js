var global = global || (function () { return this; }());
// setup logger
(function (global) {
    "use strict";
    
    let levels = ['log', 'info', 'warn', 'error']

    let sendRequestSync = puerts.sendRequestSync;
    
    let tgjsLog = global.__tgjsLog || function(nlevel, msg) {
        sendRequestSync(levels[nlevel], msg);
    }
    global.__tgjsLog = undefined;

    const console_org = global.console;
    var console = {}

    function log(level, args) {
        tgjsLog(level, Array.prototype.map.call(args, x => {
            try {
                return x+'';
            } catch (err){
                return err;
            }
        }).join(','));
    }

    console.log = function() {
        if (console_org) console_org.log.apply(null, Array.prototype.slice.call(arguments));
        log(0, arguments);
    }

    console.info = function() {
        if (console_org) console_org.info.apply(null, Array.prototype.slice.call(arguments));
        log(1, arguments);
    }

    console.warn = function() {
        if (console_org) console_org.warn.apply(null, Array.prototype.slice.call(arguments));
        log(2, arguments);
    }

    console.error = function() {
        if (console_org) console_org.error.apply(null, Array.prototype.slice.call(arguments));
        log(3, arguments);
    }

    global.puerts.console = console;
    global.console = console;
}(global));
