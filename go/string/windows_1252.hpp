#ifndef GO_STRING_WINDOWS_1252_HPP_INCLUDED
#define GO_STRING_WINDOWS_1252_HPP_INCLUDED

//
//  windows_1252.hpp
//
//  Copyright 2018-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <string>
#include <go/string/u8string.hpp>

namespace go
{
namespace string
{

template<typename C>
bool is_windows_1252_character(const C c);

template<>
inline bool is_windows_1252_character(const unsigned char c)
{
    if ((c < 0x20) || (c == 0x7F) || (c == 0x81) || (c == 0x8D) || (c == 0x8F) || (c == 0x90) || (c == 0x9D) || (c > 0xFF))
    {
        return false;
    }
    return true;
}

template<>
inline bool is_windows_1252_character(const char c)
{
    return is_windows_1252_character(static_cast<unsigned char>(c));
}

template<typename C>
inline bool is_windows_1252_character(const C c)
{
    if ((c < 0x20) || (c == 0x7F) || (c == 0x81) || (c == 0x8D) || (c == 0x8F) || (c == 0x90) || (c == 0x9D) || (c > 0xFF))
    {
        return false;
    }
    return true;
}

template<class S>
inline bool is_windows_1252_string(const S& s)
{
    for (const typename S::value_type c : s)
    {
        if (!is_windows_1252_character(c))
        {
            return false;
        }
    }
    return true;
}

template<class S>
std::string& reduce_to_windows_1252(const S& s, std::string& windows1252s);

template<>
inline std::string& reduce_to_windows_1252(const u8string& s, std::string& windows1252s)
{
    windows1252s.clear();
    u8string::const_iterator it = s.begin();
    while (it != s.end())
    {
        const unsigned char c = static_cast<unsigned char>(*it);
        if (c < 0x20)
        {
            ++it;
        }
        else if (c < 0x7F)
        {
            windows1252s.push_back(*it);
            ++it;
        }
        else if ((c >= 0x7F) && (c <= 0xC1))
        {
            ++it;
        }
        else if (c == 0xC2)
        {
            ++it;
            const unsigned char cc = static_cast<unsigned char>(*it);
            if((cc == 0x80) || ((cc >= 0x82) && (cc <= 0x8C)) || (cc == 0x8E) || ((cc >= 0x91) && (cc <= 0x9C)) || ((cc >= 0x9E) && (cc <= 0xBF)))
            {
                windows1252s.push_back(*it);
                ++it;
            }
            else
            {
                ++it;
            }
        }
        else if (c == 0xC3)
        {
            ++it;
            const unsigned char cc = static_cast<unsigned char>(*it);
            if ((cc >= 0x80) && (cc <= 0xBF))
            {
                windows1252s.push_back((*it) + 0x40);
                ++it;
            }
            else
            {
                ++it;
            }
        }
        else if ((c >= 0xC4) && (c < 0xE0))
        {
            std::advance(it, 2);
        }
        else if ((c >= 0xE0) && (c < 0xF0))
        {
            std::advance(it, 3);
        }
        else if ((c >= 0xF0) && (c < 0xFC))
        {
            std::advance(it, 4);
        }
        else if ((c >= 0xFC) && (c < 0xFE))
        {
            std::advance(it, 5);
        }
        else
        {
            std::advance(it, 6);
        }
    }
    return windows1252s;
}

template<class S>
inline std::string& reduce_to_windows_1252(const S& s, std::string& windows1252s)
{
    windows1252s.clear();
    typename S::iterator it = s.begin();
    while (it != s.end())
    {
        const typename S::value_type c = *it;
        if (is_windows_1252_character(c))
        {
            windows1252s.push_back(static_cast<std::string::value_type>(c));
        }
        ++it;
    }
    return windows1252s;
}

template<class S>
inline S reduce_to_windows_1252_copy(const S& s)
{
    S a = s;
    reduce_to_windows_1252(a);
    return a;
}

}
}

#endif  // #ifndef GO_STRING_WINDOWS_1252_HPP_INCLUDED
