
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
        GetTimeLeft() : void;
        Completed() : void;
        InProgress() : void;
        Expired() : void;
        HasStarted() : void;
        IsTicking() : void;
        HasTimeLeft() : void;
        mStartTime : number;
        mTimeLeft : number;
    }
}
