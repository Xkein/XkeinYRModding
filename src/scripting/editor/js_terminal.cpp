#include "javascript/js_env.h"
#include <ui/imgui/yr_imgui.h>
#include <core/logger/logger.h>
#include "yr/event/general_event.h"
#include "yr/event/ui_event.h"
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
        ImGui::InputTextMultiline("##command", buffer, IM_ARRAYSIZE(buffer), ImVec2(800, ImGui::GetTextLineHeight() * 16), flags);
        if (isEnterToRun ? ImGui::IsKeyReleased(ImGuiKey_Enter) : ImGui::Button("Run"))
        {
            if (gJsEnv->Eval(buffer, "(terminal)"))
            {
                gLogger->info(gJsEnv->ObjectToString(gJsEnv->ResultInfo.Result));
            }
            else
            {
                gLogger->error(gJsEnv->LastExceptionInfo);
            }
            if (isEnterToRun)
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

static void Update()
{
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
}

REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, Update)
REGISTER_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent, Update)
