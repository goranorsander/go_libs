#ifndef GO_UTILITY_U8STRING_HPP_INCLUDED
#define GO_UTILITY_U8STRING_HPP_INCLUDED

//
//  u8string.hpp
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

typedef GO_TYPENAME unsigned char char8_t;

class u8string
    : public std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>
{
public:
    typedef typename u8string this_type;

public:
    virtual ~u8string();

    u8string();

    explicit u8string(const allocator_type& alloc);

    u8string(size_type count, value_type ch, const allocator_type& alloc = allocator_type());

    u8string(const u8string& other, size_type pos, size_type count = this_type::npos, const allocator_type& alloc = allocator_type());

    u8string(const u8string& other, size_type pos, const allocator_type& alloc = allocator_type());

    u8string(const value_type* s, size_type count, const allocator_type& alloc = allocator_type());

    u8string(const value_type* s, const allocator_type& alloc = allocator_type());

    template<class InputIt>
    u8string(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());

    u8string(const u8string& other);

    u8string(const u8string& other, const allocator_type& alloc);

    u8string(u8string&& other) noexcept;

    u8string(u8string&& other, const allocator_type& alloc);

    u8string(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type());

    template<class T>
    u8string(const T& t, size_type pos, size_type n, const allocator_type& alloc = allocator_type());

};

inline u8string::~u8string()
{
}

inline u8string::u8string()
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(allocator_type())
{
}

inline u8string::u8string(const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(alloc)
{
}

inline u8string::u8string(size_type count, value_type ch, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(count, ch, alloc)
{
}

inline u8string::u8string(const u8string& other, size_type pos, size_type count, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other, pos, count, alloc)
{
}

inline u8string::u8string(const u8string& other, size_type pos, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other, pos, alloc)
{
}

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

inline u8string::u8string(const u8string& other, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other, alloc)
{
}

inline u8string::u8string(u8string&& other) noexcept
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other)
{
}

inline u8string::u8string(u8string&& other, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(other, alloc)
{
}

inline u8string::u8string(std::initializer_list<value_type> init, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(init, alloc)
{
}

template<class T>
inline u8string::u8string(const T& t, size_type pos, size_type n, const allocator_type& alloc)
    : std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>(t, pos, n, alloc)
{
}

}
}

#endif  // #ifndef GO_UTILITY_U8STRING_HPP_INCLUDED
