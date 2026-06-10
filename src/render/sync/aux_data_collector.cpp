#include "render/sync/aux_data_collector.h"

thread_local std::vector<CellUpdate>  AuxDataCollector::_cellChanges;
thread_local std::vector<LaserData>   AuxDataCollector::_lasers;
thread_local std::vector<TextData>    AuxDataCollector::_texts;
thread_local std::vector<ParticleData> AuxDataCollector::_particles;

void AuxDataCollector::BeginFrame()
{
    _cellChanges.clear();
    _lasers.clear();
    _texts.clear();
    _particles.clear();
}

void AuxDataCollector::EndFrame()
{
    // 数据已就绪，等待 SyncDataCollector 读取
}

void AuxDataCollector::OnCellFogChanged(int32_t cx, int32_t cy, bool revealed, bool fogged)
{
    _cellChanges.push_back({ cx, cy, revealed, fogged, false });
}

void AuxDataCollector::OnLaserDrawn(const LaserData& laser)
{
    _lasers.push_back(laser);
}

void AuxDataCollector::OnTextDrawn(const TextData& text)
{
    _texts.push_back(text);
}

void AuxDataCollector::OnParticleDrawn(const ParticleData& particle)
{
    _particles.push_back(particle);
}

void AuxDataCollector::InstallHooks()
{
    // TODO: 安装各数据收集 Hook
    // 1. Cell Fog: Hook MapClass::RevealCell / MapClass::ShroudCell
    // 2. Laser: Hook LaserDrawClass::DrawAll (0x6F2900)
    // 3. Text: Hook 文字渲染函数
    // 4. Particle: Hook ParticleClass::Draw / ParticleSystemClass::Draw
}

void AuxDataCollector::RemoveHooks()
{
    // TODO: 移除 Hook
}