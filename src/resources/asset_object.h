#pragma once

#include "core/object.h"

#include "CCFileClass.h"

#include <string_view>

ENUM()
enum EAssetType
{
    Text
};

CLASS()
class AssetObject : public Object
{
    GENERATED_BODY(AssetObject)
protected:
    AssetObject(CCFileClass* yrFile);
    AssetObject(std::string_view path);

public:
    virtual ~AssetObject();
    FUNCTION()
    virtual const char* GetName();
    FUNCTION()
    virtual EAssetType GetAssetType() = 0;

    CCFileClass* GetYrFile()
    {
        return yrFile;
    }


protected:
    CCFileClass* yrFile;
    bool         allocated { false };
};
