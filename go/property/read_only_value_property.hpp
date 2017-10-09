#ifndef GO_PROPERTY_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED

//
//  read_only_value_property.hpp
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

#include <algorithm>
#include <string>
#include <go/property/detail/arithmetic_comparison_operators.hpp>
#include <go/property/detail/read_only_property_base.hpp>
#include <go/property/policy/value.hpp>
#include <go/utility/u8string.hpp>

namespace go
{
namespace property
{
namespace read_only
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
    virtual ~basic_value_property() GO_DEFAULT_DESTRUCTOR

    basic_value_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(v), property_name)
    {
    }
};

template<class T> class value_property
    : public basic_value_property<T, std::string>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef value_property<value_type> this_type;

public:
    virtual ~value_property() GO_DEFAULT_DESTRUCTOR

    value_property(const std::string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }
};

template<class T> class value_wproperty
    : public basic_value_property<T, std::wstring>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef value_wproperty<value_type> this_type;

public:
    virtual ~value_wproperty() GO_DEFAULT_DESTRUCTOR

    value_wproperty(const std::wstring& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }
};

template<class T> class value_u8property
    : public basic_value_property<T, utility::u8string>
{
public:
    typedef T value_type;
    typedef utility::u8string string_type;
    typedef value_u8property<value_type> this_type;

public:
    virtual ~value_u8property() GO_DEFAULT_DESTRUCTOR

    value_u8property(const utility::u8string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }
};

template<class T> class value_u16property
    : public basic_value_property<T, std::u16string>
{
public:
    typedef T value_type;
    typedef std::u16string string_type;
    typedef value_u16property<value_type> this_type;

public:
    virtual ~value_u16property() GO_DEFAULT_DESTRUCTOR

    value_u16property(const std::u16string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }
};

template<class T> class value_u32property
    : public basic_value_property<T, std::u32string>
{
public:
    typedef T value_type;
    typedef std::u32string string_type;
    typedef value_u32property<value_type> this_type;

public:
    virtual ~value_u32property() GO_DEFAULT_DESTRUCTOR

    value_u32property(const std::u32string& property_name, const value_type& v)
        : basic_value_property<value_type, string_type>(property_name, v)
    {
    }
};

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::string, std::u32string)

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::wstring, std::u32string)

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, utility::u8string, std::u32string)

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u16string, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u16string, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u16string, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u16string, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u16string, std::u32string)

GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u32string, std::string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u32string, std::wstring)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u32string, utility::u8string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u32string, std::u16string)
GO_IMPLEMENT_PROPERTY_ARITHMETIC_EQUALITY_OPERATORS(basic_value_property, std::u32string, std::u32string)

} // namespace read_only
} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_READ_ONLY_VALUE_PROPERTY_HPP_INCLUDED
