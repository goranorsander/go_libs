#ifndef GO_BOOST_UTILITY_STRING_CREATE_HPP_INCLUDED
#define GO_BOOST_UTILITY_STRING_CREATE_HPP_INCLUDED

//
//  create.hpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/utility/string_cast.hpp>
#include <go_boost/utility/string/create_exception.hpp>

namespace go_boost
{
namespace utility
{
namespace string
{

template<class to_string, typename from_char_t>
inline to_string create(const from_char_t* sz);

#define GO_BOOST_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(_to_string_type_) \
template <> \
inline _to_string_type_ create(const _to_string_type_::value_type* sz) \
{ \
    if (sz != NULL) \
    { \
        return _to_string_type_(sz); \
    } \
    return _to_string_type_(); \
}

#define GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(_to_string_type_, _from_string_type_) \
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

GO_BOOST_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(std::string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, std::wstring)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, u2string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, u8string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, u16string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::string, u32string)

// std::wstring

GO_BOOST_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(std::wstring)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, std::string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, u2string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, u8string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, u16string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(std::wstring, u32string)

// go_boost::utility::u2string

GO_BOOST_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(u2string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, std::string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, std::wstring)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, u8string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, u16string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u2string, u32string)

// go_boost::utility::u8string

GO_BOOST_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(u8string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, std::string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, std::wstring)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, u2string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, u16string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u8string, u32string)

// go_boost::utility::u16string

GO_BOOST_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(u16string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u16string, std::string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u16string, std::wstring)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u16string, u2string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u16string, u8string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u16string, u32string)

// go_boost::utility::u32string

GO_BOOST_IMPLEMENT_STRING_CREATE_SAME_VALUE_TYPE(u32string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u32string, std::string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u32string, std::wstring)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u32string, u2string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u32string, u8string)
GO_BOOST_IMPLEMENT_STRING_CREATE_OTHER_VALUE_TYPE(u32string, u16string)

template<class to_string, typename from_char_t>
inline to_string create(const from_char_t* /*sz*/)
{
    const std::string message = std::string("Cannot assign as ") + std::string(typeid(from_string).name()) + std::string(" from ") + std::string(typeid(from_char_t).name());
    throw create_exception(message);
}

}
}
}

#endif  // #ifndef GO_BOOST_UTILITY_STRING_CREATE_HPP_INCLUDED
