#ifndef GO_BOOST_PROPERTY_WRITE_ONLY_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_WRITE_ONLY_PROPERTY_HPP_INCLUDED

//
//  write_only_property.hpp
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

#include <go_boost/property/detail/write_only_property_base.hpp>
#include <go_boost/property/policy/proxy.hpp>

namespace go_boost
{
namespace property
{
namespace write_only
{

template<class T, class S> class basic_property
    : public detail::property_base<T, policy::proxy<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef policy::proxy<value_type> policy_type;
    typedef basic_property<value_type, string_type> this_type;
    typedef boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~basic_property()
    {
    }

    basic_property(const string_type& property_name)
        : detail::property_base<value_type, policy::proxy<value_type>, string_type>(policy::proxy<value_type>(), property_name)
    {
    }

    explicit basic_property(const string_type& property_name, const set_function_signature& set_function)
        : detail::property_base<value_type, policy::proxy<value_type>, string_type>(policy::proxy<value_type>(NULL, set_function), property_name)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>

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
    typedef boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property()
    {
    }

    property(const string_type& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    explicit property(const string_type& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type>(property_name, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class wproperty
    : public basic_property<T, std::wstring>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef wproperty<value_type> this_type;
    typedef boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~wproperty()
    {
    }

    wproperty(const string_type& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    explicit wproperty(const string_type& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type>(property_name, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_WRITE_ONLY_PROPERTY_HPP_INCLUDED
