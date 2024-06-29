#pragma once
#include "runtime/platform/platform.h"
#include <string>
#include <vector>

struct FileHelper
{
	static bool LoadFileToBytes(const char* path, std::vector<uint8>& bytes);

	static bool LoadFileToString(const char* path, std::string& str);

	static bool SaveBytesToFile(const char* path, const std::vector<uint8>& bytes);

	static bool SaveStringToFile(const char* path, const std::string_view str);

};
