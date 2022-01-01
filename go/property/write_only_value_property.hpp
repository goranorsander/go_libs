#ifndef GO_PROPERTY_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED

//
//  write_only_value_property.hpp
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
#include <go/property/detail/write_only_property_base.hpp>
#include <go/property/policy/value.hpp>
#include <go/string/u8string.hpp>

namespace go
{
namespace property
{
namespace write_only
{

template<class T, class S, class L = std::recursive_mutex> class basic_value_property
    : public detail::property_base<T, policy::value<T, L>, S>
{
public:
    GO_USING(value_type, T);
    GO_USING(string_type, S);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef basic_value_property<value_type, string_type, lockable_type> this_type;
    typedef typename policy::value<value_type, lockable_type> policy_type;
#else
    using this_type = basic_value_property<value_type, string_type, lockable_type>;
    using policy_type = typename policy::value<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

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
    GO_USING(value_type, T);
    GO_USING(string_type, std::string);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef value_property<value_type, lockable_type> this_type;
#else
    using this_type = value_property<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

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
    GO_USING(value_type, T);
    GO_USING(string_type, std::wstring);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef value_wproperty<value_type, lockable_type> this_type;
#else
    using this_type = value_wproperty<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

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
    : public basic_value_property<T, string::u8string, L>
{
public:
    GO_USING(value_type, T);
    GO_USING(string_type, string::u8string);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef value_u8property<value_type, lockable_type> this_type;
#else
    using this_type = value_u8property<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

public:
    virtual ~value_u8property() GO_DEFAULT_DESTRUCTOR

    explicit value_u8property(const string::u8string& property_name)
        : basic_value_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    value_u8property(const string::u8string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class value_u16property
    : public basic_value_property<T, std::u16string, L>
{
public:
    GO_USING(value_type, T);
    GO_USING(string_type, std::u16string);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef value_u16property<value_type, lockable_type> this_type;
#else
    using this_type = value_u16property<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

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
    GO_USING(value_type, T);
    GO_USING(string_type, std::u32string);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef value_u32property<value_type, lockable_type> this_type;
#else
    using this_type = value_u32property<value_type, lockable_type>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

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

} // namespace write_only
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_WRITE_ONLY_VALUE_PROPERTY_HPP_INCLUDED
