#ifndef GO_UTILITY_STRING_DETAIL_STRING_CONVERT_HPP_INCLUDED
#define GO_UTILITY_STRING_DETAIL_STRING_CONVERT_HPP_INCLUDED

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

#include <locale>

#if defined(GO_PLATFORM_LINUX)
#include <go/utility/string/detail/string_convert_linux.hpp>
#endif  // #if defined(GO_PLATFORM_LINUX)
#if defined(GO_PLATFORM_WINDOWS)
#include <go/utility/string/detail/string_convert_windows.hpp>
#endif  // #if defined(GO_PLATFORM_WINDOWS)

#include <go/utility/string/detail/string_cast_fwd.hpp>

//
// IMPLEMENTATION NOTE #1
//
// ISSUE WITH VISUAL STUDIO 2015 AND 2017
// error LNK2001: unresolved external symbol "__declspec(dllimport) public: static class std::locale::id std::codecvt<char16_t,char,struct _Mbstatet>::id"
// See https://stackoverflow.com/questions/32055357/visual-studio-c-2015-stdcodecvt-with-char16-t-or-char32-t
//

namespace go
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
    std::wstring_convert<deletable_facet<std::codecvt<wchar_t, char, mbstate_t>>> converter;
    return converter.to_bytes(convert_u8string_to_wstring(s));
}

inline std::string convert_u16string_to_string(const std::u16string& s)
{
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<int16_t>>, int16_t> converter;
    auto p = reinterpret_cast<const int16_t*>(s.data());
    const std::string mbs = converter.to_bytes(p, p + s.size());
    #else
    std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<char16_t>>, char16_t> converter;
    const std::string mbs = converter.to_bytes(s);
    #endif
    return convert_u8string_to_string(u8string(mbs.begin(), mbs.end()));
}

inline std::string convert_u32string_to_string(const std::u32string& s)
{
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::wstring_convert<deletable_facet<std::codecvt_utf8<int32_t>>, int32_t> converter;
    auto p = reinterpret_cast<const int32_t*>(s.data());
    const std::string mbs = converter.to_bytes(p, p + s.size());
    #else
    std::wstring_convert<deletable_facet<std::codecvt_utf8<char32_t>>, char32_t> converter;
    const std::string mbs = converter.to_bytes(s);
    #endif
    return convert_u8string_to_string(u8string(mbs.begin(), mbs.end()));
}

// to std::wstring

inline std::wstring convert_u8string_to_wstring(const u8string& s)
{
    return convert_u16string_to_wstring(convert_u8string_to_u16string(s));
}

// to go::utility::u2string

inline u2string convert_string_to_u2string(const std::string& s)
{
    return convert_u8string_to_u2string(convert_string_to_u8string(s));
}

inline u2string convert_wstring_to_u2string(const std::wstring& s)
{
    return convert_u16string_to_u2string(convert_wstring_to_u16string(s));
}

inline u2string convert_u8string_to_u2string(const u8string& s)
{
    static const bool little_endian = is_little_endian_system();
    const std::string mbs(s.begin(), s.end());
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    if(little_endian)
    {
        std::wstring_convert<deletable_facet<std::codecvt_utf8<char2_t, 0x10ffffU, std::little_endian>>, char2_t> converter;
        auto xs = converter.from_bytes(mbs);
        return u2string(xs.begin(), xs.end());
    }
    else
    {
        std::wstring_convert<deletable_facet<std::codecvt_utf8<char2_t>>, char2_t> converter;
        auto xs = converter.from_bytes(mbs);
        return u2string(xs.begin(), xs.end());
    }
    #else
    if (little_endian)
    {
        std::wstring_convert<deletable_facet<std::codecvt_utf8<char16_t, 0x10ffffU, std::little_endian>>, char16_t> converter;
        return converter.from_bytes(mbs);
    }
    else
    {
        std::wstring_convert<deletable_facet<std::codecvt_utf8<char16_t>>, char16_t> converter;
        return converter.from_bytes(mbs);
    }
    #endif
}

inline u2string convert_u16string_to_u2string(const std::u16string& s)
{
    std::string bytes;
    bytes.reserve(s.size()*2);
    for (const char2_t c : s)
    {
        bytes.push_back(static_cast<char>(c/256));
        bytes.push_back(static_cast<char>(c%256));
    }
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::wstring_convert<deletable_facet<std::codecvt_utf16<int16_t>>, int16_t> converter;
    const auto u16s = converter.from_bytes(bytes);
    return u2string(u16s.begin(), u16s.end());
    #else
    std::wstring_convert<deletable_facet<std::codecvt_utf16<char16_t>>, char16_t> converter;
    const std::u16string u16s = converter.from_bytes(bytes);
    return u2string(u16s.begin(), u16s.end());
    #endif
}

inline u2string convert_u32string_to_u2string(const std::u32string& s)
{
    return convert_u16string_to_u2string(convert_u32string_to_u16string(s));
}

// to go::utility::u8string

inline u8string convert_string_to_u8string(const std::string& s)
{
    return convert_wstring_to_u8string(convert_string_to_wstring(s));
}

inline u8string convert_wstring_to_u8string(const std::wstring& s)
{
    const std::u16string u16s = convert_wstring_to_u16string(s);
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<int16_t>>, int16_t> converter;
    auto p = reinterpret_cast<const int16_t*>(u16s.data());
    const std::string mbs = converter.to_bytes(p, p + u16s.size());
    #else
    std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<char16_t>>, char16_t> converter;
    const std::string mbs = converter.to_bytes(u16s);
    #endif
    return u8string(mbs.begin(), mbs.end());
}

inline u8string convert_u2string_to_u8string(const u2string& s)
{
    std::wstring_convert<deletable_facet<std::codecvt_utf8<char2_t>>, char2_t> converter;
    const std::string mbs = converter.to_bytes(s);
    return u8string(mbs.begin(), mbs.end());
}

inline u8string convert_u16string_to_u8string(const std::u16string& s)
{
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<int16_t>>, int16_t> converter;
    auto p = reinterpret_cast<const int16_t*>(s.data());
    const std::string mbs = converter.to_bytes(p, p + s.size());
    #else
    std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<char16_t>>, char16_t> converter;
    const std::string mbs = converter.to_bytes(s);
    #endif
    return u8string(mbs.begin(), mbs.end());
}

inline u8string convert_u32string_to_u8string(const std::u32string& s)
{
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::wstring_convert<deletable_facet<std::codecvt_utf8<int32_t>>, int32_t> converter;
    auto p = reinterpret_cast<const int32_t*>(s.data());
    const std::string mbs = converter.to_bytes(p, p + s.size());
    #else
    std::wstring_convert<deletable_facet<std::codecvt_utf8<char32_t>>, char32_t> converter;
    const std::string mbs = converter.to_bytes(s);
    #endif
    return u8string(mbs.begin(), mbs.end());
}

// to std::u16string

inline std::u16string convert_string_to_u16string(const std::string& s)
{
    return convert_u8string_to_u16string(convert_string_to_u8string(s));
}

inline std::u16string convert_u2string_to_u16string(const u2string& s)
{
    std::string bytes;
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::wstring_convert<std::codecvt_utf16<int16_t>, int16_t> converter;
    auto p = reinterpret_cast<const int16_t*>(s.data());
    bytes = converter.to_bytes(p, p + s.size());
    #else
    std::wstring_convert<std::codecvt_utf16<char16_t>, char16_t> converter;
    bytes = converter.to_bytes(s);
    #endif
    std::u16string result;
    result.reserve(bytes.size()/2);
    for (size_t i = 0; i < bytes.size(); i += 2)
    {
        result.push_back(static_cast<char16_t>(static_cast<unsigned char>(bytes[i])*256+static_cast<unsigned char>(bytes[i+1])));
    }
    return result;
}

inline std::u16string convert_u8string_to_u16string(const u8string& s)
{
    static const bool little_endian = is_little_endian_system();
    const std::string mbs(s.begin(), s.end());
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    if(little_endian)
    {
        std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<int16_t, 0x10ffffU, std::little_endian>>, int16_t> converter;
        auto xs = converter.from_bytes(mbs);
        return std::u16string(xs.begin(), xs.end());
    }
    else
    {
        std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<int16_t>>, int16_t> converter;
        auto xs = converter.from_bytes(mbs);
        return std::u16string(xs.begin(), xs.end());
    }
    #else
    if (little_endian)
    {
        std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<char16_t, 0x10ffffU, std::little_endian>>, char16_t> converter;
        return converter.from_bytes(mbs);
    }
    else
    {
        std::wstring_convert<deletable_facet<std::codecvt_utf8_utf16<char16_t>>, char16_t> converter;
        return converter.from_bytes(mbs);
    }
    #endif
}

inline std::u16string convert_u32string_to_u16string(const std::u32string& s)
{
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::wstring_convert<deletable_facet<std::codecvt_utf16<int32_t>>, int32_t> converter;
    auto p = reinterpret_cast<const int32_t*>(s.data());
    const std::string bytes = converter.to_bytes(p, p + s.size());
    #else
    std::wstring_convert<deletable_facet<std::codecvt_utf16<char32_t>>, char32_t> converter;
    const std::string bytes = converter.to_bytes(s);
    #endif
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
    std::wstring_convert<deletable_facet<std::codecvt_utf8<int32_t>>, int32_t> converter;
    const std::string mbs(s.begin(), s.end());
    const auto xs = converter.from_bytes(mbs);
    return std::u32string(xs.begin(), xs.end());
    #else
    std::wstring_convert<deletable_facet<std::codecvt_utf8<char32_t>>, char32_t> converter;
    const std::string mbs(s.begin(), s.end());
    return converter.from_bytes(mbs);
    #endif
}

inline std::u32string convert_u16string_to_u32string(const std::u16string& s)
{
    std::string bytes;
    bytes.reserve(s.size()*2);
    for (const char16_t c : s)
    {
        bytes.push_back(static_cast<char>(c/256));
        bytes.push_back(static_cast<char>(c%256));
    }
    #if defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1800)  // See implementation note #1
    std::wstring_convert<std::codecvt_utf16<int32_t>, int32_t> converter;
    const auto xs = converter.from_bytes(bytes);
    return std::u32string(xs.begin(), xs.end());
    #else
    std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> converter;
    return converter.from_bytes(bytes);
    #endif
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

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_STRING_DETAIL_STRING_CONVERT_HPP_INCLUDED
