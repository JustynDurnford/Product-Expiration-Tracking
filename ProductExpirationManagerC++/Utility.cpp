// ProductExpirationManagerC++
// Utility.cpp
// Created on Jun 26 2026 by Justyn Durnford
// Last modified on Jun 26 2026 by Justyn Durnford
// Implementation file for Utility.h

#include "Utility.h"

#include <cstdint>
using std::int32_t;
using std::uint8_t;

#include <filesystem>
using std::filesystem::exists;
using std::filesystem::remove;

#include <string>
using std::size_t;
using std::string;
using std::wstring;
using std::to_string;

#include <windows.h>
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")

wstring strToWstr(const string& str)
{
    if (str.empty())
        return L"";

    int32_t size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int32_t)str.size(), nullptr, 0);
    wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int32_t)str.size(), &wstr[0], size_needed);

    return wstr;
}

DownloadResultCode downloadToFile(const string& url, const string& filepath)
{
    if (url.empty())
        return DownloadResultCode::BAD_URL;
    if (filepath.empty())
        return DownloadResultCode::BAD_FILE;

    HRESULT result = URLDownloadToFile(NULL, strToWstr(url).c_str(), strToWstr(filepath).c_str(), 0, NULL);

    if (result == S_OK)
        return DownloadResultCode::SUCCESS;

    return DownloadResultCode::FAILURE;
}