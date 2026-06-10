#include "yr/hooks/render_sync_hooks.h"

// 渲染 Hook 安装点汇总
// 各 Hook 通过 Syringe 框架注入到原引擎渲染入口：
//
//   1. CC_Draw_Shape (0x4AED70) → SHP 精灵渲染
//   2. TechnoClass::DrawVoxel → VXL 体素渲染
//   3. TacticalClass::Render eMode=Surface   → 地形瓦片渲染
//   4. TacticalClass::Render eMode=Particle → 粒子渲染
//   5. LaserDrawClass::DrawAll → 激光渲染
//   6. Text printing → 文字渲染
//
// 当启用 UE5 渲染 + 关闭原引擎渲染时，这些 Hook 直接返回，跳过渲染
//
// 参考: render_debug_switch.cpp 定义 ShouldSkipOriginalRender()

void RenderSyncHooks::InstallHooks()
{
    // TODO: 通过 Syringe DEFINE_HOOK 注入各渲染入口
    // CC_Draw_Shape hook:
    //   DEFINE_HOOK(0x4AED70, CC_Draw_Shape_Hook, 0)
    //   {
    //       if (RenderDebugSwitch::ShouldSkipOriginalRender())
    //           return 0; // 跳过渲染，不调用原函数
    //       return 0; // 执行原函数
    //   }
    //
    // 其他 Hook 类似
}

void RenderSyncHooks::RemoveHooks()
{
    // TODO: 移除 Hook
}