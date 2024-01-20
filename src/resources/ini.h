#pragma once

#include "resources/parser.h"

#include <string>
#include <map>

class IniAsset;

class IniSection;

class Ini final
{
public:
    Ini();
    Ini(const IniAsset& iniAsset);

    Ini& Read(const IniAsset& iniAsset);

    IniSection& GetSection(std::string_view section);

    void Clear();

protected:
    std::map<std::string, IniSection> sections;
};

class IniSection
{
    friend class Ini;

public:
    template<class T>
    bool Read(std::string_view key, T& buffer)
    {
        return GetDefaultParser<T>()->Parse(keyValues[key.data()], buffer);
    }


    std::string_view operator[](std::string_view key);

private:
    std::map<std::string, std::string> keyValues;
};

