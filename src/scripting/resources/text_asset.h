#pragma once

#include "asset_object.h"

CLASS()
class TextAsset : public AssetObject
{

public:
    TextAsset(CCFileClass* yrFile);
    FUNCTION()
    TextAsset(std::string_view path);
	
    virtual ~TextAsset();

    virtual EAssetType GetAssetType();

    const void* GetBytes();

    long GetDataSize();

    FUNCTION()
    std::string GetText();

private:
    void* data { nullptr };
};
