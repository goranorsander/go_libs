#ifndef GO_UTILITY_STRING_DETAIL_STRING_CONVERT_WINDOWS_HPP_INCLUDED
#define GO_UTILITY_STRING_DETAIL_STRING_CONVERT_WINDOWS_HPP_INCLUDED

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

#if defined(GO_PLATFORM_WINDOWS) || defined(GO_COMP_GCC_MINGW)

#include <go/utility/string/detail/deletable_facet.hpp>
#include <go/utility/string/detail/string_cast_fwd.hpp>
#include <codecvt>
#include <windows.h>

namespace go
{
namespace utility
{
namespace string
{
namespace detail
{

// to std::string

inline std::string convert_u2string_to_string(const u2string& s)
{
    // Windows VC++ wide strings are UCS-2
    return convert_wstring_to_string(convert_u2string_to_wstring(s));
}

// to std::wstring

inline std::wstring convert_u2string_to_wstring(const u2string& s)
{
    // Windows VC++ wide strings are UCS-2
    return std::wstring(s.begin(), s.end());
}

inline std::wstring convert_u16string_to_wstring(const std::u16string& s)
{
    // Windows VC++ wide strings are UCS-2
    std::wstring_convert<deletable_facet<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>>, wchar_t> converter;
    return converter.from_bytes(reinterpret_cast<const char*> (&s[0]), reinterpret_cast<const char*>(&s[0] + s.size()));
}

inline std::wstring convert_u32string_to_wstring(const std::u32string& s)
{
    return convert_u16string_to_wstring(convert_u32string_to_u16string(s));
}

// to go::utility::u2string

inline u2string convert_wstring_to_u2string(const std::wstring& s)
{
    // Windows VC++ wide strings are UCS-2
    return u2string(s.begin(), s.end());
}

// to std::u16string

inline std::u16string convert_wstring_to_u16string(const std::wstring& s)
{
    // Windows VC++ wide strings are UCS-2. For majority of the 65,000+
    // characters, UCS-2 LE and UTF-16 have identical code points; so they
    // are largely equivalent. This lets UTF-16 capable applications to
    // correctly interpret UCS-2 LE codes.
    const std::u16string u16s(s.begin(), s.end());
    return u16s;
}

// to std::u32string

inline std::u32string convert_wstring_to_u32string(const std::wstring& s)
{
    return convert_u16string_to_u32string(convert_wstring_to_u16string(s));
}

}
}
}
}

#endif  // #if defined(GO_PLATFORM_WINDOWS) || defined(GO_COMP_GCC_MINGW)

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_STRING_DETAIL_STRING_CONVERT_WINDOWS_HPP_INCLUDED
