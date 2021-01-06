#ifndef GO_STRING_CONVERT_CONVERT_WINDOWS_HPP_INCLUDED
#define GO_STRING_CONVERT_CONVERT_WINDOWS_HPP_INCLUDED

//
//  convert_windows.hpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#if defined(GO_PLATFORM_WINDOWS) && !defined(GO_COMP_GCC_MINGW)

#include <go/string/convert/convert_fwd.hpp>
#include <go/string/encoding/windows_1252.hpp>
#include <go/utility/deletable_facet.hpp>
#include <codecvt>
#include <windows.h>

namespace go
{
namespace string
{
namespace convert
{

// to std::string

inline std::string convert_wstring_to_string(const std::wstring& s)
{
    typedef go::utility::deletable_facet<std::codecvt<wchar_t, char, std::mbstate_t>> facet_type;
    std::wstring_convert<facet_type> converter;
    return converter.to_bytes(s);
}

inline std::string convert_u2string_to_string(const u2string& s)
{
    // Windows VC++ wide strings are UCS-2
    return convert_wstring_to_string(convert_u2string_to_wstring(s));
}

inline std::string convert_u8string_to_string(const u8string& s)
{
    std::string mbs;
    return go::string::encoding::reduce_to_windows_1252(s, mbs);
}

inline std::string convert_u16string_to_string(const std::u16string& s)
{
    return convert_u8string_to_string(convert_u16string_to_u8string(s));
}

inline std::string convert_u32string_to_string(const std::u32string& s)
{
    return convert_u8string_to_string(convert_u32string_to_u8string(s));
}

// to std::wstring

inline std::wstring convert_string_to_wstring(const std::string& s)
{
    typedef go::utility::deletable_facet<std::codecvt<wchar_t, char, mbstate_t>> facet_type;
    std::wstring_convert<facet_type> converter;
    return converter.from_bytes(s);
}

inline std::wstring convert_u2string_to_wstring(const u2string& s)
{
    // Windows VC++ wide strings are UCS-2
    return std::wstring(s.begin(), s.end());
}

inline std::wstring convert_u16string_to_wstring(const std::u16string& s)
{
    // Windows VC++ wide strings are UCS-2
    typedef go::utility::deletable_facet<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> facet_type;
    std::wstring_convert<facet_type, wchar_t> converter;
    return converter.from_bytes(reinterpret_cast<const char*> (&s[0]), reinterpret_cast<const char*>(&s[0] + s.size()));
}

inline std::wstring convert_u32string_to_wstring(const std::u32string& s)
{
    return convert_u16string_to_wstring(convert_u32string_to_u16string(s));
}

// to go::string::u2string

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

#endif  // #if defined(GO_PLATFORM_WINDOWS) && !defined(GO_COMP_GCC_MINGW)

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_STRING_CONVERT_CONVERT_WINDOWS_HPP_INCLUDED
