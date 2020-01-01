#ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CAST_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_DETAIL_STRING_CAST_HPP_INCLUDED

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

#include <go_boost/utility/string_cast_exception.hpp>
#include <go_boost/utility/string/detail/string_convert.hpp>
#include <typeinfo>

namespace go_boost
{
namespace utility
{
namespace string
{
namespace detail
{

template <typename to_string, typename from_string>
struct string_cast;

#define GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(_to_string_type_, _from_string_type_, _convert_function_) \
template <> \
struct string_cast<_to_string_type_, _from_string_type_> \
{ \
    typedef _from_string_type_ from_string_type; \
    typedef _to_string_type_ to_string_type; \
 \
    static to_string_type cast(const from_string_type& from) \
    { \
        return _convert_function_()(from); \
    } \
};

#define GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(_string_type_) \
template <> \
struct string_cast<_string_type_, _string_type_> \
{ \
    typedef _string_type_ from_string_type; \
    typedef _string_type_ to_string_type; \
 \
    static to_string_type cast(const from_string_type& from) \
    { \
        return from; \
    } \
};

// to std::string

GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(std::string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::string, std::wstring, string::convert_wstring_to_string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::string, u2string, string::convert_u2string_to_string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::string, u8string, string::convert_u8string_to_string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::string, u16string, string::convert_u16string_to_string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::string, u32string, string::convert_u32string_to_string)

// to std::wstring

GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(std::wstring)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, std::string, string::convert_string_to_wstring)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, u2string, string::convert_u2string_to_wstring)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, u8string, string::convert_u8string_to_wstring)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, u16string, string::convert_u16string_to_wstring)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, u32string, string::convert_u32string_to_wstring)

// to go_boost::utility::u2string

GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(u2string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u2string, std::string, string::convert_string_to_u2string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u2string, std::wstring, string::convert_wstring_to_u2string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u2string, u8string, string::convert_u8string_to_u2string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u2string, u16string, string::convert_u16string_to_u2string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u2string, u32string, string::convert_u32string_to_u2string)

// to go_boost::utility::u8string

GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(u8string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u8string, std::string, string::convert_string_to_u8string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u8string, std::wstring, string::convert_wstring_to_u8string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u8string, u2string, string::convert_u2string_to_u8string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u8string, u16string, string::convert_u16string_to_u8string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u8string, u32string, string::convert_u32string_to_u8string)

// to u16string

GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(u16string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u16string, std::string, string::convert_string_to_u16string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u16string, std::wstring, string::convert_wstring_to_u16string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u16string, u2string, string::convert_u2string_to_u16string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u16string, u8string, string::convert_u8string_to_u16string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u16string, u32string, string::convert_u32string_to_u16string)

// to u32string

GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(u32string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u32string, std::string, string::convert_string_to_u32string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u32string, std::wstring, string::convert_wstring_to_u32string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u32string, u2string, string::convert_u2string_to_u32string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u32string, u8string, string::convert_u8string_to_u32string)
GO_BOOST_IMPLEMENT_STRING_CAST_STRUCT(u32string, u16string, string::convert_u16string_to_u32string)

// fallback, unsupported string classes exception

template <typename to_string, typename from_string>
struct string_cast
{
    static to_string cast(const from_string&)
    {
        const std::string message = std::string("Cannot cast from ") + std::string(typeid(from_string).name()) + std::string(" to ") + std::string(typeid(to_string).name());
        throw string_cast_exception(message);
    }
};

}
}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_DETAIL_STRING_CAST_HPP_INCLUDED
