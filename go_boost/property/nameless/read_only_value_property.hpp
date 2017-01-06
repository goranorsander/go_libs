#ifndef GO_BOOST_PROPERTY_NAMELESS_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_NAMELESS_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED

//
//  read_only_value_property.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/property/nameless/detail/arithmetic_comparison_operators.hpp>
#include <go_boost/property/nameless/detail/read_only_property_base.hpp>
#include <go_boost/property/policy/value.hpp>

namespace go_boost
{
namespace property
{
namespace nameless
{
namespace read_only
{

template<class T> class value_property
    : public detail::property_base<T, policy::value<T>>
{
public:
    typedef T value_type;
    typedef value_property<value_type> this_type;
    typedef typename policy::value<value_type> policy_type;

public:
    virtual ~value_property()
    {
    }

    explicit value_property(const value_type& v)
        : detail::property_base<value_type, policy::value<value_type>>(policy::value<value_type>(v))
    {
    }
};

GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(value_property, std::string)
GO_BOOST_IMPLEMENT_ANONYMOUS_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(value_property, std::wstring)

} // namespace read_only
} // namespace nameless
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_NAMELESS_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED
