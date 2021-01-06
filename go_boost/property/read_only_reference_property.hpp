#ifndef GO_BOOST_PROPERTY_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  read_only_reference_property.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/property/detail/arithmetic_comparison_operators.hpp>
#include <go_boost/property/detail/read_only_property_base.hpp>
#include <go_boost/property/policy/reference.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

namespace go_boost
{
namespace property
{
namespace read_only
{

template<class T, class S, class L = boost::recursive_mutex> class basic_reference_property
    : public detail::property_base<T, policy::reference<T, L>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_reference_property<value_type, string_type, lockable_type> this_type;
    typedef typename policy::reference<value_type, lockable_type> policy_type;

public:
    virtual ~basic_reference_property() GO_BOOST_DEFAULT_DESTRUCTOR

    basic_reference_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::reference<value_type, lockable_type>, string_type>(policy::reference<value_type, lockable_type>(const_cast<value_type&>(v)), property_name)
    {
    }

#include <go_boost/property/detail/deleted_assignment_operator.hpp>

public:
    void bind(value_type& v)
    {
        detail::property_base<value_type, policy_type, string_type>::storage().bind(v);
    }

    GO_BOOST_CONSTEXPR bool empty() const
    {
        return detail::property_base<value_type, policy_type, string_type>::storage().empty();
    }

    void reset()
    {
        detail::property_base<value_type, policy_type, string_type>::storage().reset();
    }

    BOOST_EXPLICIT_OPERATOR_BOOL()

    GO_BOOST_CONSTEXPR bool operator!() const
    {
        return empty();
    }
};

template<class T, class L = boost::recursive_mutex> class reference_property
    : public basic_reference_property<T, std::string, L>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef L lockable_type;
    typedef reference_property<value_type, lockable_type> this_type;

public:
    virtual ~reference_property() GO_BOOST_DEFAULT_DESTRUCTOR

    reference_property(const std::string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/deleted_assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class reference_wproperty
    : public basic_reference_property<T, std::wstring, L>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef L lockable_type;
    typedef reference_wproperty<value_type, lockable_type> this_type;

public:
    virtual ~reference_wproperty() GO_BOOST_DEFAULT_DESTRUCTOR

    reference_wproperty(const std::wstring& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/deleted_assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class reference_u8property
    : public basic_reference_property<T, string::u8string, L>
{
public:
    typedef T value_type;
    typedef string::u8string string_type;
    typedef L lockable_type;
    typedef reference_u8property<value_type, lockable_type> this_type;

public:
    virtual ~reference_u8property() GO_BOOST_DEFAULT_DESTRUCTOR

    reference_u8property(const string::u8string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/deleted_assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class reference_u16property
    : public basic_reference_property<T, string::u16string, L>
{
public:
    typedef T value_type;
    typedef string::u16string string_type;
    typedef L lockable_type;
    typedef reference_u16property<value_type, lockable_type> this_type;

public:
    virtual ~reference_u16property() GO_BOOST_DEFAULT_DESTRUCTOR

    reference_u16property(const string::u16string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/deleted_assignment_operator.hpp>
};

template<class T, class L = boost::recursive_mutex> class reference_u32property
    : public basic_reference_property<T, string::u32string, L>
{
public:
    typedef T value_type;
    typedef string::u32string string_type;
    typedef L lockable_type;
    typedef reference_u32property<value_type, lockable_type> this_type;

public:
    virtual ~reference_u32property() GO_BOOST_DEFAULT_DESTRUCTOR

    reference_u32property(const string::u32string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/deleted_assignment_operator.hpp>
};

GO_BOOST_IMPLEMENT_DEFAULT_PROPERTY_TYPES_ARITHMETIC_EQUALITY_OPERATORS(basic_reference_property)

} // namespace read_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
