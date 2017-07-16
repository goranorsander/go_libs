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

#if defined(GO_PLATFORM_LINUX) && !defined(GO_COMP_GCC_MINGW)

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
    if(s.empty())
    {
        return std::string();
    }
    std::string mbs;
    std::transform(s.begin(), s.end(), std::back_inserter(mbs), [](const std::wstring::value_type c) -> std::string::value_type { return static_cast<std::string::value_type>(c & 0xFF); });
    return mbs;
}

inline std::string convert_u2string_to_string(const u2string& s)
{
    if(s.empty())
    {
        return std::string();
    }
    std::string mbs;
    std::transform(s.begin(), s.end(), std::back_inserter(mbs), [](const std::wstring::value_type c) -> std::string::value_type { return static_cast<std::string::value_type>(c & 0xFF); });
    return mbs;
}

inline std::string convert_u8string_to_string(const u8string& s)
{
    const std::u32string u32s = convert_u8string_to_u32string(s);
    return convert_u32string_to_string(u32s);
}

inline std::string convert_u16string_to_string(const std::u16string& s)
{
    if(s.empty())
    {
        return std::string();
    }
    std::string mbs;
    std::transform(s.begin(), s.end(), std::back_inserter(mbs), [](const std::wstring::value_type c) -> std::string::value_type { return static_cast<std::string::value_type>(c & 0xFF); });
    return mbs;
}

inline std::string convert_u32string_to_string(const std::u32string& s)
{
    if(s.empty())
    {
        return std::string();
    }
    std::string mbs;
    std::transform(s.begin(), s.end(), std::back_inserter(mbs), [](const std::wstring::value_type c) -> std::string::value_type { return static_cast<std::string::value_type>(c & 0xFF); });
    return mbs;
}

// to std::wstring

inline std::wstring convert_string_to_wstring(const std::string& s)
{
    if(s.empty())
    {
        return std::wstring();
    }
    std::wstring sws;
    std::transform(s.begin(), s.end(), std::back_inserter(sws), [](const std::string::value_type c) -> std::wstring::value_type { return static_cast<std::wstring::value_type>(c) & 0xFF; });
    return sws;
}

inline std::wstring convert_u2string_to_wstring(const u2string& s)
{
    const std::u16string u16s = convert_u2string_to_u16string(s);
    return convert_u16string_to_wstring(u16s);
}

inline std::wstring convert_u16string_to_wstring(const std::u16string& s)
{
    const std::u32string u32s = convert_u16string_to_u32string(s);
    return convert_u32string_to_wstring(u32s);
}

inline std::wstring convert_u32string_to_wstring(const std::u32string& s)
{
    // Non-Windows wide strings are UTF-32
    const std::wstring sws(s.begin(), s.end());
    return sws;
}

// to go::utility::u2string

inline u2string convert_wstring_to_u2string(const std::wstring& s)
{
    const std::u32string u32s = convert_wstring_to_u32string(s);
    return convert_u32string_to_u2string(u32s);
}

// to std::u16string

inline std::u16string convert_wstring_to_u16string(const std::wstring& s)
{
    // Non-Windows wide strings are UTF-32
    const std::u32string u32s = convert_wstring_to_u32string(s);
    return convert_u32string_to_u16string(u32s);
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

#endif  // #if defined(GO_PLATFORM_LINUX) && !defined(GO_COMP_GCC_MINGW)

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_STRING_DETAIL_STRING_CONVERT_LINUX_HPP_INCLUDED
