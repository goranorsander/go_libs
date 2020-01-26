#ifndef GO_PROPERTY_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_PROPERTY_HPP_INCLUDED

//
//  property.hpp
//
//  Copyright 2015-2020 Göran Orsander
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
#include <go/property/detail/arithmetic_comparison_operators.hpp>
#include <go/property/detail/property_base.hpp>
#include <go/property/policy/proxy.hpp>

namespace go
{
namespace property
{

template<class T, class S, class L = std::recursive_mutex> class basic_property
    : public detail::property_base<T, policy::proxy<T, L>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_property<value_type, string_type, lockable_type> this_type;
    typedef typename policy::proxy<value_type, lockable_type> policy_type;
    typedef typename std::function<value_type(void)> get_function_signature;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~basic_property() GO_DEFAULT_DESTRUCTOR

    explicit basic_property(const string_type& property_name)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    basic_property(const string_type& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(get_function, set_function), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>

public:
    void getter(const get_function_signature& f)
    {
        detail::property_base<value_type, policy_type, string_type>::storage().getter(f);
    }

    void setter(const set_function_signature& f)
    {
        detail::property_base<value_type, policy_type, string_type>::storage().setter(f);
    }
};

template<class T, class L = std::recursive_mutex> class property
    : public basic_property<T, std::string, L>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef L lockable_type;
    typedef property<value_type, lockable_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property() GO_DEFAULT_DESTRUCTOR

    explicit property(const std::string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    property(const std::string& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class wproperty
    : public basic_property<T, std::wstring, L>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef L lockable_type;
    typedef wproperty<value_type, lockable_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~wproperty() GO_DEFAULT_DESTRUCTOR

    explicit wproperty(const std::wstring& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    wproperty(const std::wstring& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class u8property
    : public basic_property<T, string::u8string, L>
{
public:
    typedef T value_type;
    typedef string::u8string string_type;
    typedef L lockable_type;
    typedef u8property<value_type, lockable_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~u8property() GO_DEFAULT_DESTRUCTOR

    explicit u8property(const string::u8string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    u8property(const string::u8string& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class u16property
    : public basic_property<T, std::u16string, L>
{
public:
    typedef T value_type;
    typedef std::u16string string_type;
    typedef L lockable_type;
    typedef u16property<value_type, lockable_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~u16property() GO_DEFAULT_DESTRUCTOR

    explicit u16property(const std::u16string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    u16property(const std::u16string& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class u32property
    : public basic_property<T, std::u32string, L>
{
public:
    typedef T value_type;
    typedef std::u32string string_type;
    typedef L lockable_type;
    typedef u32property<value_type, lockable_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;
    typedef typename std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~u32property() GO_DEFAULT_DESTRUCTOR

    explicit u32property(const std::u32string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    u32property(const std::u32string& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function, set_function)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

GO_IMPLEMENT_DEFAULT_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(basic_property)

} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_PROPERTY_HPP_INCLUDED
