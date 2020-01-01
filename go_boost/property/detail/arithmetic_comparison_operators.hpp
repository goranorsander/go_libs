#ifndef GO_BOOST_PROPERTY_DETAIL_ARITHMETIC_COMPARISON_OPERATORS_HPP_INCLUDED
#define GO_BOOST_PROPERTY_DETAIL_ARITHMETIC_COMPARISON_OPERATORS_HPP_INCLUDED

//
//  arithmetic_comparison_operators.hpp
//
//  Copyright 2015-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/utility/placebo_lockable.hpp>
#include <go_boost/utility/u8string.hpp>
#include <go_boost/utility/u16string.hpp>
#include <go_boost/utility/u32string.hpp>

#define GO_BOOST_IMPLEMENT_PROPERTY_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
inline bool operator==(const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() == rhs; \
} \
inline bool operator==(const _value_type_& lhs, const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& rhs) \
{ \
    return lhs == rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_PROPERTY_NOT_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
inline bool operator!=(const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& lhs, const _value_type_& rhs) \
{ \
    return !operator==(lhs, rhs); \
} \
inline bool operator!=(const _value_type_& lhs, const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& rhs) \
{ \
    return !operator==(lhs, rhs); \
}

#define GO_BOOST_IMPLEMENT_PROPERTY_LESS_THAN_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
inline bool operator<(const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() < rhs; \
} \
inline bool operator<(const _value_type_& lhs, const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& rhs) \
{ \
    return lhs < rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_PROPERTY_GREATER_THAN_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
inline bool operator>(const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() > rhs; \
} \
inline bool operator>(const _value_type_& lhs, const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& rhs) \
{ \
    return lhs > rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_PROPERTY_LESS_THAN_OR_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
inline bool operator<=(const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() <= rhs; \
} \
inline bool operator<=(const _value_type_& lhs, const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& rhs) \
{ \
    return lhs <= rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_PROPERTY_GREATER_THAN_OR_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
inline bool operator>=(const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() >= rhs; \
} \
inline bool operator>=(const _value_type_& lhs, const _basic_property_type_<_value_type_, _property_name_type_, _mutex_type_>& rhs) \
{ \
    return lhs >= rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_COMPARISON_OPERATORS(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
GO_BOOST_IMPLEMENT_PROPERTY_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
GO_BOOST_IMPLEMENT_PROPERTY_NOT_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
GO_BOOST_IMPLEMENT_PROPERTY_LESS_THAN_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
GO_BOOST_IMPLEMENT_PROPERTY_GREATER_THAN_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
GO_BOOST_IMPLEMENT_PROPERTY_LESS_THAN_OR_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
GO_BOOST_IMPLEMENT_PROPERTY_GREATER_THAN_OR_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_)

#define GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
GO_BOOST_IMPLEMENT_PROPERTY_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_) \
GO_BOOST_IMPLEMENT_PROPERTY_NOT_EQUAL_TO_OPERATOR(_basic_property_type_, _property_name_type_, _value_type_, _mutex_type_)

#define GO_BOOST_IMPLEMENT_DEFAULT_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, std::string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, std::wstring, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, utility::u8string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, utility::u16string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, utility::u32string, boost::recursive_mutex) \
\
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, std::string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, std::wstring, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, utility::u8string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, utility::u16string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, utility::u32string, boost::recursive_mutex) \
\
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, std::string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, std::wstring, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, utility::u8string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, utility::u16string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, utility::u32string, boost::recursive_mutex) \
\
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, std::string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, std::wstring, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, utility::u8string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, utility::u16string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, utility::u32string, boost::recursive_mutex) \
\
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, std::string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, std::wstring, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, utility::u8string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, utility::u16string, boost::recursive_mutex) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, utility::u32string, boost::recursive_mutex) \
\
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, std::string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, std::wstring, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, utility::u8string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, utility::u16string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::string, utility::u32string, utility::placebo_lockable) \
\
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, std::string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, std::wstring, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, utility::u8string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, utility::u16string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, std::wstring, utility::u32string, utility::placebo_lockable) \
\
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, std::string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, std::wstring, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, utility::u8string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, utility::u16string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u8string, utility::u32string, utility::placebo_lockable) \
\
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, std::string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, std::wstring, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, utility::u8string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, utility::u16string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u16string, utility::u32string, utility::placebo_lockable) \
\
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, std::string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, std::wstring, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, utility::u8string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, utility::u16string, utility::placebo_lockable) \
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, utility::u32string, utility::u32string, utility::placebo_lockable)

#endif  // #ifndef GO_BOOST_PROPERTY_DETAIL_ARITHMETIC_COMPARISON_OPERATORS_HPP_INCLUDED
