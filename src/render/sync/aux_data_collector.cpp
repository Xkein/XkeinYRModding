#include "render/sync/aux_data_collector.h"
#include "render/sync/render_debug_switch.h"

#include <Syringe.h>
#include <Helpers/Macro.h>
#include <CellClass.h>
#include <LaserDrawClass.h>
#include <ArrayClasses.h>
#include <Surface.h>
#include <Unsorted.h>

#include <windows.h>

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


// ============================================================================
// Syringe Hook — Cell Fog
// Hook CellClass::Unshroud (0x4876F0)
// 该函数在 Cell 被揭示（revealed）时调用，设置 AltFlags |= 0x18
// ============================================================================

DEFINE_HOOK(0x4876F0, Aux_CellUnshroud_Hook, 5)
{
    CellClass* pCell = R->ECX<CellClass*>();
    AuxDataCollector::OnCellFogChanged(
        pCell->MapCoords.X,
        pCell->MapCoords.Y,
        true,   // revealed
        false   // fogged
    );
    return 0;
}


// ============================================================================
// Syringe Hook — Lasers
// Hook sub_550240: LaserDrawClass 帧渲染入口
// 遍历 LaserDrawClass::Array (0xABC878) 并调用 Draw 函数
// 我们在原函数执行前收集激光数据
// ============================================================================

DEFINE_HOOK(0x550240, Aux_LaserDrawAll_Hook, 6)
{
    auto& laserArray = *reinterpret_cast<DynamicVectorClass<LaserDrawClass*>*>(0xABC878);
    for (int i = 0; i < laserArray.Count; ++i) {
        LaserDrawClass* pLaser = laserArray.Items[i];
        if (!pLaser) continue;

        LaserData data{};
        data.StartX = static_cast<float>(pLaser->Source.X);
        data.StartY = static_cast<float>(pLaser->Source.Y);
        data.StartZ = static_cast<float>(pLaser->Source.Z);
        data.EndX   = static_cast<float>(pLaser->Target.X);
        data.EndY   = static_cast<float>(pLaser->Target.Y);
        data.EndZ   = static_cast<float>(pLaser->Target.Z);
        data.InnerColor = (pLaser->InnerColor.R << 16) | (pLaser->InnerColor.G << 8) | pLaser->InnerColor.B;
        data.OuterColor = (pLaser->OuterColor.R << 16) | (pLaser->OuterColor.G << 8) | pLaser->OuterColor.B;

        // 根据 LaserDrawClass 字段区分激光类型
        // 0=Standard, 1=Sonic, 2=BigLaser, 3=Magnetron
        if (pLaser->IsSupported)
            data.Type = 3; // Magnetron (持续光束)
        else if (pLaser->IsHouseColor)
            data.Type = 2; // BigLaser (阵营色激光)
        else if (pLaser->Blinks)
            data.Type = 2; // BigLaser (闪烁激光)
        else
            data.Type = 0; // Standard
        // TODO: Sonic (Type=1) 可能使用不同的渲染路径，不走 LaserDrawClass，待逆向确认

        AuxDataCollector::OnLaserDrawn(data);
    }
    // 如果 UE5 渲染开启，跳过原引擎激光渲染
    if (RenderDebugSwitch::ShouldSkipOriginalRender())
        return 1;
    return 0;
}


// ============================================================================
// Syringe Hook — Text Drawing
// Hook sub_6D4E20 (0x6D4E20): 文字渲染入口
// 签名: void __thiscall sub_6D4E20(void* this, wchar_t* String)
//   ECX = this (TacticalInstance/DisplayClass)
//   Stack[0x4] = wchar_t* String
// ============================================================================

DEFINE_HOOK(0x6D4E20, Aux_TextDraw_Hook, 5)
{
    wchar_t* pString = R->Stack<wchar_t*>(0x4);
    if (pString && wcslen(pString) > 0)
    {
        TextData data{};

        // 计算屏幕坐标（文本在 ViewBounds 中居中绘制，参考 sub_6D4E20）
        data.ScreenX = static_cast<float>(DSurface::ViewBounds->X + DSurface::ViewBounds->Width / 2);
        data.ScreenY = static_cast<float>(DSurface::ViewBounds->Y + DSurface::ViewBounds->Height / 2);

        // wchar_t -> char 转换
        WideCharToMultiByte(CP_ACP, 0, pString, -1, data.Text, sizeof(data.Text) - 1, nullptr, nullptr);
        data.Text[sizeof(data.Text) - 1] = '\0';

        // 从 ColorPackData 计算当前文本颜色（参考 sub_6D4E20）
        auto& cpd = *Unsorted::ColorPackData;
        uint32_t r = (255u >> cpd._R_SHR) << cpd._R_SHL;
        uint32_t g = (255u >> cpd._G_SHR) << cpd._G_SHL;
        uint32_t b = (255u >> cpd._B_SHR) << cpd._B_SHL;
        data.Color = 0xFF000000 | (r << 16) | (g << 8) | b;

        data.Style = 0;

        AuxDataCollector::OnTextDrawn(data);
    }
    // 如果 UE5 渲染开启，跳过原引擎文字渲染（与 render_sync_hooks 合并）
    if (RenderDebugSwitch::ShouldSkipOriginalRender())
        return 1;
    return 0;
}


// ============================================================================
// Particle — TODO (需进一步逆向)
// ============================================================================
//
// 已确认:
//   - ParticleClass::Array 位于 0xA83DC8 (DynamicVectorClass<ParticleClass*>)
//   - ParticleClass 通过 CC_Draw_Shape 渲染（已被 RenderSync_CCDrawShape 覆盖）
//   - ParticleClass 构造函数: 0x62B5E0
//
// 待确认:
//   - ParticleClass::Update/Draw 的 vtable 偏移（用于收集粒子位置、帧、生命周期等）
//   - ParticleClass::vt_entry_1E8() 可能为 Update 或 Draw 函数
//
// 当前方案: 粒子渲染跳过已通过 CC_Draw_Shape Hook 实现
// 粒子数据收集暂标记为 TODO，后续逆向确认更新函数地址后添加:
//
//   DEFINE_HOOK(particle_update_addr, Aux_ParticleUpdate_Hook, 5)
//   {
//       ParticleClass* pParticle = R->ECX<ParticleClass*>();
//       ParticleData data{};
//       data.PosX = static_cast<float>(...);
//       data.PosY = static_cast<float>(...);
//       ...
//       AuxDataCollector::OnParticleDrawn(data);
//       return 0;
//   }


// ============================================================================
// InstallHooks / RemoveHooks
// Syringe DEFINE_HOOK 通过 .sypat section 自动安装/卸载，
// 此处仅做初始化标记，供外部控制生命周期
// ============================================================================

void AuxDataCollector::InstallHooks()
{
    // DEFINE_HOOK 通过 .sypat section 自动安装，此处无需额外操作
}

void AuxDataCollector::RemoveHooks()
{
    // DEFINE_HOOK 通过 .sypat section 自动卸载，此处无需额外操作
}