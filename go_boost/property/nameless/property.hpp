#ifndef GO_BOOST_PROPERTY_NAMELESS_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_NAMELESS_PROPERTY_HPP_INCLUDED

//
//  property.hpp
//
//  Copyright 2015-2018 Göran Orsander
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
#include <go_boost/property/nameless/detail/property_base.hpp>
#include <go_boost/property/policy/proxy.hpp>

namespace go_boost
{
namespace property
{
namespace nameless
{

template<class T, class L = boost::recursive_mutex> class property
    : public detail::property_base<T, policy::proxy<T, L>>
{
public:
    typedef T value_type;
    typedef L lockable_type;
    typedef property<value_type, lockable_type> this_type;
    typedef typename policy::proxy<value_type, lockable_type> policy_type;
    typedef typename boost::function<value_type(void)> get_function_signature;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property() GO_BOOST_DEFAULT_DESTRUCTOR

     property()
        : detail::property_base<value_type, policy_type>(policy::proxy<value_type, lockable_type>())
    {
    }

    property(const get_function_signature& get_function, const set_function_signature& set_function)
        : detail::property_base<value_type, policy_type>(policy::proxy<value_type, lockable_type>(get_function, set_function))
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>

public:
    void getter(const get_function_signature& f)
    {
        detail::property_base<value_type, policy_type>::storage().getter(f);
    }

    void setter(const set_function_signature& f)
    {
        detail::property_base<value_type, policy_type>::storage().setter(f);
    }
};

GO_BOOST_IMPLEMENT_DEFAULT_NAMELESS_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(property)

} // namespace nameless
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_NAMELESS_PROPERTY_HPP_INCLUDED
