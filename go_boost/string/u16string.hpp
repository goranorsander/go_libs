#ifndef GO_BOOST_UTILITY_U16STRING_HPP_INCLUDED
#define GO_BOOST_UTILITY_U16STRING_HPP_INCLUDED

//
//  u16string.hpp
//
//  Copyright 2017-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/string/equals.hpp>
#include <string>

#if defined(BOOST_NO_CXX11_CHAR16_T) && !(defined(GO_BOOST_COMP_MSVC_VC100) || defined(GO_BOOST_COMP_MSVC_VC110) || defined(GO_BOOST_COMP_MSVC_VC120))
typedef boost::uint16_t char16_t;
#endif  // #if defined(BOOST_NO_CXX11_CHAR16_T) && !(defined(GO_BOOST_COMP_MSVC_VC100) || defined(GO_BOOST_COMP_MSVC_VC110) || defined(GO_BOOST_COMP_MSVC_VC120))

namespace go_boost
{
namespace string
{

class u16string
    : public std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>
{
public:
    typedef u16string this_type;
    typedef std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>> base_type;
    typedef std::char_traits<char16_t> traits_type;
    typedef std::allocator<char16_t> allocator_type;

    typedef GO_BOOST_TYPENAME base_type::value_type value_type;
    typedef GO_BOOST_TYPENAME base_type::size_type size_type;
    typedef GO_BOOST_TYPENAME base_type::difference_type difference_type;
    typedef GO_BOOST_TYPENAME base_type::pointer pointer;
    typedef GO_BOOST_TYPENAME base_type::const_pointer const_pointer;
    typedef GO_BOOST_TYPENAME base_type::reference reference;
    typedef GO_BOOST_TYPENAME base_type::const_reference const_reference;

    typedef GO_BOOST_TYPENAME base_type::iterator iterator;
    typedef GO_BOOST_TYPENAME base_type::const_iterator const_iterator;

    typedef base_type::reverse_iterator reverse_iterator;
    typedef base_type::const_reverse_iterator const_reverse_iterator;

public:
    virtual ~u16string() GO_BOOST_DEFAULT_DESTRUCTOR

    u16string();

    explicit u16string(const allocator_type& alloc);

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

    u16string(size_type count, value_type ch, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

    u16string(const u16string& other, size_type pos, size_type count = this_type::npos, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

#if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (BOOST_GCC > 50300)) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

    u16string(const u16string& other, size_type pos, const allocator_type& alloc = allocator_type());

#endif  // #if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (BOOST_GCC > 50300)) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

    u16string(const value_type* s, size_type count, const allocator_type& alloc = allocator_type());

    explicit u16string(const value_type* s, const allocator_type& alloc = allocator_type());

    template<class InputIt>
    u16string(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());

    u16string(const u16string& other);

    u16string(const u16string& other, const allocator_type& alloc);

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    u16string(u16string&& other) BOOST_NOEXCEPT_OR_NOTHROW;

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

    u16string(u16string&& other, const allocator_type& alloc);

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    explicit u16string(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    template<class T>
    u16string(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type());

public:
    u16string& operator=(const u16string& other) BOOST_NOEXCEPT_OR_NOTHROW;

    bool operator==(const u16string& other) const;

    bool operator!=(const u16string& other) const;
};

inline u16string::u16string()
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(allocator_type())
{
}

inline u16string::u16string(const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(alloc)
{
}

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

inline u16string::u16string(size_type count, value_type ch, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(count, ch, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

inline u16string::u16string(const u16string& other, size_type pos, size_type count, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(other, pos, count, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

#if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (BOOST_GCC > 50300)) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

inline u16string::u16string(const u16string& other, size_type pos, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(other, pos, alloc)
{
}

#endif  // #if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (BOOST_GCC > 50300)) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

inline u16string::u16string(const value_type* s, size_type count, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(s, count, alloc)
{
}

inline u16string::u16string(const value_type* s, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(s, alloc)
{
}

template<class InputIt>
inline u16string::u16string(InputIt first, InputIt last, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(first, last, alloc)
{
}

inline u16string::u16string(const u16string& other)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(other)
{
}

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

inline u16string::u16string(const u16string& other, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(other, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

inline u16string::u16string(u16string&& other) BOOST_NOEXCEPT_OR_NOTHROW
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(other)
{
}

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

inline u16string::u16string(u16string&& other, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(other, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1600))

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

inline u16string::u16string(std::initializer_list<value_type> init, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(init, alloc)
{
}

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

template<class T>
inline u16string::u16string(const T& t, size_type pos, size_type n, const allocator_type& alloc)
    : std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>(t, pos, n, alloc)
{
}

inline u16string& u16string::operator=(const u16string& other) BOOST_NOEXCEPT_OR_NOTHROW
{
    if (&other != this)
    {
        std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>::operator=(other);
    }
    return *this;
}

inline bool u16string::operator==(const u16string& other) const
{
    if (&other != this)
    {
        return equals(*this, other);
    }
    return true;
}

inline bool u16string::operator!=(const u16string& other) const
{
    return !operator==(other);
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_U16STRING_HPP_INCLUDED
