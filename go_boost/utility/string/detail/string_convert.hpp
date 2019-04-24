#ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_HPP_INCLUDED

//
//  string_convert.hpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/bind.hpp>
#include <boost/locale.hpp>

#if defined(GO_BOOST_PLATFORM_LINUX) || defined(GO_BOOST_COMP_GCC_MINGW)
#include <go_boost/utility/string/detail/string_convert_linux.hpp>
#endif  // #if defined(GO_BOOST_PLATFORM_LINUX)
#if defined(GO_BOOST_PLATFORM_WINDOWS) && !defined(GO_BOOST_COMP_GCC_MINGW)
#include <go_boost/utility/string/detail/string_convert_windows.hpp>
#endif  // #if defined(GO_BOOST_PLATFORM_WINDOWS)

#include <go_boost/utility/string/algorithm.hpp>
#include <go_boost/utility/string/ascii.hpp>
#include <go_boost/utility/string/detail/setup_global_locale.hpp>
#include <go_boost/utility/string/detail/string_cast_fwd.hpp>
#include <go_boost/utility/string/iso_8859_1.hpp>
#include <go_boost/utility/string/ucs2.hpp>

namespace go_boost
{
namespace utility
{
namespace string
{
namespace detail
{

// conversions

inline char to_char(const wchar_t c)
{
    return static_cast<char>(c & 0xFF);
}

inline wchar_t to_wchar_t(const char c)
{
    return static_cast<wchar_t>(c) & 0xFF;
}

// to std::string

inline std::string convert_wstring_to_string(const std::wstring& s)
{
    try
    {
        static bool global_locale_is_initialized = false;
        if (!global_locale_is_initialized)
        {
            setup_global_locale();
            global_locale_is_initialized = true;
        }
        boost::locale::generator generator;
        generator.locale_cache_enabled(true);
        const std::locale locale = generator(boost::locale::util::get_system_locale());
        const std::string mbs = boost::locale::conv::from_utf(s, locale);
#if defined(GO_BOOST_COMP_CLANG)
        const u8string u8s(mbs.begin(), mbs.end());
        std::string mbs_reduced;
        reduce_to_iso_8859_1(u8s, mbs_reduced);
        return mbs_reduced;
#else
        return mbs;
#endif  // #if defined(GO_BOOST_COMP_CLANG)
    }
    catch (const std::exception&)
    {
        // Fallback
        const std::wstring s2 = reduce_to_7_bit_ascii_copy(s);
        std::string mbs;
        std::transform(s2.begin(), s2.end(), std::back_inserter(mbs), boost::bind(to_char, _1));
        return mbs;
    }
}

inline std::string convert_u2string_to_string(const u2string& s)
{
    return convert_u8string_to_string(convert_u2string_to_u8string(s));
}

inline std::string convert_u16string_to_string(const u16string& s)
{
    return convert_u8string_to_string(convert_u16string_to_u8string(s));
}

inline std::string convert_u32string_to_string(const u32string& s)
{
    return convert_u8string_to_string(convert_u32string_to_u8string(s));
}

// to std::wstring

inline std::wstring convert_string_to_wstring(const std::string& s)
{
    if(s.empty())
    {
        return std::wstring();
    }
    std::wstring sws;
    std::transform(s.begin(), s.end(), std::back_inserter(sws), boost::bind(to_wchar_t, _1));
    return sws;
}

// to go_boost::utility::u2string

inline u2string convert_string_to_u2string(const std::string& s)
{
    return convert_u8string_to_u2string(convert_string_to_u8string(s));
}

inline u2string convert_u8string_to_u2string(const u8string& s)
{
    const uft8_string_type u8s = s.string();
    u2string u2s;
    uft8_string_type::const_iterator it = u8s.begin();
    const uft8_string_type::const_iterator endit = u8s.end();
    while (it != endit)
    {
        char2_t ucs2ch = 0;
        if (try_convert_to_ucs2(ucs2ch, it->second))
        {
            u2s += ucs2ch;
        }
        ++it;
    }
    return u2s;
}

inline u2string convert_u16string_to_u2string(const u16string& s)
{
    return convert_u8string_to_u2string(convert_u16string_to_u8string(s));
}

inline u2string convert_u32string_to_u2string(const u32string& s)
{
    return convert_u8string_to_u2string(convert_u32string_to_u8string(s));
}

// to go_boost::utility::u8string

inline u8string convert_wstring_to_u8string(const std::wstring& s)
{
    const std::string utf8s = boost::locale::conv::utf_to_utf<char>(s);
    const u8string u8s(utf8s.begin(), utf8s.end());
    return u8s;
}

inline u8string convert_u2string_to_u8string(const u2string& s)
{
    const std::string utf8s = boost::locale::conv::utf_to_utf<char>(s);
    const u8string u8s(utf8s.begin(), utf8s.end());
    return u8s;
}

inline u8string convert_u16string_to_u8string(const u16string& s)
{
    const std::wstring utf16s(s.begin(), s.end());
    const std::string utf8s = boost::locale::conv::utf_to_utf<char>(utf16s);
    const u8string u8s(utf8s.begin(), utf8s.end());
    return u8s;
}

inline u8string convert_u32string_to_u8string(const u32string& s)
{
    const std::basic_string<boost::int32_t> xs(s.begin(), s.end());
    const std::string utf8s = boost::locale::conv::utf_to_utf<char, boost::int32_t>(xs); // boost::locale::conv::from_utf<boost::int32_t>(xs, "UTF-8");
    const u8string u8s(utf8s.begin(), utf8s.end());
    return u8s;
}

// to u16string

inline u16string convert_string_to_u16string(const std::string& s)
{
    return convert_u8string_to_u16string(convert_string_to_u8string(s));
}

inline u16string convert_u2string_to_u16string(const u2string& s)
{
    return convert_u8string_to_u16string(convert_u2string_to_u8string(s));
}

inline u16string convert_u8string_to_u16string(const u8string& s)
{
    const std::string utf8s(s.begin(), s.end());
    const std::wstring utf16s = boost::locale::conv::to_utf<wchar_t>(utf8s, "UTF-8");
    const u16string u16s(utf16s.begin(), utf16s.end());
    return u16s;
}

inline u16string convert_u32string_to_u16string(const u32string& s)
{
    return convert_u8string_to_u16string(convert_u32string_to_u8string(s));
}

// to u32string

inline u32string convert_string_to_u32string(const std::string& s)
{
    return convert_u8string_to_u32string(convert_string_to_u8string(s));
}

inline u32string convert_wstring_to_u32string(const std::wstring& s)
{
    return convert_u8string_to_u32string(convert_wstring_to_u8string(s));
}

inline u32string convert_u2string_to_u32string(const u2string& s)
{
    return convert_u8string_to_u32string(convert_u2string_to_u8string(s));
}

inline u32string convert_u8string_to_u32string(const u8string& s)
{
    const std::string uft8s(s.begin(), s.end());
    const std::basic_string<boost::int32_t> xs = boost::locale::conv::utf_to_utf<boost::int32_t, char>(uft8s);
    const u32string u32s(xs.begin(), xs.end());
    return u32s;
}

inline u32string convert_u16string_to_u32string(const u16string& s)
{
    return convert_u8string_to_u32string(convert_u16string_to_u8string(s));
}

inline bool is_little_endian_system()
{
    static const char16_t endian_test = 0x0102;
    return (reinterpret_cast<const char*>(&endian_test))[0] == 0x02;
}

}
}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CONVERT_HPP_INCLUDED
