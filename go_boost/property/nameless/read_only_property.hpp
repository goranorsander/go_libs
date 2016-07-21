#ifndef GO_BOOST_PROPERTY_ANONYMOUS_READ_ONLY_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_ANONYMOUS_READ_ONLY_PROPERTY_HPP_INCLUDED

//
//  read_only_property.hpp
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

#include <go_boost/property/nameless/detail/read_only_property_base.hpp>
#include <go_boost/property/policy/proxy.hpp>

namespace go_boost
{
namespace property
{
namespace nameless
{
namespace read_only
{

template<class T> class property
    : public detail::property_base<T, policy::proxy<T>>
{
public:
    typedef T value_type;
    typedef property<value_type> this_type;
    typedef typename policy::proxy<value_type> policy_type;
    typedef typename boost::function<value_type(void)> get_function_signature;

public:
    virtual ~property()
    {
    }

    explicit property()
        : detail::property_base<value_type, policy::proxy<value_type>>(policy::proxy<value_type>())
    {
    }

    explicit property(const get_function_signature& get_function)
        : detail::property_base<value_type, policy::proxy<value_type>>(policy::proxy<value_type>(get_function, NULL))
    {
    }

    void getter(const get_function_signature& f)
    {
        const_cast<policy_type&>(detail::property_base<value_type, policy_type>::storage()).getter(f);
    }
};

} // namespace read_only
} // namespace nameless
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_ANONYMOUS_READ_ONLY_PROPERTY_HPP_INCLUDED
