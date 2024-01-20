#pragma once

class Ini;
class IniSection;
class IniAsset;

class IReadTask
{
public:
    virtual void Read(Ini& ini) = 0;

    virtual void ReadCustom() = 0;
};

struct ScheduleReadInfo
{
    IReadTask* task {nullptr};
    // if true, IReadTask::ReadCustom() will be invoked
    bool       custom {false};
    bool       rules {false};
    bool       art {false};
    bool       ai {false};
    bool       async {true};
};


class ReadScheduler
{
public:
    static void ScheduleRead(ScheduleReadInfo readInfo);

    static void ClearAllTasks();

    static void Tick();

    static void Preload();

    static bool HasTasks();

    static void Clear();

private:

    static void ReadImmediately(const ScheduleReadInfo& readInfo);

};