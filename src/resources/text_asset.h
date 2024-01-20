#pragma once

#include "asset_object.h"

class TextAsset : public AssetObject
{

public:
    TextAsset(CCFileClass* yrFile);
    TextAsset(std::string_view path);
	
    virtual ~TextAsset();

    virtual EAssetType GetAssetType();

    const void* GetBytes();

    long  GetDataSize();

    std::string GetText();

private:
    void* data { nullptr };
};
