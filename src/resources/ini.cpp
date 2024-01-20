#include "ini.h"
#include "ini_asset.h"

#include <CCINIClass.h>
#include <mutex>

char gIniReadBuffer[4096 * 4];
std::mutex gReadMutex;

Ini::Ini()
{
}

Ini::Ini(const IniAsset& iniAsset)
{
    Read(iniAsset);
}

Ini& Ini::Read(const IniAsset& iniAsset)
{
    std::lock_guard guard(gReadMutex);

    CCINIClass* yrIni = iniAsset.GetYrIni();

    for (auto yrSection = yrIni->Sections.First(); yrSection; yrSection = yrSection->Next())
    {
        auto sectionName = yrSection->Name;
        if (sectionName)
        {
            IniSection& section = sections[sectionName];

            int keyCount = yrIni->GetKeyCount(sectionName);
            for (int idx = 0; idx < keyCount; idx++)
            {
                auto key = yrIni->GetKeyName(sectionName, idx);
                auto value = yrIni->ReadString(sectionName, key, "", gIniReadBuffer);
                section.keyValues[key] = value;
            }
        }
    }

    return *this;
}

IniSection& Ini::GetSection(std::string_view section)
{
    return sections[section.data()];
}

void Ini::Clear()
{
    sections.clear();
}

std::string_view IniSection::operator[](std::string_view key)
{
    return keyValues[key.data()];
}
