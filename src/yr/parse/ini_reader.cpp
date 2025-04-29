#include "yr/parse/ini_reader.h"

YREXTCORE_API char IniReader::_readBuffer[2048];

IniReader::IniReader(CCINIClass* pIni) : IniFile(pIni), _selfAlloc(false) {}

IniReader::IniReader(const std::string& filename) {
    IniFile = GameCreate<CCINIClass>();
    _selfAlloc = true;
    CCFileClass file { filename.c_str() };
    if (file.Exists()) {
        IniFile->ReadCCFile(&file);
    }
}

IniReader::~IniReader() {
    if (_selfAlloc) {
        GameDelete(IniFile);
        IniFile = nullptr;
    }
}
