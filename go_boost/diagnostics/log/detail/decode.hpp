#ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DECODE_HPP_INCLUDED
#define GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DECODE_HPP_INCLUDED

//
//  decode.hpp
//
//  Copyright 2018-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/diagnostics/log/detail/string_literal.hpp>
#include <go_boost/string/string_cast.hpp>

#include <string>

namespace go_boost
{
namespace diagnostics
{
namespace log
{
namespace detail
{

template <typename C, class O, typename Arg>
C* decode(O& os, C* b, Arg* a);

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
    const std::string mbs = go_boost::string::string_cast<std::string>(std::wstring(s._s));
    os << mbs.c_str();
    return reinterpret_cast<std::string::value_type*>(reinterpret_cast<std::size_t>(b) + sizeof(string_literal_t<std::string::value_type>));
}

template <>
inline std::string::value_type* decode(std::ostream & os, std::string::value_type* b, std::string::value_type* /*a*/)
{
    while (*b != '\0')
    {
        os << *b;
        ++b;
    }
    return ++b;
}

template <>
inline std::string::value_type* decode(std::ostream & os, std::string::value_type* b, std::string::value_type** /*a*/)
{
    while (*b != '\0')
    {
        os << *b;
        ++b;
    }
    return ++b;
}

template <>
inline std::string::value_type* decode(std::ostream & os, std::string::value_type* b, std::wstring::value_type* /*a*/)
{
    string_literal_t<std::wstring::value_type> s = *reinterpret_cast<string_literal_t<std::wstring::value_type>*>(b);
    const std::string mbs = go_boost::string::string_cast<std::string>(std::wstring(s._s));
    const std::string::const_iterator end = mbs.end();
    for (std::string::const_iterator c = mbs.begin(); c != end; ++b, ++c)
    {
        if (*c == '\0')
        {
            break;
        }
        os << *c;
    }
    return ++b;
}

template <>
inline std::string::value_type* decode(std::ostream & os, std::string::value_type* b, std::wstring::value_type** /*a*/)
{
    string_literal_t<std::wstring::value_type> s = *reinterpret_cast<string_literal_t<std::wstring::value_type>*>(b);
    const std::string mbs = go_boost::string::string_cast<std::string>(std::wstring(s._s));
    const std::string::const_iterator end = mbs.end();
    for (std::string::const_iterator c = mbs.begin(); c != end; ++b, ++c)
    {
        if (*c == '\0')
        {
            break;
        }
        os << *c;
    }
    return ++b;
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
    const std::wstring sws = go_boost::string::string_cast<std::wstring>(std::string(s._s));
    os << sws.c_str();
    return reinterpret_cast<std::wstring::value_type*>(reinterpret_cast<std::size_t>(b) + sizeof(string_literal_t<std::wstring::value_type>));
}

template <>
inline std::wstring::value_type* decode(std::wostream & os, std::wstring::value_type* b, std::wstring::value_type* /*a*/)
{
    while (*b != L'\0')
    {
        os << *b;
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
inline std::wstring::value_type* decode(std::wostream & os, std::wstring::value_type* b, std::string::value_type* /*a*/)
{
    string_literal_t<std::string::value_type> s = *reinterpret_cast<string_literal_t<std::string::value_type>*>(b);
    const std::wstring sws = go_boost::string::string_cast<std::wstring>(std::string(s._s));
    const std::wstring::const_iterator end = sws.end();
    for (std::wstring::const_iterator c = sws.begin(); c != end; ++b, ++c)
    {
        if (*c == L'\0')
        {
            break;
        }
        os << *c;
    }
    return ++b;
}

template <>
inline std::wstring::value_type* decode(std::wostream & os, std::wstring::value_type* b, std::string::value_type** /*a*/)
{
    string_literal_t<std::string::value_type> s = *reinterpret_cast<string_literal_t<std::string::value_type>*>(b);
    const std::wstring sws = go_boost::string::string_cast<std::wstring>(std::string(s._s));
    const std::wstring::const_iterator end = sws.end();
    for (std::wstring::const_iterator c = sws.begin(); c != end; ++b, ++c)
    {
        if (*c == L'\0')
        {
            break;
        }
        os << *c;
    }
    return ++b;
}

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
} // namespace go_boost

#endif  // #ifndef GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DECODE_HPP_INCLUDED
