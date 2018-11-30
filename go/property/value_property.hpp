#ifndef GO_PROPERTY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_VALUE_PROPERTY_HPP_INCLUDED

//
//  value_property.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <algorithm>
#include <string>
#include <go/property/detail/arithmetic_comparison_operators.hpp>
#include <go/property/detail/property_base.hpp>
#include <go/property/policy/value.hpp>

namespace go
{
namespace property
{

template<class T, class S, class L = std::recursive_mutex> class basic_value_property
    : public detail::property_base<T, policy::value<T, L>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_value_property<value_type, string_type, lockable_type> this_type;
    typedef typename policy::value<value_type, lockable_type> policy_type;

public:
    virtual ~basic_value_property() GO_DEFAULT_DESTRUCTOR

    explicit basic_value_property(const string_type& property_name)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    basic_value_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(v), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class value_property
    : public basic_value_property<T, std::string, L>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef L lockable_type;
    typedef value_property<value_type, lockable_type> this_type;

public:
    virtual ~value_property() GO_DEFAULT_DESTRUCTOR

    explicit value_property(const std::string& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_property(const std::string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class value_wproperty
    : public basic_value_property<T, std::wstring, L>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef L lockable_type;
    typedef value_wproperty<value_type, lockable_type> this_type;

public:
    virtual ~value_wproperty() GO_DEFAULT_DESTRUCTOR

    explicit value_wproperty(const std::wstring& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_wproperty(const std::wstring& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class value_u8property
    : public basic_value_property<T, utility::u8string, L>
{
public:
    typedef T value_type;
    typedef utility::u8string string_type;
    typedef L lockable_type;
    typedef value_u8property<value_type, lockable_type> this_type;

public:
    virtual ~value_u8property() GO_DEFAULT_DESTRUCTOR

    explicit value_u8property(const utility::u8string& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_u8property(const utility::u8string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class value_u16property
    : public basic_value_property<T, std::u16string, L>
{
public:
    typedef T value_type;
    typedef std::u16string string_type;
    typedef L lockable_type;
    typedef value_u16property<value_type, lockable_type> this_type;

public:
    virtual ~value_u16property() GO_DEFAULT_DESTRUCTOR

    explicit value_u16property(const std::u16string& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_u16property(const std::u16string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class value_u32property
    : public basic_value_property<T, std::u32string, L>
{
public:
    typedef T value_type;
    typedef std::u32string string_type;
    typedef L lockable_type;
    typedef value_u32property<value_type, lockable_type> this_type;

public:
    virtual ~value_u32property() GO_DEFAULT_DESTRUCTOR

    explicit value_u32property(const std::u32string& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_u32property(const std::u32string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

GO_IMPLEMENT_DEFAULT_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property)

} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_VALUE_PROPERTY_HPP_INCLUDED
