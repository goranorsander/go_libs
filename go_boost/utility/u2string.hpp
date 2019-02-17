#ifndef GO_BOOST_UTILITY_U2STRING_HPP_INCLUDED
#define GO_BOOST_UTILITY_U2STRING_HPP_INCLUDED

//
//  u2string.hpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/utility/string/algorithm_fwd.hpp>
#include <string>

namespace go_boost
{
namespace utility
{

typedef boost::uint16_t char2_t;

class u2string
    : public std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>
{
public:
    typedef u2string this_type;
    typedef std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>> base_type;
    typedef std::char_traits<char2_t> traits_type;
    typedef std::allocator<char2_t> allocator_type;

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
    virtual ~u2string() GO_BOOST_DEFAULT_DESTRUCTOR

    u2string();

    explicit u2string(const allocator_type& alloc);

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

    u2string(size_type count, value_type ch, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1900))

    u2string(const u2string& other, size_type pos, size_type count = this_type::npos, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1900))

#if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (GO_BOOST_GCC_VER > 50300)) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1900))

    u2string(const u2string& other, size_type pos, const allocator_type& alloc = allocator_type());

#endif  // #if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (GO_BOOST_GCC_VER > 50300)) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1900))

    u2string(const value_type* s, size_type count, const allocator_type& alloc = allocator_type());

    u2string(const value_type* s, const allocator_type& alloc = allocator_type());

    template<class InputIt>
    u2string(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());

    u2string(const u2string& other);

    u2string(const u2string& other, const allocator_type& alloc);

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    u2string(u2string&& other) BOOST_NOEXCEPT_OR_NOTHROW;

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

    u2string(u2string&& other, const allocator_type& alloc);

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    u2string(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type());

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    template<class T>
    u2string(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type());

public:
    u2string& operator=(const u2string& other);

    bool operator==(const u2string& other) const;

    bool operator!=(const u2string& other) const;
};

inline u2string::u2string()
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(allocator_type())
{
}

inline u2string::u2string(const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(alloc)
{
}

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

inline u2string::u2string(size_type count, value_type ch, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(count, ch, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1900))

inline u2string::u2string(const u2string& other, size_type pos, size_type count, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other, pos, count, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1900))

#if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (GO_BOOST_GCC_VER > 50300)) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1900))

inline u2string::u2string(const u2string& other, size_type pos, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other, pos, alloc)
{
}

#endif  // #if (!defined(BOOST_GCC) && !defined(BOOST_MSVC)) || (defined(BOOST_GCC) && (GO_BOOST_GCC_VER > 50300)) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1900))

inline u2string::u2string(const value_type* s, size_type count, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(s, count, alloc)
{
}

inline u2string::u2string(const value_type* s, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(s, alloc)
{
}

template<class InputIt>
inline u2string::u2string(InputIt first, InputIt last, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(first, last, alloc)
{
}

inline u2string::u2string(const u2string& other)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other)
{
}

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

inline u2string::u2string(const u2string& other, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

inline u2string::u2string(u2string&& other) BOOST_NOEXCEPT_OR_NOTHROW
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other)
{
}

#if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

inline u2string::u2string(u2string&& other, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other, alloc)
{
}

#endif  // #if !defined(BOOST_MSVC) || (defined(BOOST_MSVC) && (GO_BOOST_MSVC_MFC_VER > 1600))

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

inline u2string::u2string(std::initializer_list<value_type> init, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(init, alloc)
{
}

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

template<class T>
inline u2string::u2string(const T& t, size_type pos, size_type n, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(t, pos, n, alloc)
{
}

inline u2string& u2string::operator=(const u2string& other)
{
    if (&other != this)
    {
        std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>::operator=(other);
    }
    return *this;
}

inline bool u2string::operator==(const u2string& other) const
{
    if (&other != this)
    {
        return string::equals(*this, other);
    }
    return true;
}

inline bool u2string::operator!=(const u2string& other) const
{
    return !operator==(other);
}

}
}

#endif  // #ifndef GO_BOOST_UTILITY_U2STRING_HPP_INCLUDED
