#pragma once
#include "ui/imgui/yr_imgui.h"

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
private:
    std::unique_ptr<YrEditorWindow_Impl> _impl;
};

class YrEditor final : public YrImGuiWindow
{

    virtual void OnOpen() override;
    virtual void OnClose() override;
    virtual void OnFrame() override;

public:
    YrEditor();
    virtual ~YrEditor();
    
    std::vector<std::unique_ptr<YrEditorWindow>> windows;
};

extern XKEINEDITOR_API std::shared_ptr<YrEditor> gYrEditor;