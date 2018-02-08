#ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_LINUX_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_LINUX_HPP_INCLUDED

//
//  string_convert.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#if defined(GO_BOOST_PLATFORM_LINUX) || defined(GO_BOOST_COMP_GCC_MINGW)

#include <go_boost/utility/string/ascii.hpp>
#include <go_boost/utility/string/detail/string_cast_fwd.hpp>
#include <go_boost/utility/string/iso_8859_1.hpp>

namespace go_boost
{
namespace utility
{
namespace string
{
namespace detail
{

// to std::string

inline std::string convert_u8string_to_string(const u8string& s)
{
    if (s.empty())
    {
        return std::string();
    }
#if defined(GO_BOOST_COMP_CLANG)
    std::string mbs;
    reduce_to_iso_8859_1(s, mbs);
#else
    const u8string u8s = reduce_iso_8859_1_to_7_bit_ascii_copy(s, false);
    const std::string mbs(s.begin(), s.end());
#endif  // #if defined(GO_BOOST_COMP_CLANG)
    return mbs;
}

// to std::wstring

inline std::wstring convert_u2string_to_wstring(const u2string& s)
{
    const u8string u8s = convert_u2string_to_u8string(s);
    return convert_u8string_to_wstring(u8s);
}

inline std::wstring convert_u8string_to_wstring(const u8string& s)
{
    // Linux wide strings are UCS-4 (and UCS-4 is UTF-32)
    const std::wstring sws = convert_u32string_to_wstring(convert_u8string_to_u32string(s));
    return sws;
}

inline std::wstring convert_u16string_to_wstring(const u16string& s)
{
    const u8string u8s = convert_u16string_to_u8string(s);
    return convert_u8string_to_wstring(u8s);
}

inline std::wstring convert_u32string_to_wstring(const u32string& s)
{
    // Linux wide strings are UCS-4 (and UCS-4 is UTF-32)
    const std::wstring sws(s.begin(), s.end());
    return sws;
}

// to go::utility::u2string

inline u2string convert_wstring_to_u2string(const std::wstring& s)
{
    const u32string u32s = convert_wstring_to_u32string(s);
    return convert_u32string_to_u2string(u32s);
}

// to go::utility::u8string

inline u8string convert_string_to_u8string(const std::string& s)
{
    const std::string utf8s = boost::locale::conv::to_utf<char>(s, "ISO-8859-1");
    const u8string u8s(utf8s.begin(), utf8s.end());
    return u8s;
}

// to u16string

inline u16string convert_wstring_to_u16string(const std::wstring& s)
{
    // Non-Windows wide strings are UTF-32
    const u32string u32s = convert_wstring_to_u32string(s);
    return convert_u32string_to_u16string(u32s);
}

}
}
}
}

#endif  // #if defined(GO_BOOST_PLATFORM_LINUX) || defined(GO_BOOST_COMP_GCC_MINGW)

#endif  // #ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_LINUX_HPP_INCLUDED
