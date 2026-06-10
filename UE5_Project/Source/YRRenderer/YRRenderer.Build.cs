// YRRenderer.Build.cs
// UE5 渲染前端模块，负责接收 gamemd 同步数据并驱动渲染
// 复制到 UE5 Project/Source/YRRenderer/ 目录

using UnrealBuildTool;

public class YRRenderer : ModuleRules
{
    public YRRenderer(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "RenderCore",
            "Renderer",
            "RHI",
            "Slate",
            "SlateCore",
            "UMG",
            "Niagara",
            "Projects"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "RenderGraph",
            "ComputeShader"
        });
    }
}