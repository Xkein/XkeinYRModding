export declare namespace AK {
    namespace EVENTS {
        const M_GAMEOVER = 155272345;
        const M_INVASION = 4033210584;
        const M_NONE = 443355295;
        const M_NORMAL = 2309605244;
        const M_UNDERATTACK = 2821901421;
        const M_WINNING = 3431848355;
    }
    namespace STATES {
        namespace MUSIC {
            const GROUP = 3991942870;
            namespace STATE {
                const GAMEOVER = 4158285989;
                const INVASION = 1335043396;
                const NONE = 748895195;
                const NORMAL = 1160234136;
                const UNDERATTACK = 2862835585;
                const WINNING = 2996998095;
            }
        }
    }
    namespace SWITCHES {
        namespace SURFACE {
            const GROUP = 1834394558;
            namespace SWITCH {
                const BEACH = 4075332698;
                const CLEAR = 1754255536;
                const ICE = 344481046;
                const RAILROAD = 2722214071;
                const ROAD = 2110808655;
                const ROCK = 2144363834;
                const ROUGH = 1262240040;
                const TIBERIUM = 3960883458;
                const TUNNEL = 3059984139;
                const WALL = 2108779961;
                const WATER = 2654748154;
                const WEEDS = 588027413;
            }
        }
    }
    namespace GAME_PARAMETERS {
        const OBJECTHP = 1335699628;
    }
    namespace BANKS {
        const INIT = 1355168291;
        const ENGINEUSED = 2066667852;
    }
    namespace BUSSES {
        const _3D_BUS = 2337546123;
        const ENVIRONMENT = 1229948536;
        const EVA = 932389257;
        const MASTER_AUDIO_BUS = 3803692087;
        const MUSIC = 3991942870;
        const SOUNDS = 1492361653;
        const UI = 1551306167;
        const UNIT = 1304109583;
        const VOICE = 3170124113;
    }
    namespace AUDIO_DEVICES {
        const NO_OUTPUT = 2317455096;
        const SYSTEM = 3859886410;
    }
}
export declare enum EMusicState {
    None = 0,
    Normal = 1,
    GameOver = 2,
    Winning = 3,
    UnderAttack = 4,
    Invasion = 5
}
