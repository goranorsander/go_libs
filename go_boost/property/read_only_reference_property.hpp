#ifndef GO_BOOST_PROPERTY_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  read_only_reference_property.hpp
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

#include <go_boost/property/detail/arithmetic_comparison_operators.hpp>
#include <go_boost/property/detail/read_only_property_base.hpp>
#include <go_boost/property/policy/reference.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

namespace go_boost
{
namespace property
{
namespace read_only
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

    basic_reference_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::reference<value_type>, string_type>(policy::reference<value_type>(const_cast<value_type&>(v)), property_name)
    {
    }

    bool empty() const
    {
        return detail::property_base<value_type, policy_type, string_type>::storage().empty();
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

    reference_property(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }
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

    reference_wproperty(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }
};

GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property, std::string, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property, std::string, std::wstring)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property, std::wstring, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property, std::wstring, std::wstring)

} // namespace read_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
