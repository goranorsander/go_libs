#ifndef GO_UTILITY_STRING_DETAIL_STRING_CONVERT_LINUX_HPP_INCLUDED
#define GO_UTILITY_STRING_DETAIL_STRING_CONVERT_LINUX_HPP_INCLUDED

//
//  string_convert.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/utility/string/detail/deletable_facet.hpp>
#include <go/utility/string/detail/string_cast_fwd.hpp>
#include <clocale>
#include <codecvt>
#include <cwchar>
#include <vector>

namespace go
{
namespace utility
{
namespace string
{
namespace detail
{

// to std::string

inline std::string convert_wstring_to_string(const std::wstring& s)
{
    std::mbstate_t state = std::mbstate_t();
    const wchar_t* wstr = s.c_str();
    const int len = 1 + std::wcsrtombs(nullptr, &wstr, 0, &state);
    std::vector<char> mbstr(len);
    std::wcsrtombs(&mbstr[0], &wstr, mbstr.size(), &state);
    return std::string(&mbstr[0]);
}

inline std::string convert_u2string_to_string(const u2string& s)
{
    std::wstring_convert<std::codecvt_utf8<char2_t>, char2_t> convert;
    return convert.to_bytes(s);
}

// to std::wstring

inline std::wstring convert_u2string_to_wstring(const u2string& s)
{
    return convert_u16string_to_wstring(convert_u2string_to_u16string(s));
}

inline std::wstring convert_string_to_wstring(const std::string& s)
{
    std::mbstate_t state = std::mbstate_t();
    const char* mbstr = s.c_str();
    const int len = 1 + std::mbsrtowcs(NULL, &mbstr, 0, &state);
    std::vector<wchar_t> wstr(len);
    std::mbsrtowcs(&wstr[0], &mbstr, wstr.size(), &state);
    return std::wstring(&wstr[0]);
}

inline std::wstring convert_u16string_to_wstring(const std::u16string& s)
{
    return convert_u32string_to_wstring(convert_u16string_to_u32string(s));
}

inline std::wstring convert_u32string_to_wstring(const std::u32string& s)
{
    // Non-Windows wide strings are UTF-32
    const std::wstring sws(s.begin(), s.end());
    return sws;
}

// to std::u16string

inline std::u16string convert_wstring_to_u16string(const std::wstring& s)
{
    // Non-Windows wide strings are UTF-32
    return convert_u32string_to_u16string(convert_wstring_to_u32string(s));
}

// to std::u32string

inline std::u32string convert_wstring_to_u32string(const std::wstring& s)
{
    // Non-Windows wide strings are UTF-32
    const std::u32string u32s(s.begin(), s.end());
    return u32s;
}

}
}
}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_STRING_DETAIL_STRING_CONVERT_LINUX_HPP_INCLUDED
