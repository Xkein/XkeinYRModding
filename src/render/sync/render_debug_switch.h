#pragma once

// 全局调试开关 Hook
// 当 ue5_render_enabled && !enable_original_render 时，
// 在 CC_Draw_Shape / DrawVoxel / LaserDraw 等渲染入口处跳过原始渲染
// 但保留 Z-Buffer 维护逻辑（后续在总开关关闭时一并关闭）

namespace RenderDebugSwitch
{
    void Initialize();
    bool ShouldSkipOriginalRender();
    bool ShouldSkipZBuffer(); // Z-Buffer 也可以跳过（UE5 自建）
}