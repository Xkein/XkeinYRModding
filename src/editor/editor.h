#pragma once
#include "ui/imgui/yr_imgui.h"
#include "core/raii_invoker.h"
#include <string_view>

class YrEditorWindow_Impl;

class YrEditorWindow
{
    friend class YrEditorWindow_Impl;
    friend class YrEditor;
protected:
    XKEINEDITOR_API YrEditorWindow();
    virtual void OnOpen() {}
    virtual void OnFrame() {}
    virtual void OnClose() {}
public:
    XKEINEDITOR_API virtual ~YrEditorWindow();
    XKEINEDITOR_API void NewFrame();
    XKEINEDITOR_API void Open();
    XKEINEDITOR_API void Close();
    XKEINEDITOR_API bool IsOpened() const;
    
    template<typename T>
    static void SwitchEditorWindow(std::shared_ptr<T>& ptr, bool destroyClose = false)
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
private:
    std::unique_ptr<YrEditorWindow_Impl> _impl;
};

struct YrEditorKeyListener
{
    using ListenerFuncType = bool(*)();
    static void Register(std::string_view config, ListenerFuncType listener);
    static void Unregister(std::string_view config, ListenerFuncType listener);
};
#define IMPL_EDITOR_WINDOW(CLASS, KEY_CONFIG)                                           \
    bool __##CLASS##KeyListener() {                                                     \
        static std::shared_ptr<CLASS> __##CLASS;                                        \
        YrEditorWindow::SwitchEditorWindow(__##CLASS);                                  \
        return true;                                                                    \
    }                                                                                   \
    GLOBAL_INVOKE_ON_CTOR_DTOR(                                                         \
        []() {YrEditorKeyListener::Register(KEY_CONFIG, __##CLASS##KeyListener);}       \
        , []() {YrEditorKeyListener::Unregister(KEY_CONFIG, __##CLASS##KeyListener);}) \
