
#include <filesystem>

void LoadExtension();
struct Loader
{
    Loader()
    {
        LoadExtension();
    }
} _;

#include <Windows.h>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;

void LoadExtension()
{
    auto dir = fs::absolute("YrExtensions");
    if (!fs::is_directory(dir))
    {
        return;
    }
    AddDllDirectory(dir.c_str());

    std::ifstream f("YrExtensions/config.json");
    json          data = json::parse(f);
    for (auto ext : data["extensions"])
    {
        if (!ext.is_string())
        {
            continue;
        }
        std::string extName = ext;
        LoadLibraryA(extName.c_str());
    }
}
