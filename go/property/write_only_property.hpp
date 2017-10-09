#ifndef GO_PROPERTY_WRITE_ONLY_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_WRITE_ONLY_PROPERTY_HPP_INCLUDED

//
//  write_only_property.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <string>
#include <go/property/detail/write_only_property_base.hpp>
#include <go/property/policy/proxy.hpp>
#include <go/utility/u8string.hpp>

namespace go
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
    typedef basic_property<value_type, string_type> this_type;
    typedef typename policy::proxy<value_type> policy_type;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~basic_property() GO_DEFAULT_DESTRUCTOR

    explicit basic_property(const string_type& property_name)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    basic_property(const string_type& property_name, const set_function_signature& set_function)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(nullptr, set_function), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>

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
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property() GO_DEFAULT_DESTRUCTOR

    explicit property(const std::string& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    property(const std::string& property_name, const set_function_signature& set_function)
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
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~wproperty() GO_DEFAULT_DESTRUCTOR

    explicit wproperty(const std::wstring& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    wproperty(const std::wstring& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type>(property_name, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class u8property
    : public basic_property<T, utility::u8string>
{
public:
    typedef T value_type;
    typedef utility::u8string string_type;
    typedef u8property<value_type> this_type;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~u8property() GO_DEFAULT_DESTRUCTOR

    explicit u8property(const utility::u8string& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    u8property(const utility::u8string& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type>(property_name, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class u16property
    : public basic_property<T, std::u16string>
{
public:
    typedef T value_type;
    typedef std::u16string string_type;
    typedef u16property<value_type> this_type;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~u16property() GO_DEFAULT_DESTRUCTOR

    explicit u16property(const std::u16string& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    u16property(const std::u16string& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type>(property_name, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class u32property
    : public basic_property<T, std::u32string>
{
public:
    typedef T value_type;
    typedef std::u32string string_type;
    typedef u32property<value_type> this_type;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~u32property() GO_DEFAULT_DESTRUCTOR

    explicit u32property(const std::u32string& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    u32property(const std::u32string& property_name, const set_function_signature& set_function)
        : basic_property<value_type, string_type>(property_name, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_WRITE_ONLY_PROPERTY_HPP_INCLUDED
