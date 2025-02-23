
declare module "YRpp" {
    class _GUID { }
    class _ULARGE_INTEGER { }

    class DirStruct {
    }

    class CDTimerClass {
        Start(rate_0 : number) : void;
        Stop() : void;
        Pause() : void;
        Resume() : void;
        GetTimeLeft() : number;
        Completed() : boolean;
        InProgress() : boolean;
        Expired() : boolean;
        HasStarted() : boolean;
        IsTicking() : boolean;
        HasTimeLeft() : boolean;
        m_StartTime : number;
        m_TimeLeft : number;
    }
}
