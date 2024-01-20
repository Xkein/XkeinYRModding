#pragma once

#include "core/object.h"

#include "CCFileClass.h"

#include <string_view>

enum EAssetType
{
    Text
};

class AssetObject : public Object
{
protected:
    AssetObject(CCFileClass* yrFile);
    AssetObject(std::string_view path);

public:
    virtual ~AssetObject();

    virtual const char* GetName();

    virtual EAssetType GetAssetType() = 0;

    CCFileClass* GetYrFile()
    {
        return yrFile;
    }


protected:
    CCFileClass* yrFile;
    bool         allocated { false };
};
