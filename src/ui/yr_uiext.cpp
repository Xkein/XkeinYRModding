#include "core/raii_invoker.h"
#include "yr/event/general_event.h"
#include "ui/imgui/yr_imgui.h"
#include <Unsorted.h>
#include "core/logger/logger.h"
#include <thread>
#include "yr/debug_util.h"

using namespace std::chrono_literals;

struct ImGuiThread
{
    ImGuiThread()
    {
        _thread = std::thread(&ImGuiThread::ImGuiThreadFunc, this);
    }
    ~ImGuiThread()
    {
        shouldStop = true;
        _thread.detach();
        // wait imgui destruction
        std::this_thread::sleep_for(1s);
    }

    void ImGuiThreadFunc()
    {
        std::string* stackTrace;
        __try
        {
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
                __try
                {
                    YrImGui::Render();
                    std::this_thread::sleep_for(16ms);
                }
                __except (ExceptionFilterGetInfo(GetExceptionInformation(), stackTrace))
                {
                    gLogger->error("YrExtUI: ImGuiThread render error!");
                    gLogger->error("stack trace : {}", *stackTrace);
                    delete stackTrace;
                    stackTrace = nullptr;
                }
            }

            gLogger->info("YrExtUI: imgui thread loop stop.");

            YrImGui::Destory();
            gLogger->info("YrExtUI: imgui thread end.");
        }
        __except (ExceptionFilterGetInfo(GetExceptionInformation(), stackTrace))
        {
            gLogger->error("YrExtUI: ImGuiThread error!");
            gLogger->error("stack trace : {}", *stackTrace);
            delete stackTrace;
            stackTrace = nullptr;
        }
    }

    bool        shouldStop;
    std::thread _thread;
};

std::unique_ptr<ImGuiThread> imguiThread;

#include <core/logger/logger.h> 
GLOBAL_INVOKE_ON_CTOR_DTOR([]() {
    gLogger->info("Yr Extension UI module load.");
    imguiThread = std::make_unique<ImGuiThread>();
}, []() {
	gLogger->info("Yr Extension UI module unload.");
})