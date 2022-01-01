#ifndef GO_DIAGNOSTICS_LOG_DETAIL_DECODE_HPP_INCLUDED
#define GO_DIAGNOSTICS_LOG_DETAIL_DECODE_HPP_INCLUDED

//
//  decode.hpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/diagnostics/log/detail/string_literal.hpp>
#include <go/string/string_cast.hpp>

#include <iostream> 
#include <string>

namespace go
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <typename C, class O, typename Arg>
C* decode(O& os, C* b, Arg* a);

// Arg is string_literal_t<char_type>*

template <>
inline std::string::value_type* decode(std::ostream& os, std::string::value_type* b, string_literal_t<std::string::value_type>* /*a*/)
{
    string_literal_t<std::string::value_type> s = *reinterpret_cast<string_literal_t<std::string::value_type>*>(b);
    os << s._s;
    return reinterpret_cast<std::string::value_type*>(reinterpret_cast<std::size_t>(b) + sizeof(string_literal_t<std::string::value_type>));
}

template <>
inline std::string::value_type* decode(std::ostream& os, std::string::value_type* b, string_literal_t<std::wstring::value_type>* /*a*/)
{
    string_literal_t<std::wstring::value_type> s = *reinterpret_cast<string_literal_t<std::wstring::value_type>*>(b);
    const std::string mbs = go::string::string_cast<std::string>(std::wstring(s._s));
    os << mbs.c_str();
    return reinterpret_cast<std::string::value_type*>(reinterpret_cast<std::size_t>(b) + sizeof(string_literal_t<std::string::value_type>));
}

template <>
inline std::wstring::value_type* decode(std::wostream& os, std::wstring::value_type* b, string_literal_t<std::wstring::value_type>* /*a*/)
{
    string_literal_t<std::wstring::value_type> s = *reinterpret_cast<string_literal_t<std::wstring::value_type>*>(b);
    os << s._s;
    return reinterpret_cast<std::wstring::value_type*>(reinterpret_cast<std::size_t>(b) + sizeof(string_literal_t<std::wstring::value_type>));
}

template <>
inline std::wstring::value_type* decode(std::wostream& os, std::wstring::value_type* b, string_literal_t<std::string::value_type>* /*a*/)
{
    string_literal_t<std::string::value_type> s = *reinterpret_cast<string_literal_t<std::string::value_type>*>(b);
    const std::wstring sws = go::string::string_cast<std::wstring>(std::string(s._s));
    os << sws.c_str();
    return reinterpret_cast<std::wstring::value_type*>(reinterpret_cast<std::size_t>(b) + sizeof(string_literal_t<std::wstring::value_type>));
}

// Arg is char_type*

template <>
inline std::string::value_type* decode(std::ostream& os, std::string::value_type* b, std::string::value_type* /*a*/)
{
    while (*b != '\0')
    {
        os << *b;
        ++b;
    }
    return ++b;
}

template <>
inline std::string::value_type* decode(std::ostream& os, std::string::value_type* b, std::wstring::value_type* /*a*/)
{
    string_literal_t<std::wstring::value_type> s = *reinterpret_cast<string_literal_t<std::wstring::value_type>*>(b);
    const std::string mbs = go::string::string_cast<std::string>(std::wstring(s._s));
    for (const std::string::value_type c : mbs)
    {
        if (c == '\0')
        {
            break;
        }
        os << c;
        ++b;
    }
    return ++b;
}

template <>
inline std::wstring::value_type* decode(std::wostream& os, std::wstring::value_type* b, std::wstring::value_type* /*a*/)
{
    while (*b != L'\0')
    {
        os << *b;
        ++b;
    }
    return ++b;
}

template <>
inline std::wstring::value_type* decode(std::wostream& os, std::wstring::value_type* b, std::string::value_type* /*a*/)
{
    string_literal_t<std::string::value_type> s = *reinterpret_cast<string_literal_t<std::string::value_type>*>(b);
    const std::wstring sws = go::string::string_cast<std::wstring>(std::string(s._s));
    for (const std::wstring::value_type c : sws)
    {
        if (c == L'\0')
        {
            break;
        }
        os << c;
        ++b;
    }
    return ++b;
}

// Arg is char_type**

template <>
inline std::string::value_type* decode(std::ostream& os, std::string::value_type* b, std::string::value_type** /*a*/)
{
    while (*b != '\0')
    {
        os << *b;
        ++b;
    }
    return ++b;
}

template <>
inline std::string::value_type* decode(std::ostream& os, std::string::value_type* b, std::wstring::value_type** /*a*/)
{
    string_literal_t<std::wstring::value_type> s = *reinterpret_cast<string_literal_t<std::wstring::value_type>*>(b);
    const std::string mbs = go::string::string_cast<std::string>(std::wstring(s._s));
    for (const std::string::value_type c : mbs)
    {
        if (c == '\0')
        {
            break;
        }
        os << c;
        ++b;
    }
    return ++b;
}

template <>
inline std::wstring::value_type* decode(std::wostream & os, std::wstring::value_type* b, std::wstring::value_type** /*a*/)
{
    while (*b != L'\0')
    {
        os << *b;
        ++b;
    }
    return ++b;
}

template <>
inline std::wstring::value_type* decode(std::wostream & os, std::wstring::value_type* b, std::string::value_type** /*a*/)
{
    string_literal_t<std::string::value_type> s = *reinterpret_cast<string_literal_t<std::string::value_type>*>(b);
    const std::wstring sws = go::string::string_cast<std::wstring>(std::string(s._s));
    for (const std::wstring::value_type c : sws)
    {
        if (c == L'\0')
        {
            break;
        }
        os << c;
        ++b;
    }
    return ++b;
}

// Final fallback

template <typename C, class O, typename Arg>
inline C* decode(O& os, C* b, Arg* /*a*/)
{
    Arg arg = *reinterpret_cast<Arg*>(b);
    os << arg;
    return b + sizeof(Arg);
}

} // namespace detail
} // namespace log
} // namespace diagnostics
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_DIAGNOSTICS_LOG_DETAIL_DECODE_HPP_INCLUDED
