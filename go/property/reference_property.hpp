#ifndef GO_PROPERTY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  reference_property.hpp
//
//  Copyright 2015-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS) || defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <string>
#include <go/property/detail/arithmetic_comparison_operators.hpp>
#include <go/property/detail/property_base.hpp>
#include <go/property/policy/reference.hpp>

namespace go
{
namespace property
{

template<class T, class S, class L = std::recursive_mutex> class basic_reference_property
    : public detail::property_base<T, policy::reference<T, L>, S>
{
public:
    using value_type = T;
    using string_type = S;
    using lockable_type = L;
    using this_type = basic_reference_property<value_type, string_type, lockable_type>;
    using policy_type = typename policy::reference<value_type, lockable_type>;

public:
    virtual ~basic_reference_property() GO_DEFAULT_DESTRUCTOR

    explicit basic_reference_property(const string_type& property_name)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    basic_reference_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(v), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>

public:
    void bind(value_type& v)
    {
        detail::property_base<value_type, policy_type, string_type>::storage().bind(v);
    }

    GO_CONSTEXPR bool empty() const
    {
        return detail::property_base<value_type, policy_type, string_type>::storage().empty();
    }

    void reset()
    {
        detail::property_base<value_type, policy_type, string_type>::storage().reset();
    }

    explicit GO_CONSTEXPR operator bool() const
    {
        return !empty();
    }

    GO_CONSTEXPR bool operator!() const
    {
        return empty();
    }
};

template<class T, class L = std::recursive_mutex> class reference_property
    : public basic_reference_property<T, std::string, L>
{
public:
    using value_type = T;
    using string_type = std::string;
    using lockable_type = L;
    using this_type = reference_property<value_type, lockable_type>;

public:
    virtual ~reference_property() GO_DEFAULT_DESTRUCTOR

    explicit reference_property(const std::string& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_property(const std::string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class reference_wproperty
    : public basic_reference_property<T, std::wstring, L>
{
public:
    using value_type = T;
    using string_type = std::wstring;
    using lockable_type = L;
    using this_type = reference_wproperty<value_type, lockable_type>;

public:
    virtual ~reference_wproperty() GO_DEFAULT_DESTRUCTOR

    explicit reference_wproperty(const std::wstring& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_wproperty(const std::wstring& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class reference_u8property
    : public basic_reference_property<T, string::u8string, L>
{
public:
    using value_type = T;
    using string_type = string::u8string;
    using lockable_type = L;
    using this_type = reference_u8property<value_type, lockable_type>;

public:
    virtual ~reference_u8property() GO_DEFAULT_DESTRUCTOR

    explicit reference_u8property(const string::u8string& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_u8property(const string::u8string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class reference_u16property
    : public basic_reference_property<T, std::u16string, L>
{
public:
    using value_type = T;
    using string_type = std::u16string;
    using lockable_type = L;
    using this_type = reference_u16property<value_type, lockable_type>;

public:
    virtual ~reference_u16property() GO_DEFAULT_DESTRUCTOR

    explicit reference_u16property(const std::u16string& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_u16property(const std::u16string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T, class L = std::recursive_mutex> class reference_u32property
    : public basic_reference_property<T, std::u32string, L>
{
public:
    using value_type = T;
    using string_type = std::u32string;
    using lockable_type = L;
    using this_type = reference_u32property<value_type, lockable_type>;

public:
    virtual ~reference_u32property() GO_DEFAULT_DESTRUCTOR

    explicit reference_u32property(const std::u32string& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_u32property(const std::u32string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

GO_IMPLEMENT_DEFAULT_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property)

} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_REFERENCE_PROPERTY_HPP_INCLUDED
