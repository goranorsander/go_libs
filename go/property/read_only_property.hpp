#ifndef GO_PROPERTY_READ_ONLY_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_READ_ONLY_PROPERTY_HPP_INCLUDED

//
//  read_only_property.hpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <string>
#include <go/property/detail/arithmetic_comparison_operators.hpp>
#include <go/property/detail/read_only_property_base.hpp>
#include <go/property/policy/proxy.hpp>

namespace go
{
namespace property
{
namespace read_only
{

template<class T, class S, class L = std::recursive_mutex> class basic_property
    : public detail::property_base<T, policy::proxy<T, L>, S>
{
public:
    GO_USING(value_type, T);
    GO_USING(string_type, S);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef basic_property<value_type, string_type, lockable_type> this_type;
    typedef typename policy::proxy<value_type, lockable_type> policy_type;
#else
    using this_type = basic_property<value_type, string_type, lockable_type>;
    using policy_type = typename policy::proxy<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)
    GO_USING(get_function_signature, typename std::function<value_type(void)>);

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

template<class T, class L = std::recursive_mutex> class property
    : public basic_property<T, std::string, L>
{
public:
    GO_USING(value_type, T);
    GO_USING(string_type, std::string);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef property<value_type, lockable_type> this_type;
#else
    using this_type = property<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)
    GO_USING(get_function_signature, typename std::function<value_type(void)>);

public:
    virtual ~property() GO_DEFAULT_DESTRUCTOR

    explicit property(const std::string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    property(const std::string& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class wproperty
    : public basic_property<T, std::wstring, L>
{
public:
    GO_USING(value_type, T);
    GO_USING(string_type, std::wstring);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef wproperty<value_type, lockable_type> this_type;
#else
    using this_type = wproperty<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)
    GO_USING(get_function_signature, typename std::function<value_type(void)>);

public:
    virtual ~wproperty() GO_DEFAULT_DESTRUCTOR

    explicit wproperty(const std::wstring& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    wproperty(const std::wstring& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class u8property
    : public basic_property<T, string::u8string, L>
{
public:
    GO_USING(value_type, T);
    GO_USING(string_type, string::u8string);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef u8property<value_type, lockable_type> this_type;
#else
    using this_type = u8property<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)
    GO_USING(get_function_signature, typename std::function<value_type(void)>);

public:
    virtual ~u8property() GO_DEFAULT_DESTRUCTOR

    explicit u8property(const string::u8string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    u8property(const string::u8string& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class u16property
    : public basic_property<T, std::u16string, L>
{
public:
    GO_USING(value_type, T);
    GO_USING(string_type, std::u16string);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef u16property<value_type, lockable_type> this_type;
#else
    using this_type = u16property<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)
    GO_USING(get_function_signature, typename std::function<value_type(void)>);

public:
    virtual ~u16property() GO_DEFAULT_DESTRUCTOR

    explicit u16property(const std::u16string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    u16property(const std::u16string& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class u32property
    : public basic_property<T, std::u32string, L>
{
public:
    GO_USING(value_type, T);
    GO_USING(string_type, std::u32string);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef u32property<value_type, lockable_type> this_type;
#else
    using this_type = u32property<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)
    GO_USING(get_function_signature, typename std::function<value_type(void)>);

public:
    virtual ~u32property() GO_DEFAULT_DESTRUCTOR

    explicit u32property(const std::u32string& property_name)
        : basic_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    u32property(const std::u32string& property_name, const get_function_signature& get_function)
        : basic_property<value_type, string_type, lockable_type>(property_name, get_function)
    {
    }

#include <go/property/detail/deleted_assignment_operator.hpp>
};

GO_IMPLEMENT_DEFAULT_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(basic_property)

} // namespace read_only
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_READ_ONLY_PROPERTY_HPP_INCLUDED
