#ifndef GO_BOOST_PROPERTY_NAMELESS_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_NAMELESS_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED

//
//  write_only_value_property.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/property/nameless/detail/write_only_property_base.hpp>
#include <go_boost/property/policy/value.hpp>

namespace go_boost
{
namespace property
{
namespace nameless
{
namespace write_only
{

template<class T> class value_property
    : public detail::property_base<T, policy::value<T>>
{
public:
    typedef T value_type;
    typedef value_property<value_type> this_type;
    typedef typename policy::value<value_type> policy_type;

public:
    virtual ~value_property() GO_BOOST_DEFAULT_DESTRUCTOR

    value_property()
        : detail::property_base<value_type, policy::value<value_type>>(policy::value<value_type>())
    {
    }

    explicit value_property(const value_type& v)
        : detail::property_base<value_type, policy::value<value_type>>(policy::value<value_type>(v))
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace nameless
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_NAMELESS_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
