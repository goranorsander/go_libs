#ifndef GO_BOOST_PROPERTY_NAMELESS_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_NAMELESS_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED

//
//  read_only_value_property.hpp
//
//  Copyright 2015-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

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

template<class T, class L = boost::recursive_mutex> class value_property
    : public detail::property_base<T, policy::value<T, L>>
{
public:
    typedef T value_type;
    typedef L lockable_type;
    typedef value_property<value_type, lockable_type> this_type;
    typedef typename policy::value<value_type, lockable_type> policy_type;

public:
    virtual ~value_property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit value_property(const value_type& v)
        : detail::property_base<value_type, policy_type>(policy::value<value_type, lockable_type>(v))
    {
    }

#include <go_boost/property/detail/deleted_assignment_operator.hpp>
};

GO_BOOST_IMPLEMENT_DEFAULT_NAMELESS_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(value_property)

} // namespace read_only
} // namespace nameless
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_NAMELESS_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED
