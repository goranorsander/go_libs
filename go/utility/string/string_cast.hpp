#ifndef GO_UTILITY_STRING_STRING_CAST_HPP_INCLUDED
#define GO_UTILITY_STRING_STRING_CAST_HPP_INCLUDED

//
//  string_cast.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <functional>
#include <go/utility/string/detail/string_cast.hpp>

namespace go
{
namespace utility
{
namespace string
{

// to std::string

inline convert_wstring_to_string_function_signature& convert_wstring_to_string()
{
    static convert_wstring_to_string_function_signature f = std::bind(detail::convert_wstring_to_string, std::placeholders::_1);
    return f;
}

inline convert_u2string_to_string_function_signature& convert_u2string_to_string()
{
    static convert_u2string_to_string_function_signature f = std::bind(detail::convert_u2string_to_string, std::placeholders::_1);
    return f;
}

inline convert_u8string_to_string_function_signature& convert_u8string_to_string()
{
    static convert_u8string_to_string_function_signature f = std::bind(detail::convert_u8string_to_string, std::placeholders::_1);
    return f;
}

inline convert_u16string_to_string_function_signature& convert_u16string_to_string()
{
    static convert_u16string_to_string_function_signature f = std::bind(detail::convert_u16string_to_string, std::placeholders::_1);
    return f;
}

inline convert_u32string_to_string_function_signature& convert_u32string_to_string()
{
    static convert_u32string_to_string_function_signature f = std::bind(detail::convert_u32string_to_string, std::placeholders::_1);
    return f;
}

// to std::wstring

inline convert_string_to_wstring_function_signature& convert_string_to_wstring()
{
    static convert_string_to_wstring_function_signature f = std::bind(detail::convert_string_to_wstring, std::placeholders::_1);
    return f;
}

inline convert_u2string_to_wstring_function_signature& convert_u2string_to_wstring()
{
    static convert_u2string_to_wstring_function_signature f = std::bind(detail::convert_u2string_to_wstring, std::placeholders::_1);
    return f;
}

inline convert_u8string_to_wstring_function_signature& convert_u8string_to_wstring()
{
    static convert_u8string_to_wstring_function_signature f = std::bind(detail::convert_u8string_to_wstring, std::placeholders::_1);
    return f;
}

inline convert_u16string_to_wstring_function_signature& convert_u16string_to_wstring()
{
    static convert_u16string_to_wstring_function_signature f = std::bind(detail::convert_u16string_to_wstring, std::placeholders::_1);
    return f;
}

inline convert_u32string_to_wstring_function_signature& convert_u32string_to_wstring()
{
    static convert_u32string_to_wstring_function_signature f = std::bind(detail::convert_u32string_to_wstring, std::placeholders::_1);
    return f;
}

// to go::utility::u2string

inline convert_string_to_u2string_function_signature& convert_string_to_u2string()
{
    static convert_string_to_u2string_function_signature f = std::bind(detail::convert_string_to_u2string, std::placeholders::_1);
    return f;
}

inline convert_wstring_to_u2string_function_signature& convert_wstring_to_u2string()
{
    static convert_wstring_to_u2string_function_signature f = std::bind(detail::convert_wstring_to_u2string, std::placeholders::_1);
    return f;
}

inline convert_u8string_to_u2string_function_signature& convert_u8string_to_u2string()
{
    static convert_u8string_to_u2string_function_signature f = std::bind(detail::convert_u8string_to_u2string, std::placeholders::_1);
    return f;
}

inline convert_u16string_to_u2string_function_signature& convert_u16string_to_u2string()
{
    static convert_u16string_to_u2string_function_signature f = std::bind(detail::convert_u16string_to_u2string, std::placeholders::_1);
    return f;
}

inline convert_u32string_to_u2string_function_signature& convert_u32string_to_u2string()
{
    static convert_u32string_to_u2string_function_signature f = std::bind(detail::convert_u32string_to_u2string, std::placeholders::_1);
    return f;
}

// to go::utility::u8string

inline convert_string_to_u8string_function_signature& convert_string_to_u8string()
{
    static convert_string_to_u8string_function_signature f = std::bind(detail::convert_string_to_u8string, std::placeholders::_1);
    return f;
}

inline convert_wstring_to_u8string_function_signature& convert_wstring_to_u8string()
{
    static convert_wstring_to_u8string_function_signature f = std::bind(detail::convert_wstring_to_u8string, std::placeholders::_1);
    return f;
}

inline convert_u2string_to_u8string_function_signature& convert_u2string_to_u8string()
{
    static convert_u2string_to_u8string_function_signature f = std::bind(detail::convert_u2string_to_u8string, std::placeholders::_1);
    return f;
}

inline convert_u16string_to_u8string_function_signature& convert_u16string_to_u8string()
{
    static convert_u16string_to_u8string_function_signature f = std::bind(detail::convert_u16string_to_u8string, std::placeholders::_1);
    return f;
}

inline convert_u32string_to_u8string_function_signature& convert_u32string_to_u8string()
{
    static convert_u32string_to_u8string_function_signature f = std::bind(detail::convert_u32string_to_u8string, std::placeholders::_1);
    return f;
}

// to std::u16string

inline convert_string_to_u16string_function_signature& convert_string_to_u16string()
{
    static convert_string_to_u16string_function_signature f = std::bind(detail::convert_string_to_u16string, std::placeholders::_1);
    return f;
}

inline convert_wstring_to_u16string_function_signature& convert_wstring_to_u16string()
{
    static convert_wstring_to_u16string_function_signature f = std::bind(detail::convert_wstring_to_u16string, std::placeholders::_1);
    return f;
}

inline convert_u2string_to_u16string_function_signature& convert_u2string_to_u16string()
{
    static convert_u2string_to_u16string_function_signature f = std::bind(detail::convert_u2string_to_u16string, std::placeholders::_1);
    return f;
}

inline convert_u8string_to_u16string_function_signature& convert_u8string_to_u16string()
{
    static convert_u8string_to_u16string_function_signature f = std::bind(detail::convert_u8string_to_u16string, std::placeholders::_1);
    return f;
}

inline convert_u32string_to_u16string_function_signature& convert_u32string_to_u16string()
{
    static convert_u32string_to_u16string_function_signature f = std::bind(detail::convert_u32string_to_u16string, std::placeholders::_1);
    return f;
}

// to std::u32string

inline convert_string_to_u32string_function_signature& convert_string_to_u32string()
{
    static convert_string_to_u32string_function_signature f = std::bind(detail::convert_string_to_u32string, std::placeholders::_1);
    return f;
}

inline convert_wstring_to_u32string_function_signature& convert_wstring_to_u32string()
{
    static convert_wstring_to_u32string_function_signature f = std::bind(detail::convert_wstring_to_u32string, std::placeholders::_1);
    return f;
}

inline convert_u2string_to_u32string_function_signature& convert_u2string_to_u32string()
{
    static convert_u2string_to_u32string_function_signature f = std::bind(detail::convert_u2string_to_u32string, std::placeholders::_1);
    return f;
}

inline convert_u8string_to_u32string_function_signature& convert_u8string_to_u32string()
{
    static convert_u8string_to_u32string_function_signature f = std::bind(detail::convert_u8string_to_u32string, std::placeholders::_1);
    return f;
}

inline convert_u16string_to_u32string_function_signature& convert_u16string_to_u32string()
{
    static convert_u16string_to_u32string_function_signature f = std::bind(detail::convert_u16string_to_u32string, std::placeholders::_1);
    return f;
}

}
}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_UTILITY_STRING_STRING_CAST_HPP_INCLUDED
