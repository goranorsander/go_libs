#ifndef GO_STRING_CONVERT_CONVERT_HPP_INCLUDED
#define GO_STRING_CONVERT_CONVERT_HPP_INCLUDED

//
//  convert.hpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11_CODECVT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <codecvt>
#include <locale>

#if defined(GO_PLATFORM_LINUX) || defined(GO_COMP_GCC_MINGW)
#include <go/string/convert/convert_linux.hpp>
#endif  // #if defined(GO_PLATFORM_LINUX)
#if defined(GO_PLATFORM_WINDOWS) && !defined(GO_COMP_GCC_MINGW)
#include <go/string/convert/convert_windows.hpp>
#endif  // #if defined(GO_PLATFORM_WINDOWS)

#include <go/utility/deletable_facet.hpp>
#include <go/utility/is_little_endian_system.hpp>

//
// IMPLEMENTATION NOTE #1
//
// ISSUE WITH VISUAL STUDIO 2015 AND 2017
// error LNK2001: unresolved external symbol "__declspec(dllimport) public: static class std::locale::id std::codecvt<char16_t,char,struct _Mbstatet>::id"
// See https://stackoverflow.com/questions/32055357/visual-studio-c-2015-stdcodecvt-with-char16-t-or-char32-t
//

namespace go
{
namespace string
{
namespace convert
{

// to std::string

// to std::wstring

inline std::wstring convert_u8string_to_wstring(const u8string& s)
{
    return convert_u16string_to_wstring(convert_u8string_to_u16string(s));
}

// to go::string::u2string

inline u2string convert_string_to_u2string(const std::string& s)
{
    return convert_u8string_to_u2string(convert_string_to_u8string(s));
}

inline u2string convert_u8string_to_u2string(const u8string& s)
{
    static const bool little_endian = go::utility::is_little_endian_system();
    const std::string u8s(s.begin(), s.end());
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    if(little_endian)
    {
        using facet_type = go::utility::deletable_facet<std::codecvt_utf8<char2_t, 0x10ffffU, std::little_endian>>;
        std::wstring_convert<facet_type, char2_t> converter;
        auto xs = converter.from_bytes(u8s);
        return u2string(xs.begin(), xs.end());
    }
    else
    {
        using facet_type = go::utility::deletable_facet<std::codecvt_utf8<char2_t>>;
        std::wstring_convert<facet_type, char2_t> converter;
        auto xs = converter.from_bytes(u8s);
        return u2string(xs.begin(), xs.end());
    }
#else
    if (little_endian)
    {
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
        typedef go::utility::deletable_facet<std::codecvt_utf8<char16_t, 0x10ffffU, std::little_endian>> facet_type;
#else
        using facet_type = go::utility::deletable_facet<std::codecvt_utf8<char16_t, 0x10ffffU, std::little_endian>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
        std::wstring_convert<facet_type, char16_t> converter;
        auto xs = converter.from_bytes(u8s);
        return u2string(xs.begin(), xs.end());
    }
    else
    {
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
        typedef go::utility::deletable_facet<std::codecvt_utf8<char16_t>> facet_type;
#else
        using facet_type = go::utility::deletable_facet<std::codecvt_utf8<char16_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
        std::wstring_convert<facet_type, char16_t> converter;
        auto xs = converter.from_bytes(u8s);
        return u2string(xs.begin(), xs.end());
    }
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
}

inline u2string convert_u16string_to_u2string(const std::u16string& s)
{
    std::string bytes;
    bytes.reserve(s.size()*2);
#if !defined(GO_NO_CXX11_RANGE_FOR_LOOP)
    for (const char2_t c : s)
    {
        bytes.push_back(static_cast<char>(c/256));
        bytes.push_back(static_cast<char>(c%256));
    }
#else
    for (std::u16string::const_iterator i = s.begin(); i != s.end(); ++i)
    {
        const char2_t c = *i;
        bytes.push_back(static_cast<char>(c/256));
        bytes.push_back(static_cast<char>(c%256));
    }
#endif  // #if !defined(GO_NO_CXX11_RANGE_FOR_LOOP)
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    using facet_type = go::utility::deletable_facet<std::codecvt_utf16<int16_t>>;
    std::wstring_convert<facet_type, int16_t> converter;
    const auto u16s = converter.from_bytes(bytes);
    return u2string(u16s.begin(), u16s.end());
#else
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf16<char16_t>> facet_type;
#else
    using facet_type = go::utility::deletable_facet<std::codecvt_utf16<char16_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_type, char16_t> converter;
    const std::u16string u16s = converter.from_bytes(bytes);
    return u2string(u16s.begin(), u16s.end());
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
}

inline u2string convert_u32string_to_u2string(const std::u32string& s)
{
    return convert_u16string_to_u2string(convert_u32string_to_u16string(s));
}

// to go::string::u8string

inline u8string convert_string_to_u8string(const std::string& s)
{
    return convert_wstring_to_u8string(convert_string_to_wstring(s));
}

inline u8string convert_wstring_to_u8string(const std::wstring& s)
{
    const std::u16string u16s = convert_wstring_to_u16string(s);
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8_utf16<int16_t>>;
    std::wstring_convert<facet_type, int16_t> converter;
    auto p = reinterpret_cast<const int16_t*>(u16s.data());
    const std::string u8s = converter.to_bytes(p, p + u16s.size());
#else
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t>> facet_type;
#else
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_type, char16_t> converter;
    const std::string u8s = converter.to_bytes(u16s);
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
    return u8string(u8s.begin(), u8s.end());
}

inline u8string convert_u2string_to_u8string(const u2string& s)
{
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8<char2_t>>;
    std::wstring_convert<facet_type, char2_t> converter;
    const std::string u8s = converter.to_bytes(s);
    return u8string(u8s.begin(), u8s.end());
#else
    const std::u16string u16s(s.begin(), s.end());
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf8<char16_t>> facet_type;
#else
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8<char16_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_type, char16_t> converter;
    const auto xs = converter.to_bytes(u16s);
    return u8string(xs.begin(), xs.end());
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
}

inline u8string convert_u16string_to_u8string(const std::u16string& s)
{
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8_utf16<int16_t>>;
    std::wstring_convert<facet_type, int16_t> converter;
    auto p = reinterpret_cast<const int16_t*>(s.data());
    const std::string u8s = converter.to_bytes(p, p + s.size());
#else
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t>> facet_type;
#else
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_type, char16_t> converter;
    const std::string u8s = converter.to_bytes(s);
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
    return u8string(u8s.begin(), u8s.end());
}

inline u8string convert_u32string_to_u8string(const std::u32string& s)
{
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8<int32_t>>;
    std::wstring_convert<facet_type, int32_t> converter;
    auto p = reinterpret_cast<const int32_t*>(s.data());
    const std::string u8s = converter.to_bytes(p, p + s.size());
#else
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf8<char32_t>> facet_type;
#else
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8<char32_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_type, char32_t> converter;
    const std::string u8s = converter.to_bytes(s);
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
    return u8string(u8s.begin(), u8s.end());
}

// to std::u16string

inline std::u16string convert_string_to_u16string(const std::string& s)
{
    return convert_u8string_to_u16string(convert_string_to_u8string(s));
}

inline std::u16string convert_u2string_to_u16string(const u2string& s)
{
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::string bytes;
    using facet_type = go::utility::deletable_facet<std::codecvt_utf16<int16_t>>;
    std::wstring_convert<facet_type, int16_t> converter;
    auto p = reinterpret_cast<const int16_t*>(s.data());
    bytes = converter.to_bytes(p, p + s.size());
    std::u16string result;
    result.reserve(bytes.size() / 2);
    for (size_t i = 0; i < bytes.size(); i += 2)
    {
        result.push_back(static_cast<char16_t>(static_cast<unsigned char>(bytes[i]) * 256 + static_cast<unsigned char>(bytes[i + 1])));
    }
    return result;
#else
    const std::u16string u16s(s.begin(), s.end());
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf8<char16_t>> facet_1_type;
#else
    using facet_1_type = go::utility::deletable_facet<std::codecvt_utf8<char16_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_1_type, char16_t> converter1;
    const auto xs = converter1.to_bytes(u16s);
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t>> facet_2_type;
#else
    using facet_2_type = go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_2_type, char16_t> converter2;
    return converter2.from_bytes(xs);
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
}

inline std::u16string convert_u8string_to_u16string(const u8string& s)
{
    static const bool little_endian = go::utility::is_little_endian_system();
    const std::string u8s(s.begin(), s.end());
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    if(little_endian)
    {
        using facet_type = go::utility::deletable_facet<std::codecvt_utf8_utf16<int16_t, 0x10ffffU, std::little_endian>>;
        std::wstring_convert<facet_type, int16_t> converter;
        auto xs = converter.from_bytes(u8s);
        return std::u16string(xs.begin(), xs.end());
    }
    else
    {
        using facet_type = go::utility::deletable_facet<std::codecvt_utf8_utf16<int16_t>>;
        std::wstring_convert<facet_type, int16_t> converter;
        auto xs = converter.from_bytes(u8s);
        return std::u16string(xs.begin(), xs.end());
    }
#else
    if (little_endian)
    {
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
        typedef go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t, 0x10ffffU, std::little_endian>> facet_type;
#else
        using facet_type = go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t, 0x10ffffU, std::little_endian>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
        std::wstring_convert<facet_type, char16_t> converter;
        return converter.from_bytes(u8s);
    }
    else
    {
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
        typedef go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t>> facet_type;
#else
        using facet_type = go::utility::deletable_facet<std::codecvt_utf8_utf16<char16_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
        std::wstring_convert<facet_type, char16_t> converter;
        return converter.from_bytes(u8s);
    }
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
}

inline std::u16string convert_u32string_to_u16string(const std::u32string& s)
{
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    using facet_type = go::utility::deletable_facet<std::codecvt_utf16<int32_t>>;
    std::wstring_convert<facet_type, int32_t> converter;
    auto p = reinterpret_cast<const int32_t*>(s.data());
    const std::string bytes = converter.to_bytes(p, p + s.size());
#else
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf16<char32_t>> facet_type;
#else
    using facet_type = go::utility::deletable_facet<std::codecvt_utf16<char32_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_type, char32_t> converter;
    const std::string bytes = converter.to_bytes(s);
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
    std::u16string u16s;
    u16s.reserve(bytes.size()/2);
    for (size_t i = 0; i < bytes.size(); i += 2)
    {
        u16s.push_back(static_cast<char16_t>(static_cast<unsigned char>(bytes[i])*256 + static_cast<unsigned char>(bytes[i+1])));
    }
    return u16s;
}

// to std::u32string

inline std::u32string convert_string_to_u32string(const std::string& s)
{
    return convert_u8string_to_u32string(convert_string_to_u8string(s));
}

inline std::u32string convert_u2string_to_u32string(const u2string& s)
{
    return convert_u16string_to_u32string(convert_u2string_to_u16string(s));
}

inline std::u32string convert_u8string_to_u32string(const u8string& s)
{
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8<int32_t>>;
    std::wstring_convert<facet_type, int32_t> converter;
    const std::string u8s(s.begin(), s.end());
    const auto xs = converter.from_bytes(u8s);
    return std::u32string(xs.begin(), xs.end());
#else
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf8<char32_t>> facet_type;
#else
    using facet_type = go::utility::deletable_facet<std::codecvt_utf8<char32_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_type, char32_t> converter;
    const std::string u8s(s.begin(), s.end());
    return converter.from_bytes(u8s);
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
}

inline std::u32string convert_u16string_to_u32string(const std::u16string& s)
{
    std::string bytes;
    bytes.reserve(s.size()*2);
#if !defined(GO_NO_CXX11_RANGE_FOR_LOOP)
    for (const char16_t c : s)
    {
        bytes.push_back(static_cast<char>(c/256));
        bytes.push_back(static_cast<char>(c%256));
    }
#else
    for (std::u16string::const_iterator i = s.begin(); i != s.end(); ++i)
    {
        const char16_t c = *i;
        bytes.push_back(static_cast<char>(c/256));
        bytes.push_back(static_cast<char>(c%256));
    }
#endif  // #if !defined(GO_NO_CXX11_RANGE_FOR_LOOP)
#if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    using facet_type = go::utility::deletable_facet<std::codecvt_utf16<int32_t>>;
    std::wstring_convert<facet_type, int32_t> converter;
    const auto xs = converter.from_bytes(bytes);
    return std::u32string(xs.begin(), xs.end());
#else
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef go::utility::deletable_facet<std::codecvt_utf16<char32_t>> facet_type;
#else
    using facet_type = go::utility::deletable_facet<std::codecvt_utf16<char32_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    std::wstring_convert<facet_type, char32_t> converter;
    return converter.from_bytes(bytes);
#endif  // #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)
}

}
}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_STRING_CONVERT_CONVERT_HPP_INCLUDED
