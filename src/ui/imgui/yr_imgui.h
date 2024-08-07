#pragma once

#include <imgui.h>
#include <memory>
#include <vector>

class YrImGuiWindow_Impl;
class YrImGuiWindow
{
    friend class YrImGuiWindow_Impl;

protected:
    YREXTUI_API YrImGuiWindow();
    virtual void OnOpen() {}
    virtual void OnFrame() {}
    virtual void OnClose() {}
    
public:
    YREXTUI_API virtual ~YrImGuiWindow();
    YREXTUI_API void NewFrame();
    YREXTUI_API void Open();
    YREXTUI_API void Close();
    YREXTUI_API bool IsOpened() const;

private:
    std::unique_ptr<YrImGuiWindow_Impl> _impl;
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

    YREXTUI_API int GetOpenedWinCount();

    extern YREXTUI_API std::vector<YrImGuiWindow*> gWindows;

    template<typename T>
    void SwitchWindow(std::shared_ptr<T>& ptr, bool destroyClose = false)
    {
        if (!ptr)
        {
            ptr = std::make_shared<T>();
        }
        if (ptr->IsOpened())
        {
            ptr->Close();
            if (destroyClose)
                ptr.reset();
        }
        else
        {
            ptr->Open();
        }
    }
};
