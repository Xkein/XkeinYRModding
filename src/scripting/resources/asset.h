#pragma once

#include "asset_object.h"

#include <memory>
#include <string_view>

class TextAsset;
class IniAsset;


class Asset
{
public:
    // Decide asset type by file extension. Return TextAsset if fails.
    static std::shared_ptr<AssetObject> Load(std::string_view path);

    template<class T>
    static std::shared_ptr<T> Load(std::string_view path)
    {
        return Load_Impl<T>(path);
    }

private:
    template<class T>
    static std::shared_ptr<T> Load_Impl(std::string_view path);
};

