#include "yr/parse/ini_reader.h"

YREXTCORE_API char IniReader::_readBuffer[2048];
YREXTCORE_API std::map<std::size_t, std::string> detail::ini_string_pool::string_dict;
