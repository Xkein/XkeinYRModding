#include "asset_object.h"

AssetObject::AssetObject(CCFileClass* yrFile) : Object(), yrFile(yrFile)
{

}

AssetObject::AssetObject(std::string_view path) : Object()
{
    yrFile = GameCreate<CCFileClass>(path.data());
    allocated = true;
}

AssetObject::~AssetObject()
{
    if (allocated)
    {
        GameDelete(yrFile);
    }
}

const char* AssetObject::GetName()
{
    return yrFile->GetFileName();
}
