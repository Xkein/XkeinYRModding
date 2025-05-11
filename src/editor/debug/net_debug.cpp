#include "editor/editor.h"
#include "yr/network/net_pack.h"
#include "runtime/logger/logger.h"
#include "core/string/string_tool.h"
#include <MessageListClass.h>
#include <HouseClass.h>

struct NetEventDebug {
    int counter;
    void Execute(EventPack<NetEventDebug>& eventPack) {
        gLogger->info("net event debug pack executed: {}", counter);
        std::wstring msg = widen(std::string("net event debug pack executed: ") + std::to_string(counter));
        MessageListClass::Instance->PrintMessage(msg.c_str());
    }
};

GLOBAL_INVOKE_ON_CTOR([]() {
    NetPackDispatch::RegisterCustomEvent<NetEventDebug>();
});

struct NetDebugWindow : public YrEditorWindow
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
        if (!ImGui::Begin("net debug tool", &isShow))
        {
            ImGui::End();
            return;
        }
        if (!isShow)
            this->Close();

        if (ImGui::Button("Send Net Debug Pack") && ScenarioClass::Instance) {
            static int counter = 0;
            EventPack<NetEventDebug> pack;
            pack.Data.counter = ++counter;
            NetPackDispatch::AddEvent(pack);
        }

        ImGui::End();
    }
    bool isShow {false};
};

IMPL_EDITOR_WINDOW(NetDebugWindow, "net_debug_tool");
