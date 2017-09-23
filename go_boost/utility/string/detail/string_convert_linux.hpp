#ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_LINUX_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_LINUX_HPP_INCLUDED

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

#if defined(GO_BOOST_PLATFORM_LINUX) || defined(GO_BOOST_COMP_GCC_MINGW)

#include <go_boost/utility/string/detail/string_cast_fwd.hpp>

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
    const u16string u16s = convert_u2string_to_u16string(s);
    return convert_u16string_to_wstring(u16s);
}

inline std::wstring convert_u16string_to_wstring(const u16string& s)
{
    const u32string u32s = convert_u16string_to_u32string(s);
    return convert_u32string_to_wstring(u32s);
}

// to go::utility::u2string

inline u2string convert_wstring_to_u2string(const std::wstring& s)
{
    const u32string u32s = convert_wstring_to_u32string(s);
    return convert_u32string_to_u2string(u32s);
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
