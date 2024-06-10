#include "ui/yr_uiext.h"
#include "yr/event/general_event.h"
#include "yr/event/ui_event.h"
#include "ui/imgui/yr_imgui.h"
#include <Unsorted.h>
#include "core/logger/logger.h"
#include <thread>
#include "yr/debug_util.h"

using namespace std::chrono_literals;

extern std::mutex windowMtx;
static bool       isMainThread = false;

struct ImGuiThread
{
    ImGuiThread()
    {
        _thread = std::thread(&ImGuiThread::ImGuiThreadFunc, this);
    }
    ~ImGuiThread()
    {
        shouldStop = true;
        _thread.detach(); // prevent thread error and endless
        // wait 1s for imgui destruction
        std::this_thread::sleep_for(1s);
    }

    void ImGuiThreadFunc()
    {
        GuardExecute([this]() {
            std::this_thread::sleep_for(200ms);
            while (!Game::hWnd)
            {
                gConsole->info("YrExtUI: could not acquire HWND!");
                std::this_thread::sleep_for(50ms);
            }

            gLogger->info("YrExtUI: imgui thread begin.");
            YrImGui::Init();

            while (!shouldStop)
            {
                Tick();
                std::this_thread::sleep_for(16ms);
            }

            gLogger->info("YrExtUI: imgui thread loop stop.");

            YrImGui::Destory();
            gLogger->info("YrExtUI: imgui thread end.");
        }, [](std::string stackTrace) {
            gLogger->error("YrExtUI: ImGuiThread error!");
            gLogger->error("stack trace : {}", stackTrace);
        });
    }

    void Tick()
    {
        GuardExecute([]() {
            windowMtx.lock();

            if (YrImGui::GetOpenedWinCount() == 0 && !isMainThread)
            {
                YrImGui::Render();
            }
        }, []() {
            windowMtx.unlock();
        });
    }

    bool         shouldStop {false};
    std::thread _thread;
};

std::unique_ptr<ImGuiThread> imguiThread;

void UIMainThread()
{
    if (YrImGui::GetOpenedWinCount() > 0)
    {
        isMainThread = true;
        YrImGui::Render();
    }
    else if (isMainThread)
    {
        YrImGui::Render();
        isMainThread = false;
    }
}

REGISTER_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent, []() {
    ImGui::GetIO().MouseDrawCursor = false;
    UIMainThread();
})

REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, []() {
})

REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, []() {
    ImGui::GetIO().MouseDrawCursor = true;
    UIMainThread();
})

REGISTER_YR_HOOK_EVENT_LISTENER(YrBeginRenderEvent, []() {
})

REGISTER_YR_HOOK_EVENT_LISTENER(YrEndRenderEvent, []() {
})

void YrExtUIModule::Startup()
{
    gLogger->info("Yr Extension UI module load.");
    imguiThread = std::make_unique<ImGuiThread>();
}

void YrExtUIModule::Shutdown()
{
    gLogger->info("Yr Extension UI module unload.");
}
