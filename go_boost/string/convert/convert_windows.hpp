#ifndef GO_BOOST_STRING_CONVERT_CONVERT_WINDOWS_HPP_INCLUDED
#define GO_BOOST_STRING_CONVERT_CONVERT_WINDOWS_HPP_INCLUDED

//
//  convert_windows.hpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(GO_BOOST_PLATFORM_WINDOWS) && !defined(GO_BOOST_COMP_GCC_MINGW)

#include <go_boost/string/convert/convert_fwd.hpp>
#include <go_boost/string/encoding/ascii.hpp>
#include <go_boost/string/encoding/windows_1252.hpp>
#include <go_boost/utility/setup_global_locale.hpp>
#include <windows.h>

namespace go_boost
{
namespace string
{
namespace convert
{

// to std::string

inline std::string convert_u8string_to_string(const u8string& s)
{
    std::string mbs;
    return go_boost::string::encoding::reduce_to_windows_1252(s, mbs);
}

// to std::wstring

inline std::wstring convert_u2string_to_wstring(const u2string& s)
{
    // Windows VC++ wide strings are UCS-2
    return std::wstring(s.begin(), s.end());
}

inline std::wstring convert_u8string_to_wstring(const u8string& s)
{
    return convert_u16string_to_wstring(convert_u8string_to_u16string(s));
}

inline std::wstring convert_u16string_to_wstring(const u16string& s)
{
    // Windows VC++ wide strings are UCS-2 (and UCS-2 is almost UTF-16)
    std::wstring sws(s.begin(), s.end());
    return sws;
}

inline std::wstring convert_u32string_to_wstring(const u32string& s)
{
    return convert_u16string_to_wstring(convert_u32string_to_u16string(s));
}

// to go_boost::string::u2string

inline u2string convert_wstring_to_u2string(const std::wstring& s)
{
    // Windows VC++ wide strings are UCS-2
    return u2string(s.begin(), s.end());
}

// to go_boost::string::u8string

inline u8string convert_string_to_u8string(const std::string& s)
{
    try
    {
        static bool global_locale_is_initialized = false;
        if (!global_locale_is_initialized)
        {
            go_boost::utility::setup_global_locale();
            global_locale_is_initialized = true;
        }
        boost::locale::generator generator;
        generator.locale_cache_enabled(true);
        const std::locale locale = generator(boost::locale::util::get_system_locale());
        const std::string utf8s = boost::locale::conv::to_utf<char>(s, locale);
        const u8string u8s(utf8s.begin(), utf8s.end());
        return u8s;
    }
    catch (const std::exception&)
    {
        // Fallback
        const std::string s2 = go_boost::string::encoding::reduce_to_7_bit_ascii_copy(s);
        const u8string u8s(s2.begin(), s2.end());
        return u8s;
    }
}

// to u16string

inline u16string convert_wstring_to_u16string(const std::wstring& s)
{
    // Windows VC++ wide strings are UCS-2. For majority of the 65,000+
    // characters, UCS-2 LE and UTF-16 have identical code points; so they
    // are largely equivalent. This lets UTF-16 capable applications to
    // correctly interpret UCS-2 LE codes.
    const u16string u16s(s.begin(), s.end());
    return u16s;
}

}
}
}

#endif  // #if defined(GO_BOOST_PLATFORM_WINDOWS) && !defined(GO_BOOST_COMP_GCC_MINGW)

#endif  // #ifndef GO_BOOST_STRING_CONVERT_CONVERT_WINDOWS_HPP_INCLUDED
