#ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_WINDOWS_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_WINDOWS_HPP_INCLUDED

//
//  string_convert.hpp
//
//  Copyright 2017 Göran Orsander
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

#include <go_boost/utility/string/detail/string_cast_fwd.hpp>
#include <windows.h>

namespace go_boost
{
namespace utility
{
namespace string
{
namespace detail
{

// to std::wstring

inline std::wstring convert_u2string_to_wstring(const u2string& s)
{
    // Windows VC++ wide strings are UCS-2
    return std::wstring(s.begin(), s.end());
}

inline std::wstring convert_u16string_to_wstring(const u16string& s)
{
    // Windows VC++ wide strings are UCS-2 (and UCS-2 is almost UTF-16)
    std::wstring sws(s.begin(), s.end());
    return sws;
}

// to go::utility::u2string

inline u2string convert_wstring_to_u2string(const std::wstring& s)
{
    // Windows VC++ wide strings are UCS-2
    return u2string(s.begin(), s.end());
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
}

#endif  // #if defined(GO_BOOST_PLATFORM_WINDOWS) && !defined(GO_BOOST_COMP_GCC_MINGW)

#endif  // #ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_WINDOWS_HPP_INCLUDED
