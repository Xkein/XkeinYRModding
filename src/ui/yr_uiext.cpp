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
        _thread.detach(); // prevent thread error and endless
        // wait 1s for imgui destruction
        std::this_thread::sleep_for(1s);
    }

    void ImGuiThreadFunc()
    {
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
                TickSafe();
                std::this_thread::sleep_for(16ms);
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

    void TickSafe()
    {
        __try
        {
            Tick();
        }
        __except (ExceptionFilterGetInfo(GetExceptionInformation(), stackTrace))
        {
            gLogger->error("YrExtUI: ImGuiThread render error!");
            gLogger->error("stack trace : {}", *stackTrace);
            delete stackTrace;
            stackTrace = nullptr;
        }
    }

    void Tick()
    {
        std::unique_lock lk(mtx);
        cv.wait(lk);
        YrImGui::Render();
    }

    std::string* stackTrace;
    bool         shouldStop {false};
    std::thread _thread;

    std::mutex              mtx;
    std::condition_variable cv;
};

std::unique_ptr<ImGuiThread> imguiThread;

REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, []() {
    imguiThread->cv.notify_one();
})
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, []() {

})

GLOBAL_INVOKE_ON_CTOR_DTOR([]() {
    gLogger->info("Yr Extension UI module load.");
    imguiThread = std::make_unique<ImGuiThread>();
}, []() {
	gLogger->info("Yr Extension UI module unload.");
})