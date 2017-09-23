#ifndef GO_BOOST_UTILITY_STRING_ALGORITHM_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_ALGORITHM_HPP_INCLUDED

//
//  algorithm.hpp
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

#include <string>
#include <go_boost/utility/u2string.hpp>
#include <go_boost/utility/u8string.hpp>
#include <go_boost/utility/u16string.hpp>
#include <go_boost/utility/u32string.hpp>

namespace go_boost
{
namespace utility
{
namespace string
{

template<class S>
inline bool equals(const S& s1, const S& s2)
{
    if (s1.size() == s2.size())
    {
        for (typename S::const_iterator i1 = s1.begin(), i2 = s2.begin(), e = s1.end(); i1 != e; ++i1, ++i2)
        {
            if (*i1 != *i2)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

inline std::string copy_to_multibyte_string(const std::wstring& sws)
{
    std::string mbs;
    for (std::wstring::const_iterator it = sws.begin(); it != sws.end(); ++it)
    {
#if defined(GO_BOOST_PLATFORM_WINDOWS)
        const unsigned short ch = static_cast<unsigned short>(*it);
        const unsigned char ch0 = static_cast<unsigned char>(ch & 0x00FF);
        const unsigned char ch1 = static_cast<unsigned char>(ch >> 8);
        mbs += static_cast<typename std::string::value_type>(ch0);
        mbs += static_cast<typename std::string::value_type>(ch1);
#else
        const unsigned long ch = static_cast<unsigned long>(*it);
        const unsigned char ch0 = static_cast<unsigned char>(ch & 0x00FF);
        const unsigned char ch1 = static_cast<unsigned char>((ch >> 8) & 0x00FF);
        const unsigned char ch2 = static_cast<unsigned char>((ch >> 16) & 0x00FF);
        const unsigned char ch3 = static_cast<unsigned char>(ch >> 24);
        mbs += static_cast<typename std::string::value_type>(ch0);
        mbs += static_cast<typename std::string::value_type>(ch1);
        mbs += static_cast<typename std::string::value_type>(ch2);
        mbs += static_cast<typename std::string::value_type>(ch3);
#endif  // #if defined(GO_BOOST_PLATFORM_WINDOWS)
    }
    return mbs;
}

inline std::string copy_to_multibyte_string(const u2string& u2s)
{
    std::string mbs;
    for (u2string::const_iterator it = u2s.begin(); it != u2s.end(); ++it)
    {
        const unsigned short ch = static_cast<unsigned short>(*it);
        const unsigned char ch0 = static_cast<unsigned char>(ch & 0x00FF);
        const unsigned char ch1 = static_cast<unsigned char>(ch >> 8);
        mbs += static_cast<typename std::string::value_type>(ch0);
        mbs += static_cast<typename std::string::value_type>(ch1);
    }
    return mbs;
}

inline std::string copy_to_multibyte_string(const u8string& u8s)
{
    const std::string mbs(u8s.begin(), u8s.end());
    return mbs;
}

inline std::string copy_to_multibyte_string(const u16string& u16s)
{
    std::string mbs;
    for (u16string::const_iterator it = u16s.begin(); it != u16s.end(); ++it)
    {
        const unsigned short ch = static_cast<unsigned short>(*it);
        const unsigned char ch0 = static_cast<unsigned char>(ch & 0x00FF);
        const unsigned char ch1 = static_cast<unsigned char>(ch >> 8);
        mbs += static_cast<typename std::string::value_type>(ch0);
        mbs += static_cast<typename std::string::value_type>(ch1);
    }
    return mbs;
}

inline std::string copy_to_multibyte_string(const u32string& u32s)
{
    std::string mbs;
    for (u32string::const_iterator it = u32s.begin(); it != u32s.end(); ++it)
    {
        const unsigned long ch = static_cast<unsigned long>(*it);
        const unsigned char ch0 = static_cast<unsigned char>(ch & 0x00FF);
        const unsigned char ch1 = static_cast<unsigned char>((ch >> 8) & 0x00FF);
        const unsigned char ch2 = static_cast<unsigned char>((ch >> 16) & 0x00FF);
        const unsigned char ch3 = static_cast<unsigned char>(ch >> 24);
        mbs += static_cast<typename std::string::value_type>(ch0);
        mbs += static_cast<typename std::string::value_type>(ch1);
        mbs += static_cast<typename std::string::value_type>(ch2);
        mbs += static_cast<typename std::string::value_type>(ch3);
    }
    return mbs;
}

inline bool try_copy_from_multibyte_string(const std::string& mbs, std::wstring& sws)
{
    sws.clear();
    if (mbs.empty())
    {
        return true;
    }
#if defined(GO_BOOST_PLATFORM_WINDOWS)
    if (sws.size() % 2 == 0)
    {
        std::string::const_iterator it = mbs.begin();
        const std::string::const_iterator endit = mbs.end();
        while (it != endit)
        {
            const unsigned char c0 = *it;
            ++it;
            const unsigned char c1 = *it;
            ++it;
            unsigned short c = static_cast<unsigned short>(c0);
            c <<= 8;
            c += static_cast<unsigned short>(c1);
            sws += static_cast<typename std::wstring::value_type>(c);
        }
        return true;
    }
#else
    if (sws.size() % 4 == 0)
    {
        std::string::const_iterator it = mbs.begin();
        const std::string::const_iterator endit = mbs.end();
        while (it != endit)
        {
            const unsigned char c0 = *it;
            ++it;
            const unsigned char c1 = *it;
            ++it;
            const unsigned char c2 = *it;
            ++it;
            const unsigned char c3 = *it;
            ++it;
            unsigned long c = static_cast<unsigned short>(c0);
            c <<= 8;
            c += static_cast<unsigned long>(c1);
            c <<= 8;
            c += static_cast<unsigned long>(c2);
            c <<= 8;
            c += static_cast<unsigned long>(c3);
            sws += static_cast<typename std::wstring::value_type>(c);
        }
        return true;
    }
#endif  // #if defined(GO_BOOST_PLATFORM_WINDOWS)
    return false;
}

inline bool try_copy_from_multibyte_string(const std::string& mbs, u2string& u2s)
{
    u2s.clear();
    if (mbs.empty())
    {
        return true;
    }
    if (u2s.size() % 2 == 0)
    {
        std::string::const_iterator it = mbs.begin();
        const std::string::const_iterator endit = mbs.end();
        while (it != endit)
        {
            const unsigned char c0 = *it;
            ++it;
            const unsigned char c1 = *it;
            ++it;
            unsigned short c = static_cast<unsigned short>(c0);
            c <<= 8;
            c += static_cast<unsigned short>(c1);
            u2s += static_cast<typename std::wstring::value_type>(c);
        }
        return true;
    }
    return false;
}

inline bool try_copy_from_multibyte_string(const std::string& mbs, u8string& u8s)
{
    u8s.clear();
    if (mbs.empty())
    {
        return true;
    }
    std::string::const_iterator it = mbs.begin();
    const std::string::const_iterator endit = mbs.end();
    while (it != endit)
    {
        const unsigned char c0 = *it;
        ++it;
        u8s += static_cast<typename u8string::value_type>(c0);
    }
    return true;
}

inline bool try_copy_from_multibyte_string(const std::string& mbs, u16string& u16s)
{
    u16s.clear();
    if (mbs.empty())
    {
        return true;
    }
    if (u16s.size() % 2 == 0)
    {
        std::string::const_iterator it = mbs.begin();
        const std::string::const_iterator endit = mbs.end();
        while (it != endit)
        {
            const unsigned char c0 = *it;
            ++it;
            const unsigned char c1 = *it;
            ++it;
            unsigned short c = static_cast<unsigned short>(c0);
            c <<= 8;
            c += static_cast<unsigned short>(c1);
            u16s += static_cast<typename u16string::value_type>(c);
        }
        return true;
    }
    return false;
}

inline bool try_copy_from_multibyte_string(const std::string& mbs, u32string& u32s)
{
    u32s.clear();
    if (mbs.empty())
    {
        return true;
    }
    if (u32s.size() % 4 == 0)
    {
        std::string::const_iterator it = mbs.begin();
        const std::string::const_iterator endit = mbs.end();
        while (it != endit)
        {
            const unsigned char c0 = *it;
            ++it;
            const unsigned char c1 = *it;
            ++it;
            const unsigned char c2 = *it;
            ++it;
            const unsigned char c3 = *it;
            ++it;
            unsigned long c = static_cast<unsigned short>(c0);
            c <<= 8;
            c += static_cast<unsigned long>(c1);
            c <<= 8;
            c += static_cast<unsigned long>(c2);
            c <<= 8;
            c += static_cast<unsigned long>(c3);
            u32s += static_cast<typename u32string::value_type>(c);
        }
        return true;
    }
    return false;
}

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_ALGORITHM_HPP_INCLUDED
