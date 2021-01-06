#ifndef GO_STRING_CREATE_HPP_INCLUDED
#define GO_STRING_CREATE_HPP_INCLUDED

//
//  create.hpp
//
//  Copyright 2018-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11_CODECVT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/string/create_exception.hpp>
#include <go/string/string_cast.hpp>
#include <go/string/u2string.hpp>
#include <go/string/u8string.hpp>

namespace go
{
namespace string
{

template<class to_string, typename from_char_t>
to_string create(const from_char_t* sz);

#define GO_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(_to_string_type_) \
template <> \
inline _to_string_type_ create(const _to_string_type_::value_type* sz) \
{ \
    if (sz != NULL) \
    { \
        return _to_string_type_(sz); \
    } \
    return _to_string_type_(); \
}

#define GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(_to_string_type_, _from_string_type_) \
template<> \
inline _to_string_type_ create(const _from_string_type_::value_type* sz) \
{ \
    if (sz != NULL) \
    { \
        const _from_string_type_ s(sz); \
        return string_cast<_to_string_type_>(s); \
    } \
    return _to_string_type_(); \
}

// std::string

GO_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(std::string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, std::wstring)
#if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, u2string)
#endif  // #if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, u8string)
#if !defined(GO_NO_CXX11_CHAR16_T)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, std::u16string)
#endif  // #if !defined(GO_NO_CXX11_CHAR16_T)
#if !defined(GO_NO_CXX11_CHAR32_T)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, std::u32string)
#endif  // #if !defined(GO_NO_CXX11_CHAR32_T)

// std::wstring

GO_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(std::wstring)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, std::string)
#if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, u2string)
#endif  // #if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, u8string)
#if !defined(GO_NO_CXX11_CHAR16_T)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, std::u16string)
#endif  // #if !defined(GO_NO_CXX11_CHAR16_T)
#if !defined(GO_NO_CXX11_CHAR32_T)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, std::u32string)
#endif  // #if !defined(GO_NO_CXX11_CHAR32_T)

// go::string::u2string

#if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(u2string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, std::string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, std::wstring)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, u8string)
#if !defined(GO_NO_CXX11_CHAR16_T)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, std::u16string)
#endif  // #if !defined(GO_NO_CXX11_CHAR16_T)
#if !defined(GO_NO_CXX11_CHAR32_T)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, std::u32string)
#endif  // #if !defined(GO_NO_CXX11_CHAR32_T)
#endif  // #if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)

// go::string::u8string

GO_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(u8string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, std::string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, std::wstring)
#if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, u2string)
#endif  // #if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
#if !defined(GO_NO_CXX11_CHAR16_T)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, std::u16string)
#endif  // #if !defined(GO_NO_CXX11_CHAR16_T)
#if !defined(GO_NO_CXX11_CHAR32_T)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, std::u32string)
#endif  // #if !defined(GO_NO_CXX11_CHAR32_T)

// std::u16string

#if !defined(GO_NO_CXX11_CHAR16_T)
GO_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(std::u16string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u16string, std::string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u16string, std::wstring)
#if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u16string, u2string)
#endif  // #if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u16string, u8string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u16string, std::u32string)
#endif  // #if !defined(GO_NO_CXX11_CHAR16_T)

// std::u32string

#if !defined(GO_NO_CXX11_CHAR32_T)
GO_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(std::u32string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u32string, std::string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u32string, std::wstring)
#if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u32string, u2string)
#endif  // #if !defined(GO_CANNOT_CREATE_U2STRING_ISSUE)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u32string, u8string)
GO_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::u32string, std::u16string)
#endif  // #if !defined(GO_NO_CXX11_CHAR32_T)

template<class to_string, typename from_char_t>
inline to_string create(const from_char_t* /*sz*/)
{
    const std::string message = std::string("Cannot create ") + std::string(typeid(to_string).name()) + std::string(" from ") + std::string(typeid(from_char_t).name());
    throw create_exception(message);
}

}
}

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_STRING_CREATE_HPP_INCLUDED
