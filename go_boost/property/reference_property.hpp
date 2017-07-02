#ifndef GO_BOOST_PROPERTY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  reference_property.hpp
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
#include <go_boost/property/detail/property_base.hpp>
#include <go_boost/property/policy/reference.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

namespace go_boost
{
namespace property
{

template<class T, class S> class basic_reference_property
    : public detail::property_base<T, policy::reference<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef basic_reference_property<value_type, string_type> this_type;
    typedef typename policy::reference<value_type> policy_type;

public:
    virtual ~basic_reference_property()
    {
    }

    explicit basic_reference_property(const string_type& property_name)
        : detail::property_base<value_type, policy::reference<value_type>, string_type>(policy::reference<value_type>(), property_name)
    {
    }

    basic_reference_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::reference<value_type>, string_type>(policy::reference<value_type>(v), property_name)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>

    bool empty() const
    {
        return detail::property_base<value_type, policy_type, string_type>::storage().empty();
    }

    void clear()
    {
        return detail::property_base<value_type, policy_type, string_type>::storage().clear();
    }

    BOOST_EXPLICIT_OPERATOR_BOOL()

        bool operator!() const
    {
        return empty();
    }
};

template<class T> class reference_property
    : public basic_reference_property<T, std::string>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef reference_property<value_type> this_type;

public:
    virtual ~reference_property()
    {
    }

    explicit reference_property(const string_type& property_name)
        : basic_reference_property<value_type, string_type>(property_name)
    {
    }

    reference_property(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class reference_wproperty
    : public basic_reference_property<T, std::wstring>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef reference_wproperty<value_type> this_type;

public:
    virtual ~reference_wproperty()
    {
    }

    explicit reference_wproperty(const string_type& property_name)
        : basic_reference_property<value_type, string_type>(property_name)
    {
    }

    reference_wproperty(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property, std::string, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property, std::string, std::wstring)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property, std::wstring, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property, std::wstring, std::wstring)

} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_REFERENCE_PROPERTY_HPP_INCLUDED
