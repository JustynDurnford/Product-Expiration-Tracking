// ProductExpirationManagerC++
// Utility.h
// Created on Jun 26 2026 by Justyn Durnford
// Last modified on Jun 26 2026 by Justyn Durnford

#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

enum class DownloadResultCode : std::uint8_t
{
    SUCCESS = 0,
    BAD_URL = 1,
    BAD_FILE = 2,
    FAILURE = 255
};

// Converts the given std::string to a std::wstring.
std::wstring strToWstr(const std::string& str);

// Attemps to download a file from the given url to the given file path.
// Returns a DownloadResultCode
DownloadResultCode downloadToFile(const std::string& url, const std::string& filepath);