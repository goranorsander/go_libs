#ifndef GO_BOOST_PROPERTY_NAMELESS_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_NAMELESS_PROPERTY_HPP_INCLUDED

//
//  property.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/property/nameless/detail/property_base.hpp>
#include <go_boost/property/policy/proxy.hpp>

namespace go_boost
{
namespace property
{
namespace nameless
{

template<class T> class property
    : public detail::property_base<T, policy::proxy<T>>
{
public:
    typedef T value_type;
    typedef property<value_type> this_type;
    typedef typename policy::proxy<value_type> policy_type;
    typedef typename boost::function<value_type(void)> get_function_signature;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property()
    {
    }

    explicit property()
        : detail::property_base<value_type, policy::proxy<value_type>>(policy::proxy<value_type>())
    {
    }

    explicit property(const get_function_signature& get_function, const set_function_signature& set_function)
        : detail::property_base<value_type, policy::proxy<value_type>>(policy::proxy<value_type>(get_function, set_function))
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>

    void getter(const get_function_signature& f)
    {
        detail::property_base<value_type, policy_type>::storage().getter(f);
    }

    void setter(const set_function_signature& f)
    {
        detail::property_base<value_type, policy_type>::storage().setter(f);
    }
};

} // namespace nameless
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_NAMELESS_PROPERTY_HPP_INCLUDED
