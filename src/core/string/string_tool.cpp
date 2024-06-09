#include "core/string/string_tool.h"
#include <utf8.h>
#include <codecvt>

void buffer_to_string(std::string& result, const uint8* buffer, uint32 size)
{
    if (size >= 2 && !(size & 1) && buffer[0] == 0xff && buffer[1] == 0xfe)
    {
        // Unicode Intel byte order. Less 1 for the FFFE header, additional 1 for null terminator.
        result.reserve(size / 2);
        utf8::utf16to8(reinterpret_cast<const char16_t*>(buffer + 1), reinterpret_cast<const char16_t*>(buffer + size), std::back_inserter(result));
    }
    else if (size >= 2 && !(size & 1) && buffer[0] == 0xfe && buffer[1] == 0xff)
    {
        // Unicode non-Intel byte order. Less 1 for the FFFE header, additional 1 for null terminator.
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::consume_header>, char16_t> conv;
        result = conv.to_bytes(reinterpret_cast<const char16_t*>(buffer + 1), reinterpret_cast<const char16_t*>(buffer + size));
    }
    else
    {
        if (size >= 3 && buffer[0] == 0xef && buffer[1] == 0xbb && buffer[2] == 0xbf)
        {
            // Skip over UTF-8 BOM if there is one
            buffer += 3;
            size -= 3;
        }

        result.resize(size + 1);
        std::copy(buffer, buffer + size, result.data());
    }

    if (result.size() == 1)
    {
        // If it's only a zero terminator then make the result actually empty
        result.clear();
    }
    else
    {
        // Else ensure null terminator is present
        result.back() = '\0';
    }
}
