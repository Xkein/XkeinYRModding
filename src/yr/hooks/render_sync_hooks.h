#pragma once

// 注入到主要渲染入口的 Hook
// 当 RenderDebugSwitch::ShouldSkipOriginalRender() 为 true 时，跳过原引擎渲染
// 即使跳过渲染，数据收集仍在 SyncDataCollector::Tick() 中正常进行

class RenderSyncHooks
{
public:
    static void InstallHooks();
    static void RemoveHooks();
};