
#include "imgui_internal.h"
#include "scripting/javascript/js_env.h"
#include "yr/extcore_config.h"
#include "runtime/platform/path.h"
#include "runtime/platform/file_helper.h"
#include "runtime/logger/logger.h"
#include <efsw/efsw.hpp>

static std::shared_ptr<efsw::FileWatcher> fw;
using namespace std::chrono_literals;
 
class JsHotReloadListener : public efsw::FileWatchListener
{
    const char*  get_action_name(efsw::Action action) {
        switch (action)
        {
            case efsw::Action::Add:
                return "Add";
            case efsw::Action::Delete:
                return "Delete";
            case efsw::Action::Modified:
                return "Modified";
            case efsw::Action::Moved:
                return "Moved";
        }
        return "???";
    }
    virtual void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename = "")
    {
        std::string Extension = Paths::GetExtension(filename);
        bool        IsJs      = Extension == "js" || Extension == "mjs" || Extension == "cjs"/* || Extension == "json"*/;
        if (!IsJs)
            return;
        gLogger->info("js file changed: {}/{}, reason: {}", dir, filename, get_action_name(action));
        // waiting code editor to release file handle
        std::this_thread::sleep_for(100ms);
        switch (action)
        {
            case efsw::Action::Modified:
                OnFileModified(dir, filename);
                break;
        }
    }

    void OnFileModified(const std::string& dir, const std::string& filename)
    {
        std::string     path       = dir / filename;
        std::string     moduleName = Paths::Relative(path, gYrExtConfig->assetsPath / "JavaScript");
        std::string     source;
        if (FileHelper::LoadFileToString(path.c_str(), source))
        {
            std::lock_guard guard(gJsEnv->mutex);
            gJsEnv->ReloadModule(moduleName.c_str(), source.c_str());
        }
        else
        {
            gLogger->error("could not load file {}", path);
        }
    }

} JsHotReload;

void CreateJsHotReloadWatcher()
{
    if (gYrExtConfig->rawData.value("js_watch_files", false))
    {
        fw = std::make_shared<efsw::FileWatcher>();
        fw->addWatch(gYrExtConfig->assetsPath / "JavaScript", &JsHotReload, true);
        fw->watch();
    }
}
