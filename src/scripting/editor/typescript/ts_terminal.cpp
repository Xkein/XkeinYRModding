#include "javascript/js_env.h"
#include <ui/imgui/yr_imgui.h>
#include <core/logger/logger.h>
#include "yr/event/general_event.h"
#include <sstream>

class TerminalWindow : public YrImGuiWindow
{
public:
    virtual void OnFrame() override
    {
        ImGui::Begin("JavaScript Terminal");

        ImGui::Text("terminal");
        ImGui::Checkbox("EnterToRun", &isEnterToRun);
        ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
        if (isEnterToRun)
        {
            flags |= ImGuiInputTextFlags_EnterReturnsTrue;
        }
        bool isEnter = ImGui::InputTextMultiline("##command", buffer, IM_ARRAYSIZE(buffer), ImVec2(800, ImGui::GetTextLineHeight() * 16), flags);
        if (isEnterToRun ? isEnter : ImGui::Button("Run"))
        {
            gJsEnv->Eval(buffer, "(terminal)");
            if (isEnter)
            {
                buffer[0] = '\0';
            }
        }
        ImGui::End();
    }

    char buffer[1024 * 16];
    bool isEnterToRun {true};
};

std::shared_ptr<TerminalWindow> terminal;

REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, []() {
    if (ImGui::IsKeyReleased(ImGuiKey_GraveAccent))
    {
        if (terminal)
        {
            terminal->Close();
            terminal.reset();
        }
        else
        {
            terminal = std::make_shared<TerminalWindow>();
            terminal->Open();
        }
    }
})
