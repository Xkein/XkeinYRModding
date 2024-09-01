#include "editor/editor.h"

struct DemoWindow : public YrEditorWindow
{
    virtual void OnOpen() override
    {
        isShow = true;
    }
    virtual void OnClose()
    {
        isShow = false;
    }

    virtual void OnFrame() override
    {
        ImGui::ShowDemoWindow(&isShow);
        if (!isShow)
            this->Close();
    }
    bool isShow {false};
};

IMPL_EDITOR_WINDOW(DemoWindow, "imgui_demo");
