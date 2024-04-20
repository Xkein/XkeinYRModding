#include "text_asset.h"

TextAsset::TextAsset(CCFileClass* yrFile) : AssetObject(yrFile)
{

}

TextAsset::TextAsset(std::string_view path) : AssetObject(path)
{

}

TextAsset::~TextAsset()
{
    if (data)
    {
        delete data;
    }
}

EAssetType TextAsset::GetAssetType()
{
    return EAssetType::Text;
}

const void* TextAsset::GetBytes()
{
    if (data)
        return data;

    long dataSize = GetDataSize();
    data          = new BYTE[dataSize];

    yrFile->Seek(0, FileSeekMode::Set);
    yrFile->ReadBytes(data, dataSize);

    return data;
}

long TextAsset::GetDataSize()
{
    return yrFile->GetFileSize();
}

std::string TextAsset::GetText()
{
    const void* data = GetBytes();
    std::string tmp(static_cast<const char*>(data), GetDataSize());
    return tmp;
}
