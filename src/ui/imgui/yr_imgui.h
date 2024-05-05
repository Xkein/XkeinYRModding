#pragma once

# include <imgui.h>

namespace YrImGui
{
    void Init();
    void Destory();
    
    YREXTUI_API ImTextureID LoadTexture(const char* path);
    YREXTUI_API ImTextureID CreateTexture(const void* data, int width, int height);
    YREXTUI_API void        DestroyTexture(ImTextureID texture);
    YREXTUI_API int         GetTextureWidth(ImTextureID texture);
    YREXTUI_API int         GetTextureHeight(ImTextureID texture);

    void SetDpiScale(float dpiScale);

    void Render();
    
    extern YREXTUI_API void (*OnFrame)(float deltaTime);
};