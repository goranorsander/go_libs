#ifndef GO_BOOST_PROPERTY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_VALUE_PROPERTY_HPP_INCLUDED

//
//  value_property.hpp
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

#include <go_boost/property/detail/arithmetic_comparison_operators.hpp>
#include <go_boost/property/detail/property_base.hpp>
#include <go_boost/property/policy/value.hpp>
#include <go_boost/utility/u8string.hpp>
#include <go_boost/utility/u16string.hpp>
#include <go_boost/utility/u32string.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace go_boost
{
namespace property
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

    explicit basic_value_property(const string_type& property_name)
        : detail::property_base<value_type, policy::value<value_type>, string_type>(policy::value<value_type>(), property_name)
    {
    }

    basic_value_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::value<value_type>, string_type>(policy::value<value_type>(v), property_name)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
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

    explicit value_property(const std::string& property_name)
        : basic_value_property<value_type, string_type>(property_name)
    {
    }

    value_property(const std::string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
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

    explicit value_wproperty(const std::wstring& property_name)
        : basic_value_property<value_type, string_type>(property_name)
    {
    }

    value_wproperty(const std::wstring& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class value_u8property
    : public basic_value_property<T, utility::u8string>
{
public:
    typedef T value_type;
    typedef utility::u8string string_type;
    typedef value_u8property<value_type> this_type;

public:
    virtual ~value_u8property()
    {
    }

    explicit value_u8property(const utility::u8string& property_name)
        : basic_value_property<value_type, string_type>(property_name)
    {
    }

    value_u8property(const utility::u8string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class value_u16property
    : public basic_value_property<T, utility::u16string>
{
public:
    typedef T value_type;
    typedef utility::u16string string_type;
    typedef value_u16property<value_type> this_type;

public:
    virtual ~value_u16property()
    {
    }

    explicit value_u16property(const utility::u16string& property_name)
        : basic_value_property<value_type, string_type>(property_name)
    {
    }

    value_u16property(const utility::u16string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class value_u32property
    : public basic_value_property<T, utility::u32string>
{
public:
    typedef T value_type;
    typedef utility::u32string string_type;
    typedef value_u32property<value_type> this_type;

public:
    virtual ~value_u32property()
    {
    }

    explicit value_u32property(const utility::u32string& property_name)
        : basic_value_property<value_type, string_type>(property_name)
    {
    }

    value_u32property(const utility::u32string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, std::wstring)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, utility::u8string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, utility::u16string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, utility::u32string)

GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, std::wstring)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, utility::u8string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, utility::u16string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, utility::u32string)

GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, std::wstring)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, utility::u8string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, utility::u16string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, utility::u32string)

GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u16string, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u16string, std::wstring)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u16string, utility::u8string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u16string, utility::u16string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u16string, utility::u32string)

GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u32string, std::string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u32string, std::wstring)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u32string, utility::u8string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u32string, utility::u16string)
GO_BOOST_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u32string, utility::u32string)

} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_VALUE_PROPERTY_HPP_INCLUDED
