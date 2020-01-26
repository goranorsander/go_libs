#ifndef GO_BOOST_STRING_STRING_CAST_HPP_INCLUDED
#define GO_BOOST_STRING_STRING_CAST_HPP_INCLUDED

//
//  string_cast.hpp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/bind.hpp>
#include <go_boost/string/detail/string_cast.hpp>

namespace go_boost
{
namespace string
{

// to std::string

inline convert_wstring_to_string_function_signature& convert_wstring_to_string()
{
    static convert_wstring_to_string_function_signature f = boost::bind(detail::convert_wstring_to_string, _1);
    return f;
}

inline convert_u2string_to_string_function_signature& convert_u2string_to_string()
{
    static convert_u2string_to_string_function_signature f = boost::bind(detail::convert_u2string_to_string, _1);
    return f;
}

inline convert_u8string_to_string_function_signature& convert_u8string_to_string()
{
    static convert_u8string_to_string_function_signature f = boost::bind(detail::convert_u8string_to_string, _1);
    return f;
}

inline convert_u16string_to_string_function_signature& convert_u16string_to_string()
{
    static convert_u16string_to_string_function_signature f = boost::bind(detail::convert_u16string_to_string, _1);
    return f;
}

inline convert_u32string_to_string_function_signature& convert_u32string_to_string()
{
    static convert_u32string_to_string_function_signature f = boost::bind(detail::convert_u32string_to_string, _1);
    return f;
}

// to std::wstring

inline convert_string_to_wstring_function_signature& convert_string_to_wstring()
{
    static convert_string_to_wstring_function_signature f = boost::bind(detail::convert_string_to_wstring, _1);
    return f;
}

inline convert_u2string_to_wstring_function_signature& convert_u2string_to_wstring()
{
    static convert_u2string_to_wstring_function_signature f = boost::bind(detail::convert_u2string_to_wstring, _1);
    return f;
}

inline convert_u8string_to_wstring_function_signature& convert_u8string_to_wstring()
{
    static convert_u8string_to_wstring_function_signature f = boost::bind(detail::convert_u8string_to_wstring, _1);
    return f;
}

inline convert_u16string_to_wstring_function_signature& convert_u16string_to_wstring()
{
    static convert_u16string_to_wstring_function_signature f = boost::bind(detail::convert_u16string_to_wstring, _1);
    return f;
}

inline convert_u32string_to_wstring_function_signature& convert_u32string_to_wstring()
{
    static convert_u32string_to_wstring_function_signature f = boost::bind(detail::convert_u32string_to_wstring, _1);
    return f;
}

// to go_boost::string::u2string

inline convert_string_to_u2string_function_signature& convert_string_to_u2string()
{
    static convert_string_to_u2string_function_signature f = boost::bind(detail::convert_string_to_u2string, _1);
    return f;
}

inline convert_wstring_to_u2string_function_signature& convert_wstring_to_u2string()
{
    static convert_wstring_to_u2string_function_signature f = boost::bind(detail::convert_wstring_to_u2string, _1);
    return f;
}

inline convert_u8string_to_u2string_function_signature& convert_u8string_to_u2string()
{
    static convert_u8string_to_u2string_function_signature f = boost::bind(detail::convert_u8string_to_u2string, _1);
    return f;
}

inline convert_u16string_to_u2string_function_signature& convert_u16string_to_u2string()
{
    static convert_u16string_to_u2string_function_signature f = boost::bind(detail::convert_u16string_to_u2string, _1);
    return f;
}

inline convert_u32string_to_u2string_function_signature& convert_u32string_to_u2string()
{
    static convert_u32string_to_u2string_function_signature f = boost::bind(detail::convert_u32string_to_u2string, _1);
    return f;
}

// to go_boost::string::u8string

inline convert_string_to_u8string_function_signature& convert_string_to_u8string()
{
    static convert_string_to_u8string_function_signature f = boost::bind(detail::convert_string_to_u8string, _1);
    return f;
}

inline convert_wstring_to_u8string_function_signature& convert_wstring_to_u8string()
{
    static convert_wstring_to_u8string_function_signature f = boost::bind(detail::convert_wstring_to_u8string, _1);
    return f;
}

inline convert_u2string_to_u8string_function_signature& convert_u2string_to_u8string()
{
    static convert_u2string_to_u8string_function_signature f = boost::bind(detail::convert_u2string_to_u8string, _1);
    return f;
}

inline convert_u16string_to_u8string_function_signature& convert_u16string_to_u8string()
{
    static convert_u16string_to_u8string_function_signature f = boost::bind(detail::convert_u16string_to_u8string, _1);
    return f;
}

inline convert_u32string_to_u8string_function_signature& convert_u32string_to_u8string()
{
    static convert_u32string_to_u8string_function_signature f = boost::bind(detail::convert_u32string_to_u8string, _1);
    return f;
}

// to std::u16string

inline convert_string_to_u16string_function_signature& convert_string_to_u16string()
{
    static convert_string_to_u16string_function_signature f = boost::bind(detail::convert_string_to_u16string, _1);
    return f;
}

inline convert_wstring_to_u16string_function_signature& convert_wstring_to_u16string()
{
    static convert_wstring_to_u16string_function_signature f = boost::bind(detail::convert_wstring_to_u16string, _1);
    return f;
}

inline convert_u2string_to_u16string_function_signature& convert_u2string_to_u16string()
{
    static convert_u2string_to_u16string_function_signature f = boost::bind(detail::convert_u2string_to_u16string, _1);
    return f;
}

inline convert_u8string_to_u16string_function_signature& convert_u8string_to_u16string()
{
    static convert_u8string_to_u16string_function_signature f = boost::bind(detail::convert_u8string_to_u16string, _1);
    return f;
}

inline convert_u32string_to_u16string_function_signature& convert_u32string_to_u16string()
{
    static convert_u32string_to_u16string_function_signature f = boost::bind(detail::convert_u32string_to_u16string, _1);
    return f;
}

// to std::u32string

inline convert_string_to_u32string_function_signature& convert_string_to_u32string()
{
    static convert_string_to_u32string_function_signature f = boost::bind(detail::convert_string_to_u32string, _1);
    return f;
}

inline convert_wstring_to_u32string_function_signature& convert_wstring_to_u32string()
{
    static convert_wstring_to_u32string_function_signature f = boost::bind(detail::convert_wstring_to_u32string, _1);
    return f;
}

inline convert_u2string_to_u32string_function_signature& convert_u2string_to_u32string()
{
    static convert_u2string_to_u32string_function_signature f = boost::bind(detail::convert_u2string_to_u32string, _1);
    return f;
}

inline convert_u8string_to_u32string_function_signature& convert_u8string_to_u32string()
{
    static convert_u8string_to_u32string_function_signature f = boost::bind(detail::convert_u8string_to_u32string, _1);
    return f;
}

inline convert_u16string_to_u32string_function_signature& convert_u16string_to_u32string()
{
    static convert_u16string_to_u32string_function_signature f = boost::bind(detail::convert_u16string_to_u32string, _1);
    return f;
}

template <typename to_string, typename from_string>
GO_BOOST_CONSTEXPR to_string string_cast(const from_string& from)
{
    return detail::string_cast<to_string, from_string>::cast(from);
}

}
}

#endif  // #ifndef GO_BOOST_STRING_STRING_CAST_HPP_INCLUDED
