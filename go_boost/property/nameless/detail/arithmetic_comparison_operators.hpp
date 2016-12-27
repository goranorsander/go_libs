#ifndef GO_BOOST_PROPERTY_NAMELESS_DETAIL_ARITHMETIC_COMPARISON_OPERATORS_HPP_INCLUDED
#define GO_BOOST_PROPERTY_NAMELESS_DETAIL_ARITHMETIC_COMPARISON_OPERATORS_HPP_INCLUDED

//
//  arithmetic_comparison_operators.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_) \
inline bool operator==(const _basic_property_type_<_value_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() == rhs; \
} \
inline bool operator==(const _value_type_& lhs, const _basic_property_type_<_value_type_>& rhs) \
{ \
    return lhs == rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_NOT_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_) \
inline bool operator!=(const _basic_property_type_<_value_type_>& lhs, const _value_type_& rhs) \
{ \
    return !operator==(lhs, rhs); \
} \
inline bool operator!=(const _value_type_& lhs, const _basic_property_type_<_value_type_>& rhs) \
{ \
    return !operator==(lhs, rhs); \
}

#define GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_LESS_THAN_OPERATOR(_basic_property_type_, _value_type_) \
inline bool operator<(const _basic_property_type_<_value_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() < rhs; \
} \
inline bool operator<(const _value_type_& lhs, const _basic_property_type_<_value_type_>& rhs) \
{ \
    return lhs < rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_GREATER_THAN_OPERATOR(_basic_property_type_, _value_type_) \
inline bool operator>(const _basic_property_type_<_value_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() > rhs; \
} \
inline bool operator>(const _value_type_& lhs, const _basic_property_type_<_value_type_>& rhs) \
{ \
    return lhs > rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_LESS_THAN_OR_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_) \
inline bool operator<=(const _basic_property_type_<_value_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() <= rhs; \
} \
inline bool operator<=(const _value_type_& lhs, const _basic_property_type_<_value_type_>& rhs) \
{ \
    return lhs <= rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_GREATER_THAN_OR_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_) \
inline bool operator>=(const _basic_property_type_<_value_type_>& lhs, const _value_type_& rhs) \
{ \
    return lhs.get() >= rhs; \
} \
inline bool operator>=(const _value_type_& lhs, const _basic_property_type_<_value_type_>& rhs) \
{ \
    return lhs >= rhs.get(); \
}

#define GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_COMPARISON_OPERATORS(_basic_property_type_, _value_type_) \
GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_) \
GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_NOT_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_) \
GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_LESS_THAN_OPERATOR(_basic_property_type_, _value_type_) \
GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_GREATER_THAN_OPERATOR(_basic_property_type_, _value_type_) \
GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_LESS_THAN_OR_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_) \
GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_GREATER_THAN_OR_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_)

#define GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(_basic_property_type_, _value_type_) \
GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_) \
GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_NOT_EQUAL_TO_OPERATOR(_basic_property_type_, _value_type_)

#endif  // #ifndef GO_BOOST_PROPERTY_NAMELESS_DETAIL_ARITHMETIC_COMPARISON_OPERATORS_HPP_INCLUDED
