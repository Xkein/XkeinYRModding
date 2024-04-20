#include "asset.h"

#include "text_asset.h"
#include "ini_asset.h"

#include <map>
#include <functional>



template<class T>
std::shared_ptr<AssetObject> LoadAsset(std::string_view path)
{
    std::shared_ptr<T> ptr = Asset::Load<T>(path);
    return std::static_pointer_cast<AssetObject>(std::move(ptr));
}

using LoadAssetFuncType = std::function<std::shared_ptr<AssetObject>(std::string_view)>;

std::map<std::string_view, LoadAssetFuncType> gLoadAssetFunc {
    {"ini", LoadAsset<IniAsset>},
    {"txt", LoadAsset<TextAsset>},
};

std::shared_ptr<AssetObject> Asset::Load(std::string_view path)
{
    std::string_view ext(path.begin() + path.find_last_of('.'), path.end());

    auto iter = gLoadAssetFunc.find(ext);
    if (iter != gLoadAssetFunc.end())
    {
        const LoadAssetFuncType& load = iter->second;
        return load(path);
    }

    return Load<TextAsset>(path);
}

template<>
static std::shared_ptr<TextAsset> Asset::Load_Impl(std::string_view path)
{
    return std::make_shared<TextAsset>(path);
}

template<>
static std::shared_ptr<IniAsset> Asset::Load_Impl(std::string_view path)
{
    return std::make_shared<IniAsset>(path);
}
