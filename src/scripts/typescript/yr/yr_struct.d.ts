
declare module "YRpp" {
    class _GUID { }
    class _ULARGE_INTEGER { }

    class DirStruct {
        constructor();
        constructor(radian : number);
        constructor(dirType : DirType);
        op_Equality(a: DirStruct) : boolean;
        op_Inequality(a: DirStruct) : boolean;
        SetDir(dirType: DirType) : void;
        GetDir() : DirType;
        SetRadian(radian: number) : void;
        GetRadian() : number;
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
