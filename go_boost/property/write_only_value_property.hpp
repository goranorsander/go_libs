#ifndef GO_BOOST_PROPERTY_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED

//
//  write_only_value_property.hpp
//
//  Copyright 2015-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/property/detail/write_only_property_base.hpp>
#include <go_boost/property/policy/value.hpp>
#include <go_boost/string/u8string.hpp>
#include <go_boost/string/u16string.hpp>
#include <go_boost/string/u32string.hpp>

namespace go_boost
{
namespace property
{
namespace write_only
{

template<class T, class S, class L = boost::recursive_mutex> class basic_value_property
    : public detail::property_base<T, policy::value<T, L>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_value_property<value_type, string_type, lockable_type> this_type;
    typedef typename policy::value<value_type, lockable_type> policy_type;

public:
    virtual ~basic_value_property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit basic_value_property(const string_type& property_name)
        : detail::property_base<value_type, policy::value<value_type, lockable_type>, string_type>(policy::value<value_type, lockable_type>(), property_name)
    {
    }

    basic_value_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::value<value_type, lockable_type>, string_type>(policy::value<value_type, lockable_type>(v), property_name)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class value_property
    : public basic_value_property<T, std::string, L>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef L lockable_type;
    typedef value_property<value_type, lockable_type> this_type;

public:
    virtual ~value_property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit value_property(const std::string& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_property(const std::string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class value_wproperty
    : public basic_value_property<T, std::wstring, L>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef L lockable_type;
    typedef value_wproperty<value_type, lockable_type> this_type;

public:
    virtual ~value_wproperty() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit value_wproperty(const std::wstring& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_wproperty(const std::wstring& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class value_u8property
    : public basic_value_property<T, string::u8string, L>
{
public:
    typedef T value_type;
    typedef string::u8string string_type;
    typedef L lockable_type;
    typedef value_u8property<value_type, lockable_type> this_type;

public:
    virtual ~value_u8property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit value_u8property(const string::u8string& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_u8property(const string::u8string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class value_u16property
    : public basic_value_property<T, string::u16string, L>
{
public:
    typedef T value_type;
    typedef string::u16string string_type;
    typedef L lockable_type;
    typedef value_u16property<value_type, lockable_type> this_type;

public:
    virtual ~value_u16property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit value_u16property(const string::u16string& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_u16property(const string::u16string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class value_u32property
    : public basic_value_property<T, string::u32string, L>
{
public:
    typedef T value_type;
    typedef string::u32string string_type;
    typedef L lockable_type;
    typedef value_u32property<value_type, lockable_type> this_type;

public:
    virtual ~value_u32property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit value_u32property(const string::u32string& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_u32property(const string::u32string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
