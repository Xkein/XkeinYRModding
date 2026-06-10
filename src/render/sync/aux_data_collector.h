#pragma once

#include "render/sync/sync_aux_types.h"
#include <vector>

// Cell/Overlay/Smudge/Laser 状态收集器
// 在渲染帧中 Hook 相关函数，收集数据供 SyncDataCollector 使用

class AuxDataCollector
{
public:
    static void BeginFrame();
    static void EndFrame();

    // 获取本帧收集的数据（由 SyncDataCollector 调用）
    static const std::vector<CellUpdate>& GetCellChanges()    { return _cellChanges; }
    static const std::vector<LaserData>&  GetLasers()         { return _lasers; }
    static const std::vector<TextData>&   GetTexts()          { return _texts; }
    static const std::vector<ParticleData>& GetParticles()    { return _particles; }

    // Hook 回调（由渲染 Hook 调用）
    static void OnCellFogChanged(int32_t cx, int32_t cy, bool revealed, bool fogged);
    static void OnLaserDrawn(const LaserData& laser);
    static void OnTextDrawn(const TextData& text);
    static void OnParticleDrawn(const ParticleData& particle);

    static void InstallHooks();
    static void RemoveHooks();

private:
    static thread_local std::vector<CellUpdate> _cellChanges;
    static thread_local std::vector<LaserData>  _lasers;
    static thread_local std::vector<TextData>   _texts;
    static thread_local std::vector<ParticleData> _particles;
};