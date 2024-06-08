#pragma once
#include "core/platform/platform.h"
#include <string>
#include <vector>

class FileHelper
{

	bool LoadFileToBytes(const char* path, std::vector<uint8>& bytes);

	bool LoadFileToString(const char* path, std::string& str);

	bool SaveBytesToFile(const char* path, const std::vector<uint8>& bytes);

	bool SaveStringToFile(const char* path, const std::string_view str);

};
