#ifndef GO_PROPERTY_READ_ONLY_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_READ_ONLY_PROPERTY_HPP_INCLUDED

//
//  read_only_property.hpp
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

#include <string>
#include <go/property/detail/arithmetic_comparison_operators.hpp>
#include <go/property/detail/read_only_property_base.hpp>
#include <go/property/policy/proxy.hpp>
#include <go/utility/u8string.hpp>

namespace go
{
namespace property
{
namespace read_only
{

template<class T, class S> class basic_property
    : public detail::property_base<T, policy::proxy<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef basic_property<value_type, string_type> this_type;
    typedef typename policy::proxy<value_type> policy_type;
    typedef typename std::function<value_type(void)> get_function_signature;

public:
    virtual ~basic_property() GO_DEFAULT_DESTRUCTOR

    explicit basic_property(const string_type& property_name)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    basic_property(const string_type& property_name, const get_function_signature& get_function)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(get_function, nullptr), property_name)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>

public:
    void getter(const get_function_signature& f)
    {
        const_cast<policy_type&>(detail::property_base<value_type, policy_type, string_type>::storage()).getter(f);
    }
};

template<class T> class property
    : public basic_property<T, std::string>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef property<value_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;

public:
    virtual ~property() GO_DEFAULT_DESTRUCTOR

    explicit property(const std::string& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    property(const std::string& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

template<class T> class wproperty
    : public basic_property<T, std::wstring>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef wproperty<value_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;

public:
    virtual ~wproperty() GO_DEFAULT_DESTRUCTOR

    explicit wproperty(const std::wstring& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    wproperty(const std::wstring& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

template<class T> class u8property
    : public basic_property<T, utility::u8string>
{
public:
    typedef T value_type;
    typedef utility::u8string string_type;
    typedef u8property<value_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;

public:
    virtual ~u8property() GO_DEFAULT_DESTRUCTOR

    explicit u8property(const utility::u8string& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    u8property(const utility::u8string& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

template<class T> class u16property
    : public basic_property<T, std::u16string>
{
public:
    typedef T value_type;
    typedef std::u16string string_type;
    typedef u16property<value_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;

public:
    virtual ~u16property() GO_DEFAULT_DESTRUCTOR

    explicit u16property(const std::u16string& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    u16property(const std::u16string& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

template<class T> class u32property
    : public basic_property<T, std::u32string>
{
public:
    typedef T value_type;
    typedef std::u32string string_type;
    typedef u32property<value_type> this_type;
    typedef typename std::function<value_type(void)> get_function_signature;

public:
    virtual ~u32property() GO_DEFAULT_DESTRUCTOR

    explicit u32property(const std::u32string& property_name)
        : basic_property<value_type, string_type>(property_name)
    {
    }

    u32property(const std::u32string& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::string, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::string, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::string, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::string, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::string, std::u32string)

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::wstring, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::wstring, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::wstring, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::wstring, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::wstring, std::u32string)

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, utility::u8string, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, utility::u8string, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, utility::u8string, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, utility::u8string, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, utility::u8string, std::u32string)

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u16string, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u16string, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u16string, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u16string, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u16string, std::u32string)

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u32string, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u32string, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u32string, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u32string, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_property, std::u32string, std::u32string)

} // namespace read_only
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_READ_ONLY_PROPERTY_HPP_INCLUDED
