#ifndef GO_UTILITY_U2STRING_HPP_INCLUDED
#define GO_UTILITY_U2STRING_HPP_INCLUDED

//
//  u2string.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>
#include <string>

namespace go
{
namespace utility
{

typedef GO_TYPENAME unsigned short char2_t;

class u2string
    : public std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>
{
public:
    typedef typename u2string this_type;

public:
    virtual ~u2string();

    u2string();

    explicit u2string(const allocator_type& alloc);

    u2string(size_type count, value_type ch, const allocator_type& alloc = allocator_type());

    u2string(const u2string& other, size_type pos, size_type count = this_type::npos, const allocator_type& alloc = allocator_type());

    u2string(const u2string& other, size_type pos, const allocator_type& alloc = allocator_type());

    u2string(const value_type* s, size_type count, const allocator_type& alloc = allocator_type());

    u2string(const value_type* s, const allocator_type& alloc = allocator_type());

    template<class InputIt>
    u2string(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());

    u2string(const u2string& other);

    u2string(const u2string& other, const allocator_type& alloc);

    u2string(u2string&& other) noexcept;

    u2string(u2string&& other, const allocator_type& alloc);

    u2string(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type());

    template<class T>
    u2string(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type());

};

inline u2string::~u2string()
{
}

inline u2string::u2string()
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(allocator_type())
{
}

inline u2string::u2string(const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(alloc)
{
}

inline u2string::u2string(size_type count, value_type ch, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(count, ch, alloc)
{
}

inline u2string::u2string(const u2string& other, size_type pos, size_type count, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other, pos, count, alloc)
{
}

inline u2string::u2string(const u2string& other, size_type pos, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other, pos, alloc)
{
}

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

inline u2string::u2string(const u2string& other, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other, alloc)
{
}

inline u2string::u2string(u2string&& other) noexcept
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other)
{
}

inline u2string::u2string(u2string&& other, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(other, alloc)
{
}

inline u2string::u2string(std::initializer_list<value_type> init, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(init, alloc)
{
}

template<class T>
inline u2string::u2string(const T& t, size_type pos, size_type n, const allocator_type& alloc)
    : std::basic_string<char2_t, std::char_traits<char2_t>, std::allocator<char2_t>>(t, pos, n, alloc)
{
}

}
}

#endif  // #ifndef GO_UTILITY_U2STRING_HPP_INCLUDED
