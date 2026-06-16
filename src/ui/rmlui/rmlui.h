#pragma once

#include <memory>
#include <vector>

namespace Rml {
class Context;
class ElementDocument;
}

class YrRmlContext_Impl;
class YrRmlContext
{
    friend class YrRmlContext_Impl;

public:
    XKEINEXT_API YrRmlContext(const char* name, int width, int height);
    XKEINEXT_API virtual ~YrRmlContext();

    virtual void OnOpen() {}
    virtual void OnFrame() {}
    virtual void OnClose() {}

    XKEINEXT_API void NewFrame();
    XKEINEXT_API void Open();
    XKEINEXT_API void Close();
    XKEINEXT_API bool IsOpened() const;

    XKEINEXT_API Rml::Context* GetContext() const;

protected:
    void SetDimensions(int width, int height);
    void Update();
    void Render();

private:
    std::unique_ptr<YrRmlContext_Impl> _impl;
};

namespace YrRmlUi
{
    XKEINEXT_API void Init();
    XKEINEXT_API void Destory();

    void Render();

    XKEINEXT_API int GetOpenedWinCount();

    XKEINEXT_API extern std::vector<YrRmlContext*> gContexts;

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