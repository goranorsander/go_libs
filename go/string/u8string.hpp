#ifndef GO_UTILITY_U8STRING_HPP_INCLUDED
#define GO_UTILITY_U8STRING_HPP_INCLUDED

//
//  u8string.hpp
//
//  Copyright 2017-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <go/string/equals.hpp>
#include <algorithm>
#include <deque>
#include <map>
#include <string>

#if defined(GO_NO_CXX20_CHAR8_T)
GO_USING(char8_t, unsigned char);
#endif  // #if defined(GO_NO_CXX20_CHAR8_T)

namespace go
{
namespace string
{

GO_USING(uft8_character_type, std::deque<char8_t>);
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
typedef std::map<std::size_t, uft8_character_type> uft8_string_type;
#else
using uft8_string_type = std::map<std::size_t, uft8_character_type>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)

class u8string
    : public std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>
{
public:
    GO_USING(this_type, u8string);
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>> base_type;
#else
    using base_type = std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    GO_USING(traits_type, std::char_traits<char8_t>);
    GO_USING(allocator_type, std::allocator<char8_t>);

    GO_USING(value_type, GO_TYPENAME base_type::value_type);
    GO_USING(size_type, GO_TYPENAME base_type::size_type);
    GO_USING(difference_type, GO_TYPENAME base_type::difference_type);
    GO_USING(pointer, GO_TYPENAME base_type::pointer);
    GO_USING(const_pointer, GO_TYPENAME base_type::const_pointer);
    GO_USING(reference, GO_TYPENAME base_type::reference);
    GO_USING(const_reference, GO_TYPENAME base_type::const_reference);

    GO_USING(iterator, GO_TYPENAME base_type::iterator);
    GO_USING(const_iterator, GO_TYPENAME base_type::const_iterator);

    GO_USING(reverse_iterator, base_type::reverse_iterator);
    GO_USING(const_reverse_iterator, base_type::const_reverse_iterator);

public:
    virtual ~u8string() GO_DEFAULT_DESTRUCTOR

    u8string();

    explicit u8string(const allocator_type& alloc);

#if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

    u8string(size_type count, value_type ch, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

#if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1900))

    u8string(const u8string& other, size_type pos, size_type count = this_type::npos, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1900))

#if (!defined(GO_COMP_GCC) && !defined(GO_COMP_MSVC)) || (defined(GO_COMP_GCC) && (GO_GCC_VER > 50300)) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1900))

    u8string(const u8string& other, size_type pos, const allocator_type& alloc = allocator_type());

#endif  // #if (!defined(GO_COMP_GCC) && !defined(GO_COMP_MSVC)) || (defined(GO_COMP_GCC) && (GO_GCC_VER > 50300)) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1900))

    u8string(const value_type* s, size_type count, const allocator_type& alloc = allocator_type());

    explicit u8string(const value_type* s, const allocator_type& alloc = allocator_type());

    template<class InputIt>
    u8string(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());

    u8string(const u8string& other);

    u8string(const u8string& other, const allocator_type& alloc);

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

    u8string(u8string&& other) GO_NOEXCEPT_OR_NOTHROW;

#if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

    u8string(u8string&& other, const allocator_type& alloc);

#endif  // #if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

    explicit u8string(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

    template<class T>
    u8string(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type());

public:
    u8string& operator=(const u8string& other) GO_NOEXCEPT_OR_NOTHROW;

    bool operator==(const u8string& other) const;

    bool operator!=(const u8string& other) const;

    std::size_t characters() const;

    uft8_character_type character(const size_type pos) const;

    uft8_string_type string() const;
};

inline u8string::u8string()
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(allocator_type())
{
}

inline u8string::u8string(const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(alloc)
{
}

#if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

inline u8string::u8string(size_type count, value_type ch, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(count, ch, alloc)
{
}

#endif  // #if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

#if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1900))

inline u8string::u8string(const u8string& other, size_type pos, size_type count, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other, pos, count, alloc)
{
}

#endif  // #if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1900))

#if (!defined(GO_COMP_GCC) && !defined(GO_COMP_MSVC)) || (defined(GO_COMP_GCC) && (GO_GCC_VER > 50300)) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1900))

inline u8string::u8string(const u8string& other, size_type pos, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other, pos, alloc)
{
}

#endif  // #if (!defined(GO_COMP_GCC) && !defined(GO_COMP_MSVC)) || (defined(GO_COMP_GCC) && (GO_GCC_VER > 50300)) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1900))

inline u8string::u8string(const value_type* s, size_type count, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(s, count, alloc)
{
}

inline u8string::u8string(const value_type* s, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(s, alloc)
{
}

template<class InputIt>
inline u8string::u8string(InputIt first, InputIt last, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(first, last, alloc)
{
}

inline u8string::u8string(const u8string& other)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other)
{
}

#if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

inline u8string::u8string(const u8string& other, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other, alloc)
{
}

#endif  // #if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

#if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

inline u8string::u8string(u8string&& other) GO_NOEXCEPT_OR_NOTHROW
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other)
{
}

#if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

inline u8string::u8string(u8string&& other, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other, alloc)
{
}

#endif  // #if !defined(GO_COMP_MSVC) || (defined(GO_COMP_MSVC) && (GO_MSVC_VER > 1600))

#endif  // #if !defined(GO_NO_CXX11_RVALUE_REFERENCES)

#if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

inline u8string::u8string(std::initializer_list<value_type> init, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(init, alloc)
{
}

#endif  // #if !defined(GO_NO_CXX11_INITIALIZER_LISTS)

template<class T>
inline u8string::u8string(const T& t, size_type pos, size_type n, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(t, pos, n, alloc)
{
}

inline u8string& u8string::operator=(const u8string& other) GO_NOEXCEPT_OR_NOTHROW
{
    if (&other != this)
    {
        std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>::operator=(other);
    }
    return *this;
}

inline bool u8string::operator==(const u8string& other) const
{
    if (&other != this)
    {
        return equals(*this, other);
    }
    return true;
}

inline bool u8string::operator!=(const u8string& other) const
{
    return !operator==(other);
}

inline std::size_t u8string::characters() const
{
    std::size_t count = 0;
    const_iterator it = begin();
    const const_iterator endit = end();
    while (it != endit)
    {
        const unsigned char c = static_cast<unsigned char>(*it);
        if (c < 0x80)
        {
            ++count;
        }
        else if ((c >= 0xC2) && (c < 0xE0))
        {
            ++count;
            ++it;
        }
        else if ((c >= 0xE0) && (c < 0xF0))
        {
            ++count;
            std::advance(it, 2);
        }
        else if ((c >= 0xF0) && (c < 0xFC))
        {
            ++count;
            std::advance(it, 3);
        }
        else if ((c >= 0xFC) && (c < 0xFE))
        {
            ++count;
            std::advance(it, 4);
        }
        else if (c >= 0xFE)
        {
            ++count;
            std::advance(it, 5);
        }
        ++it;
    }
    return count;
}

inline uft8_character_type u8string::character(const size_type pos) const
{
    const uft8_string_type u8s = string();
    uft8_string_type::const_iterator it = u8s.find(pos);
    if (it != u8s.end())
    {
        return it->second;
    }
    return uft8_character_type();
}

inline uft8_string_type u8string::string() const
{
    uft8_string_type u8s;
    std::size_t count = 0;
    const_iterator it = begin();
    const const_iterator endit = end();
    while (it != endit)
    {
        uft8_character_type u8ch;
        const unsigned char c = static_cast<unsigned char>(*it);
        if (c < 0x80)
        {
            ++count;
        }
        else if ((c >= 0xC2) && (c < 0xE0))
        {
            ++count;
            u8ch.push_back(*it); ++it;
        }
        else if ((c >= 0xE0) && (c < 0xF0))
        {
            ++count;
            u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it;
        }
        else if ((c >= 0xF0) && (c < 0xFC))
        {
            ++count;
            u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it;
        }
        else if ((c >= 0xFC) && (c < 0xFE))
        {
            ++count;
            u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it;
        }
        else if (c >= 0xFE)
        {
            ++count;
            u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it; u8ch.push_back(*it); ++it;
        }
        u8ch.push_back(*it);
        ++it;
        u8s[count] = u8ch;
    }
    return u8s;
}

}
}

#endif  // #ifndef GO_UTILITY_U8STRING_HPP_INCLUDED
