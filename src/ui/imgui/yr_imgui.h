#pragma once

#include <imgui.h>
#include <memory>
#include <vector>

class YrImGuiWindow_Impl;
class YrImGuiWindow
{
    friend class YrImGuiWindow_Impl;

protected:
    XKEINEXT_API YrImGuiWindow();
    virtual void OnOpen() {}
    virtual void OnFrame() {}
    virtual void OnClose() {}
    
public:
    XKEINEXT_API virtual ~YrImGuiWindow();
    XKEINEXT_API void NewFrame();
    XKEINEXT_API void Open();
    XKEINEXT_API void Close();
    XKEINEXT_API bool IsOpened() const;

private:
    std::unique_ptr<YrImGuiWindow_Impl> _impl;
};

namespace YrImGui
{
    void Init();
    void Destory();
    
    XKEINEXT_API ImTextureID LoadTexture(const char* path);
    XKEINEXT_API ImTextureID CreateTexture(const void* data, int width, int height);
    XKEINEXT_API void        DestroyTexture(ImTextureID texture);
    XKEINEXT_API int         GetTextureWidth(ImTextureID texture);
    XKEINEXT_API int         GetTextureHeight(ImTextureID texture);

    void SetDpiScale(float dpiScale);

    void Render();

    XKEINEXT_API int GetOpenedWinCount();

    extern XKEINEXT_API std::vector<YrImGuiWindow*> gWindows;

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
