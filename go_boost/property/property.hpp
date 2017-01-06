#ifndef GO_BOOST_PROPERTY_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_PROPERTY_HPP_INCLUDED

//
//  property.hpp
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

#include <go_boost/property/detail/property_base.hpp>
#include <go_boost/property/policy/proxy.hpp>

namespace go_boost
{
namespace property
{

template<class T, class S> class basic_property
    : public detail::property_base<T, policy::proxy<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef basic_property<value_type, string_type> this_type;
    typedef typename policy::proxy<value_type> policy_type;
    typedef typename boost::function<value_type(void)> get_function_signature;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~basic_property()
    {
    }

    explicit basic_property(const string_type& property_name)
        : detail::property_base<value_type, policy::proxy<value_type>, string_type>(policy::proxy<value_type>(), property_name)
    {
    }

    explicit basic_property(const string_type& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : detail::property_base<value_type, policy::proxy<value_type>, string_type>(policy::proxy<value_type>(get_function, set_function), property_name)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>

    void getter(const get_function_signature& f)
    {
        detail::property_base<value_type, policy_type, string_type>::storage().getter(f);
    }

    void setter(const set_function_signature& f)
    {
        detail::property_base<value_type, policy_type, string_type>::storage().setter(f);
    }
};

template<class T> class property
    : public basic_property<T, std::string>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef property<value_type> this_type;
    typedef typename boost::function<value_type(void)> get_function_signature;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property()
    {
    }

    explicit property(const string_type& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    explicit property(const string_type& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : basic_property<value_type, string_type>(property_name, get_function, set_function)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T> class wproperty
    : public basic_property<T, std::wstring>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef wproperty<value_type> this_type;
    typedef typename boost::function<value_type(void)> get_function_signature;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~wproperty()
    {
    }

    explicit wproperty(const string_type& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    explicit wproperty(const string_type& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : basic_property<value_type, string_type>(property_name, get_function, set_function)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_PROPERTY_HPP_INCLUDED
