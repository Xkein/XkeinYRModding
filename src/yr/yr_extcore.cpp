
#include "yr/extcore_config.h"
#include "yr/extension_manager.h"
#include "runtime/logger/logger.h"
#include "core/raii_invoker.h"
#include <filesystem>

void InitLogger();
void LoadExtensions();

#include "codegen/YRpp.gen.h"
#include "codegen/YrExtCore.gen.h"
#include "runtime/ecs/entt.h"
#include "yr/reflection/yr_reflection.h"
#include "yr/api/yr_entity.h"

struct MetaRegistration
{
    static void Register() {
        gEntt = new entt::registry();
        YrReflectionRegister();
        __Gen_Type_YRpp::Register();
        __Gen_Type_YrExtCore::Register();
    }
    static void Unregister()
    {
        __Gen_Type_YrExtCore::Unregister();
        __Gen_Type_YRpp::Unregister();
        YrReflectionUnregister();
        delete gEntt;
        gEntt = nullptr;
    }
};

#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/null_sink.h>

void InitLogger()
{
    const nlohmann::json& json = gYrExtConfig->rawData;
    spdlog::level::level_enum logLevel = json.value("log_level", spdlog::level::trace);

    spdlog::init_thread_pool(8192, 1);

    std::vector<spdlog::sink_ptr> sinks;
    bool useConsonle = json.value("debug_console", true);
    if (useConsonle)
    {
        AllocConsole();
        SetConsoleTitleA("Game Debug Console");
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(logLevel);
        console_sink->set_pattern("[%^%l%$] %v");
        sinks.push_back(console_sink);

        gConsole = std::make_shared<spdlog::async_logger>("console", console_sink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        gConsole->set_level(logLevel);
    }
    else
    {
        gConsole = spdlog::create<spdlog::sinks::null_sink_mt>("console");
    }

    namespace fs = std::filesystem;
    fs::path logDir = fs::path("debug") / "yrextcore";
    fs::path logPath = logDir / "yr_extcore.log";
    if (fs::exists(logPath))
    {
        fs::path oldPath = logDir / std::format("yr_extcore_{:%F-%H-%M-%S}.log", fs::last_write_time(logPath));
        std::ignore = std::rename(logPath.string().c_str(), oldPath.string().c_str());
    }

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath.string());
    file_sink->set_level(logLevel);
    sinks.push_back(file_sink);

    gLogger = std::make_shared<spdlog::async_logger>("main", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    gLogger->set_level(logLevel);
    gLogger->flush_on(spdlog::level::err);

    spdlog::register_logger(gLogger);
    spdlog::set_default_logger(gLogger);

    gLogger->info("YrExtCore config: {}",  json.dump(2));
}

void LoadExtensions()
{
    ExtensionManager::AddDirectory(gYrExtConfig->pluginsPath.c_str());

    for (auto ext : gYrExtConfig->extensions)
    {
        std::string extName = ext;
        if (!ExtensionManager::LoadExtension(extName.c_str())) {
            gLogger->error("could not load extension {}", extName);
        }
    }

    gLogger->info("All extension loaded");
}

#include <Syringe.h>
SYRINGE_HANDSHAKE(pInfo)
{
    if (pInfo)
    {
        std::string message = "Yr Extension Core Handshake";
        sprintf_s(pInfo->Message, pInfo->cchMessage, message.c_str());
        return S_OK;
    }

    return E_POINTER;
}

struct YrExtCore
{
    YrExtCore();
    ~YrExtCore();
};

void OnAppOpen();
void OnAppExit();

YrExtCore::YrExtCore()
{
    OnAppOpen();
}
YrExtCore::~YrExtCore()
{
    OnAppExit();
}

std::unique_ptr<YrExtCore> gYrExtCore;
DEFINE_HOOK(0x7CD810, OnEntryPoint, 0x9)
{
    gYrExtCore = std::make_unique<YrExtCore>();
    return 0;
}

#include <Windows.h>
#include <csignal>

// GLOBAL_INVOKE_ON_CTOR([]() {
//     wchar_t system_buffer[MAX_PATH];
//     GetModuleFileNameW(NULL, system_buffer, MAX_PATH);
//     system_buffer[MAX_PATH - 1]   = L'\0';
//     std::filesystem::path exePath = system_buffer;
//     if (exePath.filename() == "gamemd.exe")
//     {
//         gYrExtCore = std::make_unique<YrExtCore>();
//     }
// })

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) {
    OnAppExit();
    return FALSE;
}
static bool appInited = false;
static bool breakOnExit = false;
#include "yr/patch/patch.h"

void OnAppOpen()
{
    gYrExtConfig = new YrExtCoreConfig();
    if (gYrExtConfig->rawData.value("break_on_start", false))
    {
        assert(false);
    }
    breakOnExit = gYrExtConfig->rawData.value("break_on_exit", false);
    InitLogger();
    MetaRegistration::Register();
    yr_entity::Init();
    InitPatch();
    LoadExtensions();
    
    SetConsoleCtrlHandler(CtrlHandler, true);
    atexit(OnAppExit);
    appInited = true;
}

void OnAppExit()
{
    if (appInited) {
        appInited = false;
        gLogger->info("OnAppExit!");
        gLogger->flush();
        if (breakOnExit) {
            assert(false);
        }
        const auto& extensions = ExtensionManager::GetExtensions();
        while (extensions.size() > 0)
        {
            ExtensionManager::RemoveExtension(*extensions.rbegin());
        };
        UninitPatch();
        MetaRegistration::Unregister();
        delete gYrExtConfig;
        gYrExtConfig = nullptr;
        gLogger->flush();
    }
}

__declspec(dllexport) BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID v)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        OnAppExit();
        break;
    }

    return true;
}

#include "yr/event/windows_event.h"
#include "yr/event/general_event.h"
#include <Interfaces.h>
#include <Unsorted.h>

LONG oriWndProc = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_QUERYENDSESSION:
        case WM_ENDSESSION:
        case WM_CLOSE:
        case WM_DESTROY:
        case WM_QUIT:
            OnAppExit();
            break;
        case WM_SYSCOMMAND:
            switch( wParam & 0xFFF0 ) {
                case SC_CLOSE:
                OnAppExit();
            }
            break;
    }

    return CallWindowProcW((WNDPROC)oriWndProc, hWnd, uMsg, wParam, lParam);
}

// DEFINE_YR_HOOK_EVENT_LISTENER(YrMainWndProcEvent) {
//     WndProc(E->hWnd, E->uMsg, E->wParam, E->lParam);
// }
DEFINE_YR_HOOK_EVENT_LISTENER(YrTerminateEvent) {
    OnAppExit();
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrAfterSetCooperativeLevelEvent) {
    if (!oriWndProc) {
        oriWndProc = SetWindowLongPtr(Game::hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
    }
}
