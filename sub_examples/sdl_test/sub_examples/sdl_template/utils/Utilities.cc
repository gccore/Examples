/**
 *
 *  @file Utilities.cc
 *  @author An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  https://github.com/an-tao/drogon
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Drogon
 *
 */

#include "Utilities.h"
#ifdef _WIN32
        #include <Windows.h>
        #include <algorithm>
#else  // _WIN32
        #include <locale>
        #include <codecvt>
#endif  // _WIN32

namespace trantor
{
namespace utils
{
std::string toUtf8(const std::wstring& wstr)
{
        if (wstr.empty())
                return {};

        std::string strTo;
#ifdef _WIN32
        int nSizeNeeded = ::WideCharToMultiByte(
                        CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
        strTo.resize(nSizeNeeded, 0);
        ::WideCharToMultiByte(CP_UTF8,
                              0,
                              &wstr[0],
                              (int)wstr.size(),
                              &strTo[0],
                              nSizeNeeded,
                              NULL,
                              NULL);
#else  // _WIN32
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf8conv;
        strTo = utf8conv.to_bytes(wstr);
#endif  // _WIN32
        return strTo;
}
std::wstring fromUtf8(const std::string& str)
{
        if (str.empty())
                return {};
        std::wstring wstrTo;
#ifdef _WIN32
        int nSizeNeeded =
                                        ::MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        wstrTo.resize(nSizeNeeded, 0);
        ::MultiByteToWideChar(
                                        CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], nSizeNeeded);
#else  // _WIN32
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf8conv;
        try {
                wstrTo = utf8conv.from_bytes(str);
        } catch (...) { // Should never fail if str valid UTF-8
        }
#endif  // _WIN32
        return wstrTo;
}

std::wstring toWidePath(const std::string& strUtf8Path)
{
        auto wstrPath{fromUtf8(strUtf8Path)};
#ifdef _WIN32
        // Not needed: normalize path (just replaces '/' with '\')
        std::replace(wstrPath.begin(), wstrPath.end(), L'/', L'\\');
#endif  // _WIN32
        return wstrPath;
}

std::string fromWidePath(const std::wstring& wstrPath)
{
#ifdef _WIN32
        auto srcPath {wstrPath};
        // Not needed: to portable path (just replaces '\' with '/')
        std::replace(srcPath.begin(), srcPath.end(), L'\\', L'/');
#else   // _WIN32
        auto& srcPath {wstrPath};
#endif  // _WIN32
        return toUtf8(srcPath);
}

}  // namespace utils
}  // namespace trantor
