#ifndef GO_STRING_ISO_8859_1_HPP_INCLUDED
#define GO_STRING_ISO_8859_1_HPP_INCLUDED

//
//  iso_8859_1.hpp
//
//  Copyright 2017-2020 Göran Orsander
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
bool is_iso_8859_1_character(const C c);

template<>
inline bool is_iso_8859_1_character(const unsigned char c)
{
    if ((c < 0x20) || ((c > 0x7E) && (c < 0xA0)))
    {
        return false;
    }
    return true;
}

template<>
inline bool is_iso_8859_1_character(const char c)
{
    return is_iso_8859_1_character(static_cast<unsigned char>(c));
}

template<typename C>
inline bool is_iso_8859_1_character(const C c)
{
    if((c < 0x20) || ((c > 0x7E) && (c < 0xA0)) || (c > 0xFF))
    {
        return false;
    }
    return true;
}

template<class S>
inline bool is_iso_8859_1_string(const S& s)
{
    for (const typename S::value_type c : s)
    {
        if (!is_iso_8859_1_character(c))
        {
            return false;
        }
    }
    return true;
}

template<class S>
std::string& reduce_to_iso_8859_1(const S& s, std::string& iso88591s);

template<>
inline std::string& reduce_to_iso_8859_1(const u8string& s, std::string& iso88591s)
{
    iso88591s.clear();
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
            iso88591s.push_back(*it);
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
            if((cc >= 0xA0) && (cc <= 0xBF))
            {
                iso88591s.push_back(*it);
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
                iso88591s.push_back((*it) + 0x40);
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
    return iso88591s;
}

template<class S>
inline std::string& reduce_to_iso_8859_1(const S& s, std::string& iso88591s)
{
    iso88591s.clear();
    typename S::iterator it = s.begin();
    while (it != s.end())
    {
        const typename S::value_type c = *it;
        if (is_iso_8859_1_character(c))
        {
            iso88591s.push_back(static_cast<std::string::value_type>(c));
        }
        ++it;
    }
    return iso88591s;
}

template<class S>
inline S reduce_to_iso_8859_1_copy(const S& s)
{
    S a = s;
    reduce_to_iso_8859_1(a);
    return a;
}

}
}

#endif  // #ifndef GO_STRING_ISO_8859_1_HPP_INCLUDED
