#ifndef GO_BOOST_UTILITY_U32STRING_HPP_INCLUDED
#define GO_BOOST_UTILITY_U32STRING_HPP_INCLUDED

//
//  u32string.hpp
//
//  Copyright 2017-2021 Göran Orsander
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

#if defined(BOOST_NO_CXX11_CHAR32_T) && !(defined(GO_BOOST_COMP_MSVC_VC100) || defined(GO_BOOST_COMP_MSVC_VC110) || defined(GO_BOOST_COMP_MSVC_VC120))
typedef boost::uint32_t char32_t;
#endif  // #if defined(BOOST_NO_CXX11_CHAR32_T) && !(defined(GO_BOOST_COMP_MSVC_VC100) || defined(GO_BOOST_COMP_MSVC_VC110) || defined(GO_BOOST_COMP_MSVC_VC120))

namespace go_boost
{
namespace string
{

class u32string
    : public std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>
{
public:
    typedef u32string this_type;
    typedef std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>> base_type;
    typedef std::char_traits<char32_t> traits_type;
    typedef std::allocator<char32_t> allocator_type;

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
    virtual ~u32string() GO_BOOST_DEFAULT_DESTRUCTOR

    u32string();

    explicit u32string(const allocator_type& alloc);

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

    u32string(size_type count, value_type ch, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

    u32string(const u32string& other, size_type pos, size_type count = this_type::npos, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

#if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (BOOST_GCC > 50300)) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

    u32string(const u32string& other, size_type pos, const allocator_type& alloc = allocator_type());

#endif  // #if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (BOOST_GCC > 50300)) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

    u32string(const value_type* s, size_type count, const allocator_type& alloc = allocator_type());

    u32string(const value_type* s, const allocator_type& alloc = allocator_type());

    template<class InputIt>
    u32string(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());

    u32string(const u32string& other);

    u32string(const u32string& other, const allocator_type& alloc);

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    u32string(u32string&& other) BOOST_NOEXCEPT_OR_NOTHROW;

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

    u32string(u32string&& other, const allocator_type& alloc);

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    u32string(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    template<class T>
    u32string(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type());

public:
    u32string& operator=(const u32string& other) BOOST_NOEXCEPT_OR_NOTHROW;

    bool operator==(const u32string& other) const;

    bool operator!=(const u32string& other) const;
};

inline u32string::u32string()
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(allocator_type())
{
}

inline u32string::u32string(const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(alloc)
{
}

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

inline u32string::u32string(size_type count, value_type ch, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(count, ch, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

inline u32string::u32string(const u32string& other, size_type pos, size_type count, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(other, pos, count, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

#if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (BOOST_GCC > 50300)) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

inline u32string::u32string(const u32string& other, size_type pos, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(other, pos, alloc)
{
}

#endif  // #if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (BOOST_GCC > 50300)) || (defined(BOOST_MSVC) && (BOOST_MSVC > 1900))

inline u32string::u32string(const value_type* s, size_type count, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(s, count, alloc)
{
}

inline u32string::u32string(const value_type* s, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(s, alloc)
{
}

template<class InputIt>
inline u32string::u32string(InputIt first, InputIt last, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(first, last, alloc)
{
}

inline u32string::u32string(const u32string& other)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(other)
{
}

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

inline u32string::u32string(const u32string& other, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(other, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

inline u32string::u32string(u32string&& other) BOOST_NOEXCEPT_OR_NOTHROW
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(other)
{
}

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

inline u32string::u32string(u32string&& other, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(other, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (BOOST_MSVC > 3200))

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

inline u32string::u32string(std::initializer_list<value_type> init, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(init, alloc)
{
}

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

template<class T>
inline u32string::u32string(const T& t, size_type pos, size_type n, const allocator_type& alloc)
    : std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>(t, pos, n, alloc)
{
}

inline u32string& u32string::operator=(const u32string& other) BOOST_NOEXCEPT_OR_NOTHROW
{
    if (&other != this)
    {
        std::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>::operator=(other);
    }
    return *this;
}

inline bool u32string::operator==(const u32string& other) const
{
    if (&other != this)
    {
        return equals(*this, other);
    }
    return true;
}

inline bool u32string::operator!=(const u32string& other) const
{
    return !operator==(other);
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_U32STRING_HPP_INCLUDED
