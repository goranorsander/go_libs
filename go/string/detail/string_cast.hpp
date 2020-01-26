#ifndef GO_STRING_DETAIL_STRING_CAST_HPP_INCLUDED
#define GO_STRING_DETAIL_STRING_CAST_HPP_INCLUDED

//
//  string_cast.hpp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11_CODECVT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/string/detail/string_convert.hpp>
#include <go/string/string_cast_exception.hpp>
#include <typeinfo>

namespace go
{
namespace string
{
namespace detail
{

template <typename to_string, typename from_string>
struct string_cast;

#define GO_IMPLEMENT_STRING_CAST_STRUCT(_to_string_type_, _from_string_type_, _convert_function_) \
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

#define GO_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(_string_type_) \
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

GO_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(std::string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::string, std::wstring, ::go::string::convert_wstring_to_string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::string, u2string, ::go::string::convert_u2string_to_string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::string, u8string, ::go::string::convert_u8string_to_string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::string, std::u16string, ::go::string::convert_u16string_to_string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::string, std::u32string, ::go::string::convert_u32string_to_string)

// to std::wstring

GO_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(std::wstring)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, std::string, ::go::string::convert_string_to_wstring)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, u2string, ::go::string::convert_u2string_to_wstring)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, u8string, ::go::string::convert_u8string_to_wstring)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, std::u16string, ::go::string::convert_u16string_to_wstring)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::wstring, std::u32string, ::go::string::convert_u32string_to_wstring)

// to go::string::u2string

GO_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(u2string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u2string, std::string, ::go::string::convert_string_to_u2string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u2string, std::wstring, ::go::string::convert_wstring_to_u2string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u2string, u8string, ::go::string::convert_u8string_to_u2string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u2string, std::u16string, ::go::string::convert_u16string_to_u2string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u2string, std::u32string, ::go::string::convert_u32string_to_u2string)

// to go::string::u8string

GO_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(u8string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u8string, std::string, ::go::string::convert_string_to_u8string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u8string, std::wstring, ::go::string::convert_wstring_to_u8string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u8string, u2string, ::go::string::convert_u2string_to_u8string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u8string, std::u16string, ::go::string::convert_u16string_to_u8string)
GO_IMPLEMENT_STRING_CAST_STRUCT(u8string, std::u32string, ::go::string::convert_u32string_to_u8string)

// to std::u16string

GO_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(std::u16string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u16string, std::string, ::go::string::convert_string_to_u16string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u16string, std::wstring, ::go::string::convert_wstring_to_u16string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u16string, u2string, ::go::string::convert_u2string_to_u16string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u16string, u8string, ::go::string::convert_u8string_to_u16string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u16string, std::u32string, ::go::string::convert_u32string_to_u16string)

// to std::u32string

GO_IMPLEMENT_STRING_CAST_STRUCT_NO_CONVERSION(std::u32string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u32string, std::string, ::go::string::convert_string_to_u32string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u32string, std::wstring, ::go::string::convert_wstring_to_u32string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u32string, u2string, ::go::string::convert_u2string_to_u32string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u32string, u8string, ::go::string::convert_u8string_to_u32string)
GO_IMPLEMENT_STRING_CAST_STRUCT(std::u32string, std::u16string, ::go::string::convert_u16string_to_u32string)

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

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_STRING_DETAIL_STRING_CAST_HPP_INCLUDED
