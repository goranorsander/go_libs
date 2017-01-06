#ifndef GO_PROPERTY_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED

//
//  write_only_value_property.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <string>
#include <go/property/detail/write_only_property_base.hpp>
#include <go/property/policy/value.hpp>

namespace go
{
namespace property
{
namespace write_only
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
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
    virtual ~basic_value_property() GO_DEFAULT_DESTRUCTOR
#else
	virtual ~basic_value_property() GO_DEFAULT_DESTRUCTOR
#endif  // !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    explicit basic_value_property(const string_type& property_name)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    explicit basic_value_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(v), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class value_property
    : public basic_value_property<T, std::string>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef value_property<value_type> this_type;

public:
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
    virtual ~value_property() GO_DEFAULT_DESTRUCTOR
#else
	virtual ~value_property() GO_DEFAULT_DESTRUCTOR
#endif  // !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    explicit value_property(const string_type& property_name)
        : basic_value_property<value_type, string_type>(property_name)
    {
    }

    explicit value_property(const string_type& property_name, const value_type& v)
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
#if !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
    virtual ~value_wproperty() GO_DEFAULT_DESTRUCTOR
#else
    virtual ~value_wproperty() GO_DEFAULT_DESTRUCTOR
#endif  // !defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    explicit value_wproperty(const string_type& property_name)
        : basic_value_property<value_type, string_type>(property_name)
    {
    }

    explicit value_wproperty(const string_type& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
