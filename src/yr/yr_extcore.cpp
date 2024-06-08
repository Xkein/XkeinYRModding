
#include "yr/extcore_config.h"
#include "yr/extension_loader.h"
#include "core/logger/logger.h"
#include "core/raii_invoker.h"
#include <filesystem>

void InitLogger();
void LoadExtensions();

#include "codegen/YRpp.gen.h"
#include "codegen/YrExtCore.gen.h"
struct MetaRegistration
{
    static void Register() {
        __Gen_Type_YRpp::Register();
        __Gen_Type_YrExtCore::Register();
    }
    static void Unregister()
    {
        __Gen_Type_YrExtCore::Unregister();
        __Gen_Type_YRpp::Unregister();
    }
};

GLOBAL_INVOKE_ON_CTOR_DTOR([]() {
    MetaRegistration::Register();
    gYrExtConfig = std::make_unique<YrExtCoreConfig>();
    InitLogger();
    LoadExtensions();
},
    []() {
    MetaRegistration::Register();
})

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
    bool useConsonle = json.value("console", true);
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
    fs::path logDir = fs::path("logs");
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

    spdlog::register_logger(gLogger);
    spdlog::set_default_logger(gLogger);

    gLogger->info("YrExtCore config: {}",  json.dump(2));
}

void LoadExtensions()
{
    ExtensionLoader::AddDirectory(gYrExtConfig->pluginsPath.wstring().c_str());

    for (auto ext : gYrExtConfig->extensions)
    {
        std::string extName = ext;
        ExtensionLoader::LoadExtension(extName.c_str());
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
