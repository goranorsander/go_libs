#ifndef GO_STRING_ENCODING_UCS2_HPP_INCLUDED
#define GO_STRING_ENCODING_UCS2_HPP_INCLUDED

//
//  ucs2.hpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/string/u2string.hpp>
#include <go/string/u8string.hpp>

namespace go
{
namespace string
{
namespace encoding
{

struct ucs2_tag {};

inline bool try_convert_from_ucs2(const char2_t ucs2ch, uft8_character_type& utf8ch)
{
    utf8ch.clear();

    if (ucs2ch < 0x0080)
    {
        utf8ch.push_back(static_cast<char8_t>(ucs2ch));
        return true;
    }
    else if (ucs2ch < 0x0800)
    {
        utf8ch.push_back(static_cast<char8_t>(0x00C0 | (ucs2ch >> 6)));
        utf8ch.push_back(static_cast<char8_t>(0x0080 | (ucs2ch & 0x003F)));
        return true;
    }
    else
    {
        utf8ch.push_back(static_cast<char8_t>(0x00E0 | (ucs2ch >> 12)));
        utf8ch.push_back(static_cast<char8_t>(0x0080 | ((ucs2ch >> 6) & 0x003F)));
        utf8ch.push_back(static_cast<char8_t>(0x0080 | (ucs2ch & 0x003F)));
        return true;
    }

    return false;
}

inline bool try_convert_to_ucs2(char2_t& ucs2ch, const uft8_character_type& utf8ch)
{
    ucs2ch = 0;

    if (utf8ch.empty())
    {
        return false;
    }

    uft8_character_type::const_iterator utf8ch0 = utf8ch.begin();
    if (((*utf8ch0) < 0x80) && (utf8ch.size() == 1))
    {
        ucs2ch = static_cast<char2_t>(*utf8ch0);
        return true;
    }
    else if ((((*utf8ch0) & 0xE0) == 0xC0) && (utf8ch.size() == 2))
    {
        uft8_character_type::const_iterator utf8ch1 = utf8ch0;
        ++utf8ch1;
        if (((*utf8ch1) & 0xC0) == 0x80)
        {
            ucs2ch = (static_cast<char2_t>((*utf8ch0) & 0x1F) << 6);
            ucs2ch |= static_cast<char2_t>((*utf8ch1) & 0x3F);
            return true;
        }
    }
    else if ((((*utf8ch0) & 0xF0) == 0xE0) && (utf8ch.size() == 3))
    {
        uft8_character_type::const_iterator utf8ch1 = utf8ch0;
        ++utf8ch1;
        uft8_character_type::const_iterator utf8ch2 = utf8ch1;
        ++utf8ch2;
        if ((((*utf8ch1) & 0xC0) == 0x80) && (((*utf8ch2) & 0xC0) == 0x80))
        {
            ucs2ch = (static_cast<char2_t>((*utf8ch0) & 0x0F) << 12);
            ucs2ch |= (static_cast<char2_t>((*utf8ch1) & 0x3F) << 6);
            ucs2ch |= static_cast<char2_t>((*utf8ch2) & 0x3F);
            return true;
        }
    }
    return false;
}

}
}
}

#endif  // #ifndef GO_STRING_ENCODING_UCS2_HPP_INCLUDED
