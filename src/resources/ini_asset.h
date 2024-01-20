#pragma once

#include "text_asset.h"

#include <string_view>

class CCFileClass;
class CCINIClass;

class IniAsset : public TextAsset
{
public:
    IniAsset(CCFileClass* yrFile);
    IniAsset(std::string_view path);

    virtual ~IniAsset();

    CCINIClass* GetYrIni() const;

private:
    CCINIClass* yrIni;
};
