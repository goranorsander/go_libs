#ifndef GO_UTILITY_STRING_ASCII_HPP_INCLUDED
#define GO_UTILITY_STRING_ASCII_HPP_INCLUDED

//
//  ascii.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <string>
#include <go/utility/u8string.hpp>

namespace go
{
namespace utility
{
namespace string
{

template<typename C>
bool is_7_bit_ascii_character(const C c);

template<>
inline bool is_7_bit_ascii_character(const unsigned char c)
{
    static const unsigned char mask = 0x80;

    if (c & mask)
    {
        return false;
    }
    return true;
}

template<>
inline bool is_7_bit_ascii_character(const char c)
{
    return is_7_bit_ascii_character(static_cast<unsigned char>(c));
}

template<typename C>
inline bool is_7_bit_ascii_character(const C c)
{
    if(c < 0 || c > 0x7F)
    {
        return false;
    }
    return true;
}

template<class S>
inline bool is_7_bit_ascii_string(const S& s)
{
    for (const S::value_type c : s)
    {
        if (!is_7_bit_ascii_character(c))
        {
            return false;
        }
    }
    return true;
}

template<class S>
inline S& reduce_to_7_bit_ascii(S& s)
{
    S::iterator it = s.begin();
    while (it != s.end())
    {
        const S::value_type c = *it;
        if (is_7_bit_ascii_character(c))
        {
            ++it;
        }
        else
        {
            it = s.erase(it);
        }
    }
    return s;
}

template<class S>
inline S reduce_to_7_bit_ascii_copy(const S& s)
{
    S a = s;
    reduce_to_7_bit_ascii(a);
    return a;
}

template<class S>
inline S& reduce_iso_8859_1_to_7_bit_ascii(S& s, const bool strict = true);

template<>
inline u8string& reduce_iso_8859_1_to_7_bit_ascii(u8string& s, const bool strict)
{
    if (strict)
    {
        return reduce_to_7_bit_ascii(s);
    }
    u8string::size_type pos = 0;
    u8string::iterator it = s.begin();
    while (it != s.end())
    {
        const unsigned char c = static_cast<unsigned char>(*it);
        if (c < 0x80)
        {
            ++it;
            ++pos;
        }
        else if ((c >= 0x80) && (c <= 0xC1))
        {
            it = s.erase(it);
        }
        else if (c == 0xC2)
        {
            it = s.erase(it);
            const unsigned char cc = static_cast<unsigned char>(*it);
            bool increment = true;
            switch (cc)
            {
            case 0xA0: s[pos] = static_cast<u8string::value_type>(0x20); break; // NBSP -> SP
            case 0xA1: s[pos] = static_cast<u8string::value_type>(0x21); break; // ¡ -> !
            case 0xA2: s[pos] = static_cast<u8string::value_type>(0x63); break; // ¢ -> c
            case 0xA3: s[pos] = static_cast<u8string::value_type>(0x50); break; // £ -> P
            case 0xA4: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ¤ -> o
            case 0xA5: s[pos] = static_cast<u8string::value_type>(0x59); break; // ¥ -> Y
            case 0xA6: s[pos] = static_cast<u8string::value_type>(0x7C); break; // ¦ -> |
            case 0xA7: s[pos] = static_cast<u8string::value_type>(0x70); break; // § -> p
            case 0xA8: s[pos] = static_cast<u8string::value_type>(0x22); break; // ¨ -> "
            case 0xA9: // © -> (c)
                s[pos] = static_cast<u8string::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x63));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x29));
                break;
            case 0xAA: s[pos] = static_cast<u8string::value_type>(0x61); break; // ª -> a
            case 0xAB: // « -> <<
                s[pos] = static_cast<u8string::value_type>(0x3C);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x3C));
                break;
            case 0xAC: s[pos] = static_cast<u8string::value_type>(0x2D); break; // ¬ -> -
            case 0xAD: // SHY -> erase
                it = s.erase(it);
                increment = false;
                break;
            case 0xAE: // ® -> (R)
                s[pos] = static_cast<u8string::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x52));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x29));
                break;
            case 0xAF: s[pos] = static_cast<u8string::value_type>(0x2D); break; // ¯ -> -

            case 0xB0: s[pos] = static_cast<u8string::value_type>(0x67); break; // ° -> g
            case 0xB1: // ± -> +/-
                s[pos] = static_cast<u8string::value_type>(0x2B);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2D));
                break;
            case 0xB2: // ² -> ^2
                s[pos] = static_cast<u8string::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x32));
                break;
            case 0xB3: // ³ -> ^3
                s[pos] = static_cast<u8string::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x33));
                break;
            case 0xB4: s[pos] = static_cast<u8string::value_type>(0x27); break; // ´ -> '
            case 0xB5: s[pos] = static_cast<u8string::value_type>(0x75); break; // µ -> u
            case 0xB6: s[pos] = static_cast<u8string::value_type>(0x39); break; // ¶ -> 9
            case 0xB7: s[pos] = static_cast<u8string::value_type>(0x2A); break; // · -> *
            case 0xB8: s[pos] = static_cast<u8string::value_type>(0x2E); break; // ¸ -> .
            case 0xB9: // ¹ -> ^1
                s[pos] = static_cast<u8string::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x31));
                break;
            case 0xBA: // º -> ^0
                s[pos] = static_cast<u8string::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x30));
                break;
            case 0xBB: // » -> >>
                s[pos] = static_cast<u8string::value_type>(0x3E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x3E));
                break;
            case 0xBC: // ¼ -> 1/4
                s[pos] = static_cast<u8string::value_type>(0x31);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x34));
                break;
            case 0xBD: // ½ -> 1/2
                s[pos] = static_cast<u8string::value_type>(0x31);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x32));
                break;
            case 0xBE: // ¾ -> 3/4
                s[pos] = static_cast<u8string::value_type>(0x33);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x34));
                break;
            case 0xBF: s[pos] = static_cast<u8string::value_type>(0x3F); break; // ¿ -> ?

            default: // erase
                it = s.erase(it);
                increment = false;
                break;
            }
            if (increment)
            {
                ++it;
                ++pos;
            }
        }
        else if (c == 0xC3)
        {
            it = s.erase(it);
            const unsigned char cc = static_cast<unsigned char>(*it);
            bool increment = true;
            switch (cc)
            {
            case 0x80: s[pos] = static_cast<u8string::value_type>(0x41); break; // À -> A
            case 0x81: s[pos] = static_cast<u8string::value_type>(0x41); break; // Á -> A
            case 0x82: s[pos] = static_cast<u8string::value_type>(0x41); break; // Â -> A
            case 0x83: s[pos] = static_cast<u8string::value_type>(0x41); break; // Ã -> A
            case 0x84: s[pos] = static_cast<u8string::value_type>(0x41); break; // Ä -> A
            case 0x85: s[pos] = static_cast<u8string::value_type>(0x41); break; // Å -> A
            case 0x86: // Æ -> AE
                s[pos] = static_cast<u8string::value_type>(0x41);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x45));
                break;
            case 0x87: s[pos] = static_cast<u8string::value_type>(0x43); break; // Ç -> C
            case 0x88: s[pos] = static_cast<u8string::value_type>(0x45); break; // È -> E
            case 0x89: s[pos] = static_cast<u8string::value_type>(0x45); break; // É -> E
            case 0x8A: s[pos] = static_cast<u8string::value_type>(0x45); break; // Ê -> E
            case 0x8B: s[pos] = static_cast<u8string::value_type>(0x45); break; // Ë -> E
            case 0x8C: s[pos] = static_cast<u8string::value_type>(0x49); break; // Ì -> I
            case 0x8D: s[pos] = static_cast<u8string::value_type>(0x49); break; // Í -> I
            case 0x8E: s[pos] = static_cast<u8string::value_type>(0x49); break; // Î -> I
            case 0x8F: s[pos] = static_cast<u8string::value_type>(0x49); break; // Ï -> I

            case 0x90: s[pos] = static_cast<u8string::value_type>(0x44); break; // Ð -> D
            case 0x91: s[pos] = static_cast<u8string::value_type>(0x4E); break; // Ñ -> N
            case 0x92: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ò -> O
            case 0x93: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ó -> O
            case 0x94: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ô -> O
            case 0x95: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Õ -> O
            case 0x96: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ö -> O
            case 0x97: s[pos] = static_cast<u8string::value_type>(0x78); break; // × -> x
            case 0x98: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ø -> O
            case 0x99: s[pos] = static_cast<u8string::value_type>(0x55); break; // Ù -> U
            case 0x9A: s[pos] = static_cast<u8string::value_type>(0x55); break; // Ú -> U
            case 0x9B: s[pos] = static_cast<u8string::value_type>(0x55); break; // Û -> U
            case 0x9C: s[pos] = static_cast<u8string::value_type>(0x55); break; // Ü -> U
            case 0x9D: s[pos] = static_cast<u8string::value_type>(0x59); break; // Ý -> Y
            case 0x9E: s[pos] = static_cast<u8string::value_type>(0x50); break; // Þ -> P
            case 0x9F: s[pos] = static_cast<u8string::value_type>(0x42); break; // ß -> B

            case 0xA0: s[pos] = static_cast<u8string::value_type>(0x61); break; // à -> a
            case 0xA1: s[pos] = static_cast<u8string::value_type>(0x61); break; // á -> a
            case 0xA2: s[pos] = static_cast<u8string::value_type>(0x61); break; // â -> a
            case 0xA3: s[pos] = static_cast<u8string::value_type>(0x61); break; // ã -> a
            case 0xA4: s[pos] = static_cast<u8string::value_type>(0x61); break; // ä -> a
            case 0xA5: s[pos] = static_cast<u8string::value_type>(0x61); break; // å -> a
            case 0xA6: s[pos] = // æ -> ae
                s[pos] = static_cast<u8string::value_type>(0x61);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x65));
                break;
            case 0xA7: s[pos] = static_cast<u8string::value_type>(0x63); break; // ç -> c
            case 0xA8: s[pos] = static_cast<u8string::value_type>(0x65); break; // è -> e
            case 0xA9: s[pos] = static_cast<u8string::value_type>(0x65); break; // é -> e
            case 0xAA: s[pos] = static_cast<u8string::value_type>(0x65); break; // ê -> e
            case 0xAB: s[pos] = static_cast<u8string::value_type>(0x65); break; // ë -> e
            case 0xAC: s[pos] = static_cast<u8string::value_type>(0x69); break; // ì -> i
            case 0xAD: s[pos] = static_cast<u8string::value_type>(0x69); break; // í -> i
            case 0xAE: s[pos] = static_cast<u8string::value_type>(0x69); break; // î -> i
            case 0xAF: s[pos] = static_cast<u8string::value_type>(0x69); break; // ï -> i

            case 0xB0: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ð -> o
            case 0xB1: s[pos] = static_cast<u8string::value_type>(0x6E); break; // ñ -> n
            case 0xB2: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ò -> o
            case 0xB3: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ó -> o
            case 0xB4: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ô -> o
            case 0xB5: s[pos] = static_cast<u8string::value_type>(0x6F); break; // õ -> o
            case 0xB6: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ö -> o
            case 0xB7: s[pos] = static_cast<u8string::value_type>(0x2F); break; // ÷ -> /
            case 0xB8: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ø -> o
            case 0xB9: s[pos] = static_cast<u8string::value_type>(0x75); break; // ù -> u
            case 0xBA: s[pos] = static_cast<u8string::value_type>(0x75); break; // ú -> u
            case 0xBB: s[pos] = static_cast<u8string::value_type>(0x75); break; // û -> u
            case 0xBC: s[pos] = static_cast<u8string::value_type>(0x75); break; // ü -> u
            case 0xBD: s[pos] = static_cast<u8string::value_type>(0x79); break; // ý -> y
            case 0xBE: s[pos] = static_cast<u8string::value_type>(0x70); break; // þ -> p
            case 0xBF: s[pos] = static_cast<u8string::value_type>(0x79); break; // ÿ -> y

            default: // erase
                it = s.erase(it);
                increment = false;
                break;
            }
            if (increment)
            {
                ++it;
                ++pos;
            }
        }
        else if ((c >= 0xC4) && (c <= 0xDF))
        {
            it = s.erase(it);
            it = s.erase(it);
        }
        else if ((c >= 0xE0) && (c <= 0xEF))
        {
            it = s.erase(it);
            it = s.erase(it);
            it = s.erase(it);
        }
        else
        {
            it = s.erase(it);
            it = s.erase(it);
            it = s.erase(it);
            it = s.erase(it);
        }
    }
    return s;
}

template<class S>
inline S& reduce_iso_8859_1_to_7_bit_ascii(S& s, const bool strict)
{
    if (strict)
    {
        return reduce_to_7_bit_ascii(s);
    }
    S::size_type pos = 0;
    S::iterator it = s.begin();
    while (it != s.end())
    {
        const unsigned char c = static_cast<unsigned char>(*it);
        if ((c < 0x20) || (c == 0x7F))
        {
            ++it;
            ++pos;
        }
        else if ((c >= 0x80) && (c <= 0x9F))
        {
            it = s.erase(it);
        }
        else
        {
            bool increment = true;
            switch (c)
            {
            case 0xA0: s[pos] = static_cast<S::value_type>(0x20); break; // NBSP -> SP
            case 0xA1: s[pos] = static_cast<S::value_type>(0x21); break; // ¡ -> !
            case 0xA2: s[pos] = static_cast<S::value_type>(0x63); break; // ¢ -> c
            case 0xA3: s[pos] = static_cast<S::value_type>(0x50); break; // £ -> P
            case 0xA4: s[pos] = static_cast<S::value_type>(0x6F); break; // ¤ -> o
            case 0xA5: s[pos] = static_cast<S::value_type>(0x59); break; // ¥ -> Y
            case 0xA6: s[pos] = static_cast<S::value_type>(0x7C); break; // ¦ -> |
            case 0xA7: s[pos] = static_cast<S::value_type>(0x70); break; // § -> p
            case 0xA8: s[pos] = static_cast<S::value_type>(0x22); break; // ¨ -> "
            case 0xA9: // © -> (c)
                s[pos] = static_cast<S::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x63));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x29));
                break;
            case 0xAA: s[pos] = static_cast<S::value_type>(0x61); break; // ª -> a
            case 0xAB: // « -> <<
                s[pos] = static_cast<u8string::value_type>(0x3C);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x3C));
                break;
            case 0xAC: s[pos] = static_cast<S::value_type>(0x2D); break; // ¬ -> -
            case 0xAD: // SHY -> erase
                it = s.erase(it);
                increment = false;
                break;
            case 0xAE: // ® -> (R)
                s[pos] = static_cast<S::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x52));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x29));
                break;
            case 0xAF: s[pos] = static_cast<S::value_type>(0x2D); break; // ¯ -> -

            case 0xB0: s[pos] = static_cast<S::value_type>(0x67); break; // ° -> g
            case 0xB1: // ± -> +/-
                s[pos] = static_cast<S::value_type>(0x2B);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2D));
                break;
            case 0xB2: // ² -> ^2
                s[pos] = static_cast<S::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x32));
                break;
            case 0xB3: // ³ -> ^3
                s[pos] = static_cast<S::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x33));
                break;
            case 0xB4: s[pos] = static_cast<S::value_type>(0x27); break; // ´ -> '
            case 0xB5: s[pos] = static_cast<S::value_type>(0x75); break; // µ -> u
            case 0xB6: s[pos] = static_cast<S::value_type>(0x39); break; // ¶ -> 9
            case 0xB7: s[pos] = static_cast<S::value_type>(0x2A); break; // · -> *
            case 0xB8: s[pos] = static_cast<S::value_type>(0x2E); break; // ¸ -> .
            case 0xB9: // ¹ -> ^1
                s[pos] = static_cast<S::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x31));
                break;
            case 0xBA: // º -> ^0
                s[pos] = static_cast<S::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x30));
                break;
            case 0xBB: // » -> >>
                s[pos] = static_cast<S::value_type>(0x3E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x3E));
                break;
            case 0xBC: // ¼ -> 1/4
                s[pos] = static_cast<S::value_type>(0x31);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x34));
                break;
            case 0xBD: // ½ -> 1/2
                s[pos] = static_cast<S::value_type>(0x31);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x32));
                break;
            case 0xBE: // ¾ -> 3/4
                s[pos] = static_cast<S::value_type>(0x33);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x34));
                break;
            case 0xBF: s[pos] = static_cast<S::value_type>(0x3F); break; // ¿ -> ?

            case 0xC0: s[pos] = static_cast<S::value_type>(0x41); break; // À -> A
            case 0xC1: s[pos] = static_cast<S::value_type>(0x41); break; // Á -> A
            case 0xC2: s[pos] = static_cast<S::value_type>(0x41); break; // Â -> A
            case 0xC3: s[pos] = static_cast<S::value_type>(0x41); break; // Ã -> A
            case 0xC4: s[pos] = static_cast<S::value_type>(0x41); break; // Ä -> A
            case 0xC5: s[pos] = static_cast<S::value_type>(0x41); break; // Å -> A
            case 0xC6: // Æ -> AE
                s[pos] = static_cast<S::value_type>(0x41);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x45));
                break;
            case 0xC7: s[pos] = static_cast<S::value_type>(0x43); break; // Ç -> C
            case 0xC8: s[pos] = static_cast<S::value_type>(0x45); break; // È -> E
            case 0xC9: s[pos] = static_cast<S::value_type>(0x45); break; // É -> E
            case 0xCA: s[pos] = static_cast<S::value_type>(0x45); break; // Ê -> E
            case 0xCB: s[pos] = static_cast<S::value_type>(0x45); break; // Ë -> E
            case 0xCC: s[pos] = static_cast<S::value_type>(0x49); break; // Ì -> I
            case 0xCD: s[pos] = static_cast<S::value_type>(0x49); break; // Í -> I
            case 0xCE: s[pos] = static_cast<S::value_type>(0x49); break; // Î -> I
            case 0xCF: s[pos] = static_cast<S::value_type>(0x49); break; // Ï -> I

            case 0xD0: s[pos] = static_cast<S::value_type>(0x44); break; // Ð -> D
            case 0xD1: s[pos] = static_cast<S::value_type>(0x4E); break; // Ñ -> N
            case 0xD2: s[pos] = static_cast<S::value_type>(0x4F); break; // Ò -> O
            case 0xD3: s[pos] = static_cast<S::value_type>(0x4F); break; // Ó -> O
            case 0xD4: s[pos] = static_cast<S::value_type>(0x4F); break; // Ô -> O
            case 0xD5: s[pos] = static_cast<S::value_type>(0x4F); break; // Õ -> O
            case 0xD6: s[pos] = static_cast<S::value_type>(0x4F); break; // Ö -> O
            case 0xD7: s[pos] = static_cast<S::value_type>(0x78); break; // × -> x
            case 0xD8: s[pos] = static_cast<S::value_type>(0x4F); break; // Ø -> O
            case 0xD9: s[pos] = static_cast<S::value_type>(0x55); break; // Ù -> U
            case 0xDA: s[pos] = static_cast<S::value_type>(0x55); break; // Ú -> U
            case 0xDB: s[pos] = static_cast<S::value_type>(0x55); break; // Û -> U
            case 0xDC: s[pos] = static_cast<S::value_type>(0x55); break; // Ü -> U
            case 0xDD: s[pos] = static_cast<S::value_type>(0x59); break; // Ý -> Y
            case 0xDE: s[pos] = static_cast<S::value_type>(0x50); break; // Þ -> P
            case 0xDF: s[pos] = static_cast<S::value_type>(0x42); break; // ß -> B

            case 0xE0: s[pos] = static_cast<S::value_type>(0x61); break; // à -> a
            case 0xE1: s[pos] = static_cast<S::value_type>(0x61); break; // á -> a
            case 0xE2: s[pos] = static_cast<S::value_type>(0x61); break; // â -> a
            case 0xE3: s[pos] = static_cast<S::value_type>(0x61); break; // ã -> a
            case 0xE4: s[pos] = static_cast<S::value_type>(0x61); break; // ä -> a
            case 0xE5: s[pos] = static_cast<S::value_type>(0x61); break; // å -> a
            case 0xE6: s[pos] = // æ -> ae
                s[pos] = static_cast<S::value_type>(0x61);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x65));
                break;
            case 0xE7: s[pos] = static_cast<S::value_type>(0x63); break; // ç -> c
            case 0xE8: s[pos] = static_cast<S::value_type>(0x65); break; // è -> e
            case 0xE9: s[pos] = static_cast<S::value_type>(0x65); break; // é -> e
            case 0xEA: s[pos] = static_cast<S::value_type>(0x65); break; // ê -> e
            case 0xEB: s[pos] = static_cast<S::value_type>(0x65); break; // ë -> e
            case 0xEC: s[pos] = static_cast<S::value_type>(0x69); break; // ì -> i
            case 0xED: s[pos] = static_cast<S::value_type>(0x69); break; // í -> i
            case 0xEE: s[pos] = static_cast<S::value_type>(0x69); break; // î -> i
            case 0xEF: s[pos] = static_cast<S::value_type>(0x69); break; // ï -> i

            case 0xF0: s[pos] = static_cast<S::value_type>(0x6F); break; // ð -> o
            case 0xF1: s[pos] = static_cast<S::value_type>(0x6E); break; // ñ -> n
            case 0xF2: s[pos] = static_cast<S::value_type>(0x6F); break; // ò -> o
            case 0xF3: s[pos] = static_cast<S::value_type>(0x6F); break; // ó -> o
            case 0xF4: s[pos] = static_cast<S::value_type>(0x6F); break; // ô -> o
            case 0xF5: s[pos] = static_cast<S::value_type>(0x6F); break; // õ -> o
            case 0xF6: s[pos] = static_cast<S::value_type>(0x6F); break; // ö -> o
            case 0xF7: s[pos] = static_cast<S::value_type>(0x2F); break; // ÷ -> /
            case 0xF8: s[pos] = static_cast<S::value_type>(0x6F); break; // ø -> o
            case 0xF9: s[pos] = static_cast<S::value_type>(0x75); break; // ù -> u
            case 0xFA: s[pos] = static_cast<S::value_type>(0x75); break; // ú -> u
            case 0xFB: s[pos] = static_cast<S::value_type>(0x75); break; // û -> u
            case 0xFC: s[pos] = static_cast<S::value_type>(0x75); break; // ü -> u
            case 0xFD: s[pos] = static_cast<S::value_type>(0x79); break; // ý -> y
            case 0xFE: s[pos] = static_cast<S::value_type>(0x70); break; // þ -> p
            case 0xFF: s[pos] = static_cast<S::value_type>(0x79); break; // ÿ -> y
            }
            if (increment)
            {
                ++it;
                ++pos;
            }
        }
    }
    return s;
}

template<class S>
inline S reduce_iso_8859_1_to_7_bit_ascii_copy(const S& s, const bool strict = true)
{
    S a = s;
    reduce_iso_8859_1_to_7_bit_ascii(a, strict);
    return a;
}

template<class S>
inline S& reduce_windows_1252_to_7_bit_ascii(S& s, const bool strict = true);

template<>
inline u8string& reduce_windows_1252_to_7_bit_ascii(u8string& s, const bool strict)
{
    if (strict)
    {
        return reduce_to_7_bit_ascii(s);
    }
    u8string::size_type pos = 0;
    u8string::iterator it = s.begin();
    while (it != s.end())
    {
        const unsigned char c = static_cast<unsigned char>(*it);
        if ((c < 0x20) || (c == 0x7F))
        {
            ++it;
            ++pos;
        }
        else
        {
            bool increment = true;
            switch (c)
            {
            case 0x80: s[pos] = static_cast<u8string::value_type>(0x43); break; // € -> C
            case 0x81: it = s.erase(it); break;
            case 0x82: s[pos] = static_cast<u8string::value_type>(0x27); break; // ‚ -> '
            case 0x83: s[pos] = static_cast<u8string::value_type>(0x66); break; // ƒ -> f
            case 0x84: s[pos] = static_cast<u8string::value_type>(0x22); break; // „ -> "
            case 0x85: // … -> ...
                s[pos] = static_cast<u8string::value_type>(0x2E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2E));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2E));
                break;
            case 0x86: s[pos] = static_cast<u8string::value_type>(0x2B); break; // † -> +
            case 0x87: s[pos] = static_cast<u8string::value_type>(0x2B); break; // ‡ -> +
            case 0x88: s[pos] = static_cast<u8string::value_type>(0x5E); break; // ˆ -> ^
            case 0x89: // ‰ -> o/oo
                s[pos] = static_cast<u8string::value_type>(0x6F);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x6F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x6F));
                break;
            case 0x8A: s[pos] = static_cast<u8string::value_type>(0x53); break; // Š -> S
            case 0x8B: s[pos] = static_cast<u8string::value_type>(0x3C); break; // ‹ -> <
            case 0x8C: s[pos] = static_cast<u8string::value_type>(0x45); break; // Œ -> E
            case 0x8D: it = s.erase(it); break;
            case 0x8E: s[pos] = static_cast<u8string::value_type>(0x5A); break; // Ž -> Z
            case 0x8F: it = s.erase(it); break;

            case 0x90: it = s.erase(it); break;
            case 0x91: s[pos] = static_cast<u8string::value_type>(0x27); break; // ‘ -> '
            case 0x92: s[pos] = static_cast<u8string::value_type>(0x27); break; // ’ -> '
            case 0x93: s[pos] = static_cast<u8string::value_type>(0x22); break; // “ -> "
            case 0x94: s[pos] = static_cast<u8string::value_type>(0x22); break; // ” -> "
            case 0x95: s[pos] = static_cast<u8string::value_type>(0x2A); break; // • -> *
            case 0x96: s[pos] = static_cast<u8string::value_type>(0x2D); break; // – -> -
            case 0x97: s[pos] = static_cast<u8string::value_type>(0x2D); break; // — -> -
            case 0x98: s[pos] = static_cast<u8string::value_type>(0x7E); break; // ˜ -> ~
            case 0x99: // ™ -> (TM)
                s[pos] = static_cast<u8string::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x54));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x4D));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x29));
                break;
            case 0x9A: s[pos] = static_cast<u8string::value_type>(0x73); break; // š -> s
            case 0x9B: s[pos] = static_cast<u8string::value_type>(0x3E); break; // › -> >
            case 0x9C: s[pos] = static_cast<u8string::value_type>(0x65); break; // œ -> e
            case 0x9D: it = s.erase(it); break;
            case 0x9E: s[pos] = static_cast<u8string::value_type>(0x7A); break; // ž -> z
            case 0x9F: s[pos] = static_cast<u8string::value_type>(0x59); break; // Ÿ -> Y

            case 0xA0: s[pos] = static_cast<u8string::value_type>(0x20); break; // NBSP -> SP
            case 0xA1: s[pos] = static_cast<u8string::value_type>(0x21); break; // ¡ -> !
            case 0xA2: s[pos] = static_cast<u8string::value_type>(0x63); break; // ¢ -> c
            case 0xA3: s[pos] = static_cast<u8string::value_type>(0x50); break; // £ -> P
            case 0xA4: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ¤ -> o
            case 0xA5: s[pos] = static_cast<u8string::value_type>(0x59); break; // ¥ -> Y
            case 0xA6: s[pos] = static_cast<u8string::value_type>(0x7C); break; // ¦ -> |
            case 0xA7: s[pos] = static_cast<u8string::value_type>(0x70); break; // § -> p
            case 0xA8: s[pos] = static_cast<u8string::value_type>(0x22); break; // ¨ -> "
            case 0xA9: // © -> (c)
                s[pos] = static_cast<u8string::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x63));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x29));
                break;
            case 0xAA: s[pos] = static_cast<u8string::value_type>(0x61); break; // ª -> a
            case 0xAB: // « -> <<
                s[pos] = static_cast<u8string::value_type>(0x3C);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x3C));
                break;
            case 0xAC: s[pos] = static_cast<u8string::value_type>(0x2D); break; // ¬ -> -
            case 0xAD: // SHY -> erase
                it = s.erase(it);
                increment = false;
                break;
            case 0xAE: // ® -> (R)
                s[pos] = static_cast<u8string::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x52));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x29));
                break;
            case 0xAF: s[pos] = static_cast<u8string::value_type>(0x2D); break; // ¯ -> -

            case 0xB0: s[pos] = static_cast<u8string::value_type>(0x67); break; // ° -> g
            case 0xB1: // ± -> +/-
                s[pos] = static_cast<u8string::value_type>(0x2B);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2D));
                break;
            case 0xB2: // ² -> ^2
                s[pos] = static_cast<u8string::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x32));
                break;
            case 0xB3: // ³ -> ^3
                s[pos] = static_cast<u8string::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x33));
                break;
            case 0xB4: s[pos] = static_cast<u8string::value_type>(0x27); break; // ´ -> '
            case 0xB5: s[pos] = static_cast<u8string::value_type>(0x75); break; // µ -> u
            case 0xB6: s[pos] = static_cast<u8string::value_type>(0x39); break; // ¶ -> 9
            case 0xB7: s[pos] = static_cast<u8string::value_type>(0x2A); break; // · -> *
            case 0xB8: s[pos] = static_cast<u8string::value_type>(0x2E); break; // ¸ -> .
            case 0xB9: // ¹ -> ^1
                s[pos] = static_cast<u8string::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x31));
                break;
            case 0xBA: // º -> ^0
                s[pos] = static_cast<u8string::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x30));
                break;
            case 0xBB: // » -> >>
                s[pos] = static_cast<u8string::value_type>(0x3E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x3E));
                break;
            case 0xBC: // ¼ -> 1/4
                s[pos] = static_cast<u8string::value_type>(0x31);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x34));
                break;
            case 0xBD: // ½ -> 1/2
                s[pos] = static_cast<u8string::value_type>(0x31);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x32));
                break;
            case 0xBE: // ¾ -> 3/4
                s[pos] = static_cast<u8string::value_type>(0x33);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x34));
                break;
            case 0xBF: s[pos] = static_cast<u8string::value_type>(0x3F); break; // ¿ -> ?

            case 0xC0: s[pos] = static_cast<u8string::value_type>(0x41); break; // À -> A
            case 0xC1: s[pos] = static_cast<u8string::value_type>(0x41); break; // Á -> A
            case 0xC2: s[pos] = static_cast<u8string::value_type>(0x41); break; // Â -> A
            case 0xC3: s[pos] = static_cast<u8string::value_type>(0x41); break; // Ã -> A
            case 0xC4: s[pos] = static_cast<u8string::value_type>(0x41); break; // Ä -> A
            case 0xC5: s[pos] = static_cast<u8string::value_type>(0x41); break; // Å -> A
            case 0xC6: // Æ -> AE
                s[pos] = static_cast<u8string::value_type>(0x41);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x45));
                break;
            case 0xC7: s[pos] = static_cast<u8string::value_type>(0x43); break; // Ç -> C
            case 0xC8: s[pos] = static_cast<u8string::value_type>(0x45); break; // È -> E
            case 0xC9: s[pos] = static_cast<u8string::value_type>(0x45); break; // É -> E
            case 0xCA: s[pos] = static_cast<u8string::value_type>(0x45); break; // Ê -> E
            case 0xCB: s[pos] = static_cast<u8string::value_type>(0x45); break; // Ë -> E
            case 0xCC: s[pos] = static_cast<u8string::value_type>(0x49); break; // Ì -> I
            case 0xCD: s[pos] = static_cast<u8string::value_type>(0x49); break; // Í -> I
            case 0xCE: s[pos] = static_cast<u8string::value_type>(0x49); break; // Î -> I
            case 0xCF: s[pos] = static_cast<u8string::value_type>(0x49); break; // Ï -> I

            case 0xD0: s[pos] = static_cast<u8string::value_type>(0x44); break; // Ð -> D
            case 0xD1: s[pos] = static_cast<u8string::value_type>(0x4E); break; // Ñ -> N
            case 0xD2: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ò -> O
            case 0xD3: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ó -> O
            case 0xD4: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ô -> O
            case 0xD5: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Õ -> O
            case 0xD6: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ö -> O
            case 0xD7: s[pos] = static_cast<u8string::value_type>(0x78); break; // × -> x
            case 0xD8: s[pos] = static_cast<u8string::value_type>(0x4F); break; // Ø -> O
            case 0xD9: s[pos] = static_cast<u8string::value_type>(0x55); break; // Ù -> U
            case 0xDA: s[pos] = static_cast<u8string::value_type>(0x55); break; // Ú -> U
            case 0xDB: s[pos] = static_cast<u8string::value_type>(0x55); break; // Û -> U
            case 0xDC: s[pos] = static_cast<u8string::value_type>(0x55); break; // Ü -> U
            case 0xDD: s[pos] = static_cast<u8string::value_type>(0x59); break; // Ý -> Y
            case 0xDE: s[pos] = static_cast<u8string::value_type>(0x50); break; // Þ -> P
            case 0xDF: s[pos] = static_cast<u8string::value_type>(0x42); break; // ß -> B

            case 0xE0: s[pos] = static_cast<u8string::value_type>(0x61); break; // à -> a
            case 0xE1: s[pos] = static_cast<u8string::value_type>(0x61); break; // á -> a
            case 0xE2: s[pos] = static_cast<u8string::value_type>(0x61); break; // â -> a
            case 0xE3: s[pos] = static_cast<u8string::value_type>(0x61); break; // ã -> a
            case 0xE4: s[pos] = static_cast<u8string::value_type>(0x61); break; // ä -> a
            case 0xE5: s[pos] = static_cast<u8string::value_type>(0x61); break; // å -> a
            case 0xE6: s[pos] = // æ -> ae
                s[pos] = static_cast<u8string::value_type>(0x61);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<u8string::value_type>(0x65));
                break;
            case 0xE7: s[pos] = static_cast<u8string::value_type>(0x63); break; // ç -> c
            case 0xE8: s[pos] = static_cast<u8string::value_type>(0x65); break; // è -> e
            case 0xE9: s[pos] = static_cast<u8string::value_type>(0x65); break; // é -> e
            case 0xEA: s[pos] = static_cast<u8string::value_type>(0x65); break; // ê -> e
            case 0xEB: s[pos] = static_cast<u8string::value_type>(0x65); break; // ë -> e
            case 0xEC: s[pos] = static_cast<u8string::value_type>(0x69); break; // ì -> i
            case 0xED: s[pos] = static_cast<u8string::value_type>(0x69); break; // í -> i
            case 0xEE: s[pos] = static_cast<u8string::value_type>(0x69); break; // î -> i
            case 0xEF: s[pos] = static_cast<u8string::value_type>(0x69); break; // ï -> i

            case 0xF0: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ð -> o
            case 0xF1: s[pos] = static_cast<u8string::value_type>(0x6E); break; // ñ -> n
            case 0xF2: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ò -> o
            case 0xF3: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ó -> o
            case 0xF4: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ô -> o
            case 0xF5: s[pos] = static_cast<u8string::value_type>(0x6F); break; // õ -> o
            case 0xF6: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ö -> o
            case 0xF7: s[pos] = static_cast<u8string::value_type>(0x2F); break; // ÷ -> /
            case 0xF8: s[pos] = static_cast<u8string::value_type>(0x6F); break; // ø -> o
            case 0xF9: s[pos] = static_cast<u8string::value_type>(0x75); break; // ù -> u
            case 0xFA: s[pos] = static_cast<u8string::value_type>(0x75); break; // ú -> u
            case 0xFB: s[pos] = static_cast<u8string::value_type>(0x75); break; // û -> u
            case 0xFC: s[pos] = static_cast<u8string::value_type>(0x75); break; // ü -> u
            case 0xFD: s[pos] = static_cast<u8string::value_type>(0x79); break; // ý -> y
            case 0xFE: s[pos] = static_cast<u8string::value_type>(0x70); break; // þ -> p
            case 0xFF: s[pos] = static_cast<u8string::value_type>(0x79); break; // ÿ -> y
            }
            if (increment)
            {
                ++it;
                ++pos;
            }
        }
    }
    return s;
}

template<class S>
inline S& reduce_windows_1252_to_7_bit_ascii(S& s, const bool strict)
{
    if (strict)
    {
        return reduce_to_7_bit_ascii(s);
    }
    S::size_type pos = 0;
    S::iterator it = s.begin();
    while (it != s.end())
    {
        const unsigned char c = static_cast<unsigned char>(*it);
        if ((c < 0x20) || (c == 0x7F))
        {
            ++it;
            ++pos;
        }
        else
        {
            bool increment = true;
            switch (c)
            {
            case 0x80: s[pos] = static_cast<S::value_type>(0x43); break; // € -> C
            case 0x81: it = s.erase(it); break;
            case 0x82: s[pos] = static_cast<S::value_type>(0x27); break; // ‚ -> '
            case 0x83: s[pos] = static_cast<S::value_type>(0x66); break; // ƒ -> f
            case 0x84: s[pos] = static_cast<S::value_type>(0x22); break; // „ -> "
            case 0x85: // … -> ...
                s[pos] = static_cast<S::value_type>(0x2E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2E));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2E));
                break;
            case 0x86: s[pos] = static_cast<S::value_type>(0x2B); break; // † -> +
            case 0x87: s[pos] = static_cast<S::value_type>(0x2B); break; // ‡ -> +
            case 0x88: s[pos] = static_cast<S::value_type>(0x5E); break; // ˆ -> ^
            case 0x89: // ‰ -> o/oo
                s[pos] = static_cast<S::value_type>(0x6F);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x6F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x6F));
                break;
            case 0x8A: s[pos] = static_cast<S::value_type>(0x53); break; // Š -> S
            case 0x8B: s[pos] = static_cast<S::value_type>(0x3C); break; // ‹ -> <
            case 0x8C: s[pos] = static_cast<S::value_type>(0x45); break; // Œ -> E
            case 0x8D: it = s.erase(it); break;
            case 0x8E: s[pos] = static_cast<S::value_type>(0x5A); break; // Ž -> Z
            case 0x8F: it = s.erase(it); break;

            case 0x90: it = s.erase(it); break;
            case 0x91: s[pos] = static_cast<S::value_type>(0x27); break; // ‘ -> '
            case 0x92: s[pos] = static_cast<S::value_type>(0x27); break; // ’ -> '
            case 0x93: s[pos] = static_cast<S::value_type>(0x22); break; // “ -> "
            case 0x94: s[pos] = static_cast<S::value_type>(0x22); break; // ” -> "
            case 0x95: s[pos] = static_cast<S::value_type>(0x2A); break; // • -> *
            case 0x96: s[pos] = static_cast<S::value_type>(0x2D); break; // – -> -
            case 0x97: s[pos] = static_cast<S::value_type>(0x2D); break; // — -> -
            case 0x98: s[pos] = static_cast<S::value_type>(0x7E); break; // ˜ -> ~
            case 0x99: // ™ -> (TM)
                s[pos] = static_cast<S::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x54));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x4D));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x29));
                break;
            case 0x9A: s[pos] = static_cast<S::value_type>(0x73); break; // š -> s
            case 0x9B: s[pos] = static_cast<S::value_type>(0x3E); break; // › -> >
            case 0x9C: s[pos] = static_cast<S::value_type>(0x65); break; // œ -> e
            case 0x9D: it = s.erase(it); break;
            case 0x9E: s[pos] = static_cast<S::value_type>(0x7A); break; // ž -> z
            case 0x9F: s[pos] = static_cast<S::value_type>(0x59); break; // Ÿ -> Y

            case 0xA0: s[pos] = static_cast<S::value_type>(0x20); break; // NBSP -> SP
            case 0xA1: s[pos] = static_cast<S::value_type>(0x21); break; // ¡ -> !
            case 0xA2: s[pos] = static_cast<S::value_type>(0x63); break; // ¢ -> c
            case 0xA3: s[pos] = static_cast<S::value_type>(0x50); break; // £ -> P
            case 0xA4: s[pos] = static_cast<S::value_type>(0x6F); break; // ¤ -> o
            case 0xA5: s[pos] = static_cast<S::value_type>(0x59); break; // ¥ -> Y
            case 0xA6: s[pos] = static_cast<S::value_type>(0x7C); break; // ¦ -> |
            case 0xA7: s[pos] = static_cast<S::value_type>(0x70); break; // § -> p
            case 0xA8: s[pos] = static_cast<S::value_type>(0x22); break; // ¨ -> "
            case 0xA9: // © -> (c)
                s[pos] = static_cast<S::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x63));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x29));
                break;
            case 0xAA: s[pos] = static_cast<S::value_type>(0x61); break; // ª -> a
            case 0xAB: // « -> <<
                s[pos] = static_cast<S::value_type>(0x3C);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x3C));
                break;
            case 0xAC: s[pos] = static_cast<S::value_type>(0x2D); break; // ¬ -> -
            case 0xAD: // SHY -> erase
                it = s.erase(it);
                increment = false;
                break;
            case 0xAE: // ® -> (R)
                s[pos] = static_cast<S::value_type>(0x28);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x52));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x29));
                break;
            case 0xAF: s[pos] = static_cast<S::value_type>(0x2D); break; // ¯ -> -

            case 0xB0: s[pos] = static_cast<S::value_type>(0x67); break; // ° -> g
            case 0xB1: // ± -> +/-
                s[pos] = static_cast<S::value_type>(0x2B);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2D));
                break;
            case 0xB2: // ² -> ^2
                s[pos] = static_cast<S::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x32));
                break;
            case 0xB3: // ³ -> ^3
                s[pos] = static_cast<S::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x33));
                break;
            case 0xB4: s[pos] = static_cast<S::value_type>(0x27); break; // ´ -> '
            case 0xB5: s[pos] = static_cast<S::value_type>(0x75); break; // µ -> u
            case 0xB6: s[pos] = static_cast<S::value_type>(0x39); break; // ¶ -> 9
            case 0xB7: s[pos] = static_cast<S::value_type>(0x2A); break; // · -> *
            case 0xB8: s[pos] = static_cast<S::value_type>(0x2E); break; // ¸ -> .
            case 0xB9: // ¹ -> ^1
                s[pos] = static_cast<S::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x31));
                break;
            case 0xBA: // º -> ^0
                s[pos] = static_cast<S::value_type>(0x5E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x30));
                break;
            case 0xBB: // » -> >>
                s[pos] = static_cast<S::value_type>(0x3E);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x3E));
                break;
            case 0xBC: // ¼ -> 1/4
                s[pos] = static_cast<S::value_type>(0x31);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x34));
                break;
            case 0xBD: // ½ -> 1/2
                s[pos] = static_cast<S::value_type>(0x31);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x32));
                break;
            case 0xBE: // ¾ -> 3/4
                s[pos] = static_cast<S::value_type>(0x33);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x2F));
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x34));
                break;
            case 0xBF: s[pos] = static_cast<S::value_type>(0x3F); break; // ¿ -> ?

            case 0xC0: s[pos] = static_cast<S::value_type>(0x41); break; // À -> A
            case 0xC1: s[pos] = static_cast<S::value_type>(0x41); break; // Á -> A
            case 0xC2: s[pos] = static_cast<S::value_type>(0x41); break; // Â -> A
            case 0xC3: s[pos] = static_cast<S::value_type>(0x41); break; // Ã -> A
            case 0xC4: s[pos] = static_cast<S::value_type>(0x41); break; // Ä -> A
            case 0xC5: s[pos] = static_cast<S::value_type>(0x41); break; // Å -> A
            case 0xC6: // Æ -> AE
                s[pos] = static_cast<S::value_type>(0x41);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x45));
                break;
            case 0xC7: s[pos] = static_cast<S::value_type>(0x43); break; // Ç -> C
            case 0xC8: s[pos] = static_cast<S::value_type>(0x45); break; // È -> E
            case 0xC9: s[pos] = static_cast<S::value_type>(0x45); break; // É -> E
            case 0xCA: s[pos] = static_cast<S::value_type>(0x45); break; // Ê -> E
            case 0xCB: s[pos] = static_cast<S::value_type>(0x45); break; // Ë -> E
            case 0xCC: s[pos] = static_cast<S::value_type>(0x49); break; // Ì -> I
            case 0xCD: s[pos] = static_cast<S::value_type>(0x49); break; // Í -> I
            case 0xCE: s[pos] = static_cast<S::value_type>(0x49); break; // Î -> I
            case 0xCF: s[pos] = static_cast<S::value_type>(0x49); break; // Ï -> I

            case 0xD0: s[pos] = static_cast<S::value_type>(0x44); break; // Ð -> D
            case 0xD1: s[pos] = static_cast<S::value_type>(0x4E); break; // Ñ -> N
            case 0xD2: s[pos] = static_cast<S::value_type>(0x4F); break; // Ò -> O
            case 0xD3: s[pos] = static_cast<S::value_type>(0x4F); break; // Ó -> O
            case 0xD4: s[pos] = static_cast<S::value_type>(0x4F); break; // Ô -> O
            case 0xD5: s[pos] = static_cast<S::value_type>(0x4F); break; // Õ -> O
            case 0xD6: s[pos] = static_cast<S::value_type>(0x4F); break; // Ö -> O
            case 0xD7: s[pos] = static_cast<S::value_type>(0x78); break; // × -> x
            case 0xD8: s[pos] = static_cast<S::value_type>(0x4F); break; // Ø -> O
            case 0xD9: s[pos] = static_cast<S::value_type>(0x55); break; // Ù -> U
            case 0xDA: s[pos] = static_cast<S::value_type>(0x55); break; // Ú -> U
            case 0xDB: s[pos] = static_cast<S::value_type>(0x55); break; // Û -> U
            case 0xDC: s[pos] = static_cast<S::value_type>(0x55); break; // Ü -> U
            case 0xDD: s[pos] = static_cast<S::value_type>(0x59); break; // Ý -> Y
            case 0xDE: s[pos] = static_cast<S::value_type>(0x50); break; // Þ -> P
            case 0xDF: s[pos] = static_cast<S::value_type>(0x42); break; // ß -> B

            case 0xE0: s[pos] = static_cast<S::value_type>(0x61); break; // à -> a
            case 0xE1: s[pos] = static_cast<S::value_type>(0x61); break; // á -> a
            case 0xE2: s[pos] = static_cast<S::value_type>(0x61); break; // â -> a
            case 0xE3: s[pos] = static_cast<S::value_type>(0x61); break; // ã -> a
            case 0xE4: s[pos] = static_cast<S::value_type>(0x61); break; // ä -> a
            case 0xE5: s[pos] = static_cast<S::value_type>(0x61); break; // å -> a
            case 0xE6: s[pos] = // æ -> ae
                s[pos] = static_cast<S::value_type>(0x61);
                ++it;
                ++pos;
                it = s.insert(it, static_cast<S::value_type>(0x65));
                break;
            case 0xE7: s[pos] = static_cast<S::value_type>(0x63); break; // ç -> c
            case 0xE8: s[pos] = static_cast<S::value_type>(0x65); break; // è -> e
            case 0xE9: s[pos] = static_cast<S::value_type>(0x65); break; // é -> e
            case 0xEA: s[pos] = static_cast<S::value_type>(0x65); break; // ê -> e
            case 0xEB: s[pos] = static_cast<S::value_type>(0x65); break; // ë -> e
            case 0xEC: s[pos] = static_cast<S::value_type>(0x69); break; // ì -> i
            case 0xED: s[pos] = static_cast<S::value_type>(0x69); break; // í -> i
            case 0xEE: s[pos] = static_cast<S::value_type>(0x69); break; // î -> i
            case 0xEF: s[pos] = static_cast<S::value_type>(0x69); break; // ï -> i

            case 0xF0: s[pos] = static_cast<S::value_type>(0x6F); break; // ð -> o
            case 0xF1: s[pos] = static_cast<S::value_type>(0x6E); break; // ñ -> n
            case 0xF2: s[pos] = static_cast<S::value_type>(0x6F); break; // ò -> o
            case 0xF3: s[pos] = static_cast<S::value_type>(0x6F); break; // ó -> o
            case 0xF4: s[pos] = static_cast<S::value_type>(0x6F); break; // ô -> o
            case 0xF5: s[pos] = static_cast<S::value_type>(0x6F); break; // õ -> o
            case 0xF6: s[pos] = static_cast<S::value_type>(0x6F); break; // ö -> o
            case 0xF7: s[pos] = static_cast<S::value_type>(0x2F); break; // ÷ -> /
            case 0xF8: s[pos] = static_cast<S::value_type>(0x6F); break; // ø -> o
            case 0xF9: s[pos] = static_cast<S::value_type>(0x75); break; // ù -> u
            case 0xFA: s[pos] = static_cast<S::value_type>(0x75); break; // ú -> u
            case 0xFB: s[pos] = static_cast<S::value_type>(0x75); break; // û -> u
            case 0xFC: s[pos] = static_cast<S::value_type>(0x75); break; // ü -> u
            case 0xFD: s[pos] = static_cast<S::value_type>(0x79); break; // ý -> y
            case 0xFE: s[pos] = static_cast<S::value_type>(0x70); break; // þ -> p
            case 0xFF: s[pos] = static_cast<S::value_type>(0x79); break; // ÿ -> y
            }
            if (increment)
            {
                ++it;
                ++pos;
            }
        }
    }
    return s;
}

template<class S>
inline S reduce_windows_1252_to_7_bit_ascii_copy(const S& s, const bool strict = true)
{
    S a = s;
    reduce_windows_1252_to_7_bit_ascii(a, strict);
    return a;
}

}
}
}

#endif  // #ifndef GO_UTILITY_STRING_ASCII_HPP_INCLUDED
