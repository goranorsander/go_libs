#ifndef GO_BOOST_PROPERTY_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED

//
//  read_only_value_property.hpp
//
//  Copyright 2015-2017 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/property/detail/arithmetic_comparison_operators.hpp>
#include <go_boost/property/detail/read_only_property_base.hpp>
#include <go_boost/property/policy/value.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace go_boost
{
namespace property
{
namespace read_only
{

template<class T, class S> class basic_value_property
    : public detail::property_base<T, policy::value<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef basic_value_property<value_type, string_type> this_type;
    typedef typename policy::value<value_type> policy_type;

public:
    virtual ~basic_value_property()
    {
    }

    basic_value_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::value<value_type>, string_type>(policy::value<value_type>(v), property_name)
    {
    }
};

template<class T> class value_property
    : public basic_value_property<T, std::string>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef value_property<value_type> this_type;

public:
    virtual ~value_property()
    {
    }

    value_property(const string_type& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }
};

template<class T> class value_wproperty
    : public basic_value_property<T, std::wstring>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef value_wproperty<value_type> this_type;

public:
    virtual ~value_wproperty()
    {
    }

    value_wproperty(const string_type& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }
};

GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, std::wstring)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, std::wstring)

} // namespace read_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED
