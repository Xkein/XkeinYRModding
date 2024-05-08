#pragma once

#include <imgui.h>
#include <memory>
#include <vector>

class YrImGuiWindow
{
protected:
    YREXTUI_API YrImGuiWindow();
    virtual void OnStart() {}
    virtual void OnFrame() {}
    virtual void OnStop() {}

public:
    YREXTUI_API virtual ~YrImGuiWindow();
    void NewFrame();

private:
    bool _started {false};
};

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

    extern YREXTUI_API std::vector<YrImGuiWindow*> gWindows;
};
