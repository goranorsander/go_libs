#ifndef GO_BOOST_PROPERTY_WRITE_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_WRITE_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  write_only_reference_property.hpp
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
#include <go_boost/property/policy/reference.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

namespace go_boost
{
namespace property
{
namespace write_only
{

template<class T, class S> class basic_reference_property
    : public detail::property_base<T, policy::reference<T>, S>
{
public:
    typedef typename T value_type;
    typedef typename S string_type;
    typedef typename policy::reference<value_type> policy_type;
    typedef typename basic_reference_property<value_type, string_type> this_type;

public:
    virtual ~basic_reference_property()
    {
    }

    explicit basic_reference_property(const string_type& property_name)
        : detail::property_base<value_type, policy::reference<value_type>, string_type>(policy::reference<value_type>(), property_name)
    {
    }

    explicit basic_reference_property(const string_type& property_name, const value_type& v)
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
    typedef typename T value_type;
    typedef typename std::string string_type;
    typedef typename reference_property<value_type> this_type;

public:
    virtual ~reference_property()
    {
    }

    explicit reference_property(const string_type& property_name)
        : basic_reference_property<value_type, string_type>(property_name)
    {
    }

    explicit reference_property(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class reference_wproperty
    : public basic_reference_property<T, std::wstring>
{
public:
    typedef typename T value_type;
    typedef typename std::wstring string_type;
    typedef typename reference_wproperty<value_type> this_type;

public:
    virtual ~reference_wproperty()
    {
    }

    explicit reference_wproperty(const string_type& property_name)
        : basic_reference_property<value_type, string_type>(property_name)
    {
    }

    explicit reference_wproperty(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_WRITE_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
