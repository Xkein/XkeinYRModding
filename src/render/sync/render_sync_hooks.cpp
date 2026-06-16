#include "render/sync/render_sync_hooks.h"
#include "render/sync/render_debug_switch.h"

#include <Syringe.h>
#include <Helpers/Macro.h>

// ============================================================================
// 渲染跳过 Hook
// 当 RenderDebugSwitch::ShouldSkipOriginalRender() 为 true 时，跳过原引擎渲染
// 数据收集已在 AuxDataCollector 的 Hook 中独立完成
// ============================================================================

// --- CC_Draw_Shape (0x4AED70): SHP 精灵渲染 ---

DEFINE_HOOK(0x4AED70, RenderSync_CCDrawShape, 5)
{
    if (RenderDebugSwitch::ShouldSkipOriginalRender())
        return 1;
    return 0;
}

// --- TechnoClass::DrawVoxel (0x706640): VXL 体素渲染 ---

DEFINE_HOOK(0x706640, RenderSync_DrawVoxel, 5)
{
    if (RenderDebugSwitch::ShouldSkipOriginalRender())
        return 1;
    return 0;
}

// --- LaserDrawClass (0x550240): 激光渲染 ---
// 激光 Hook 与 AuxDataCollector 共用 0x550240，skip-render 逻辑已在 aux_data_collector.cpp 中合并处理
// 此处不需要额外 Hook

// --- sub_6D6D10 (0x6D6D10): 地形覆盖物渲染 ---
// 遍历 Cell，绘制 Overlay（树木、岩石等）和 OverlayShadow
// 内部调用 CellClass::DrawOverlay / CellClass::DrawOverlayShadow

DEFINE_HOOK(0x6D6D10, RenderSync_TerrainOverlay, 5)
{
    if (RenderDebugSwitch::ShouldSkipOriginalRender())
        return 1;
    return 0;
}

// --- sub_6D4E20 (0x6D4E20): 文字渲染 ---
// 文字 Hook 与 AuxDataCollector 共用 0x6D4E20，skip-render 逻辑已在 aux_data_collector.cpp 中合并处理
// 此处不需要额外 Hook

// --- 粒子渲染 ---
// ParticleClass::Draw 最终走 CC_Draw_Shape (0x4AED70)，已被上面的 RenderSync_CCDrawShape 覆盖
// 无需额外 Hook


// ============================================================================
// InstallHooks / RemoveHooks
// Syringe DEFINE_HOOK 通过 .sypat section 自动安装/卸载
// ============================================================================

void RenderSyncHooks::InstallHooks()
{
    // DEFINE_HOOK 通过 .sypat section 自动安装，此处无需额外操作
}

void RenderSyncHooks::RemoveHooks()
{
    // DEFINE_HOOK 通过 .sypat section 自动卸载，此处无需额外操作
}