#ifndef GO_BOOST_PROPERTY_WRITE_ONLY_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_WRITE_ONLY_PROPERTY_HPP_INCLUDED

//
//  write_only_property.hpp
//
//  Copyright 2015-2022 Göran Orsander
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
#include <go_boost/property/policy/proxy.hpp>
#include <go_boost/string/u8string.hpp>
#include <go_boost/string/u16string.hpp>
#include <go_boost/string/u32string.hpp>

namespace go_boost
{
namespace property
{
namespace write_only
{

template<class T, class S, class L = boost::recursive_mutex> class basic_property
    : public detail::property_base<T, policy::proxy<T, L>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_property<value_type, string_type, lockable_type> this_type;
    typedef typename policy::proxy<value_type, lockable_type> policy_type;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~basic_property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit basic_property(const string_type& property_name)
        : detail::property_base<value_type, policy::proxy<value_type, lockable_type>, string_type>(policy::proxy<value_type, lockable_type>(), property_name)
    {
    }

    basic_property(const string_type& property_name, const set_function_signature& set_function)
        : detail::property_base<value_type, policy::proxy<value_type, lockable_type>, string_type>(policy::proxy<value_type, lockable_type>(NULL, set_function), property_name)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>

public:
    void setter(const set_function_signature& f)
    {
        detail::property_base<value_type, policy_type, string_type>::storage().setter(f);
    }
};

template<class T, class L = boost::recursive_mutex> class property
    : public basic_property<T, std::string, L>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef L lockable_type;
    typedef property<value_type, lockable_type> this_type;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit property(const std::string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    property(const std::string& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, set_function)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class wproperty
    : public basic_property<T, std::wstring, L>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef L lockable_type;
    typedef wproperty<value_type, lockable_type> this_type;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~wproperty() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit wproperty(const std::wstring& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    wproperty(const std::wstring& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, set_function)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class u8property
    : public basic_property<T, string::u8string, L>
{
public:
    typedef T value_type;
    typedef string::u8string string_type;
    typedef L lockable_type;
    typedef u8property<value_type, lockable_type> this_type;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~u8property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit u8property(const string::u8string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    u8property(const string::u8string& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, set_function)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class u16property
    : public basic_property<T, string::u16string, L>
{
public:
    typedef T value_type;
    typedef string::u16string string_type;
    typedef L lockable_type;
    typedef u16property<value_type, lockable_type> this_type;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~u16property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit u16property(const string::u16string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    u16property(const string::u16string& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, set_function)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class u32property
    : public basic_property<T, string::u32string, L>
{
public:
    typedef T value_type;
    typedef string::u32string string_type;
    typedef L lockable_type;
    typedef u32property<value_type, lockable_type> this_type;
    typedef typename boost::function<void(const value_type&)> set_function_signature;

public:
    virtual ~u32property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit u32property(const string::u32string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    u32property(const string::u32string& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, set_function)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_WRITE_ONLY_PROPERTY_HPP_INCLUDED
