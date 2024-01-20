#include "ini_asset.h"

#include <CCINIClass.h>

IniAsset::IniAsset(CCFileClass* yrFile) : TextAsset(yrFile)
{
    yrIni = nullptr;
}

IniAsset::IniAsset(std::string_view path) : TextAsset(path)
{
    yrIni = nullptr;
}

IniAsset::~IniAsset()
{
    if (yrIni)
    {
        GameDelete(yrIni);
    }
}

CCINIClass* IniAsset::GetYrIni() const
{
    if (yrIni)
        return yrIni;

    const_cast<IniAsset*>(this)->yrIni = GameCreate<CCINIClass>();

    yrIni->ReadCCFile(yrFile);

    return yrIni;
}
