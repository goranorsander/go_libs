#ifndef GO_BOOST_PROPERTY_WRITE_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_WRITE_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  write_only_reference_property.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/property/detail/write_only_property_base.hpp>
#include <go_boost/property/policy/reference.hpp>
#include <go_boost/utility/u8string.hpp>
#include <go_boost/utility/u16string.hpp>
#include <go_boost/utility/u32string.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

namespace go_boost
{
namespace property
{
namespace write_only
{

template<class T, class S, class L = go_boost::utility::recursive_spin_lock> class basic_reference_property
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

    explicit basic_reference_property(const string_type& property_name)
        : detail::property_base<value_type, policy::reference<value_type, lockable_type>, string_type>(policy::reference<value_type, lockable_type>(), property_name)
    {
    }

    basic_reference_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::reference<value_type, lockable_type>, string_type>(policy::reference<value_type, lockable_type>(v), property_name)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>

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

template<class T, class L = go_boost::utility::recursive_spin_lock> class reference_property
    : public basic_reference_property<T, std::string, L>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef L lockable_type;
    typedef reference_property<value_type, lockable_type> this_type;

public:
    virtual ~reference_property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit reference_property(const std::string& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_property(const std::string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = go_boost::utility::recursive_spin_lock> class reference_wproperty
    : public basic_reference_property<T, std::wstring, L>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef L lockable_type;
    typedef reference_wproperty<value_type, lockable_type> this_type;

public:
    virtual ~reference_wproperty() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit reference_wproperty(const std::wstring& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_wproperty(const std::wstring& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = go_boost::utility::recursive_spin_lock> class reference_u8property
    : public basic_reference_property<T, utility::u8string, L>
{
public:
    typedef T value_type;
    typedef utility::u8string string_type;
    typedef L lockable_type;
    typedef reference_u8property<value_type, lockable_type> this_type;

public:
    virtual ~reference_u8property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit reference_u8property(const utility::u8string& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_u8property(const utility::u8string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = go_boost::utility::recursive_spin_lock> class reference_u16property
    : public basic_reference_property<T, utility::u16string, L>
{
public:
    typedef T value_type;
    typedef utility::u16string string_type;
    typedef L lockable_type;
    typedef reference_u16property<value_type, lockable_type> this_type;

public:
    virtual ~reference_u16property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit reference_u16property(const utility::u16string& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_u16property(const utility::u16string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T, class L = go_boost::utility::recursive_spin_lock> class reference_u32property
    : public basic_reference_property<T, utility::u32string, L>
{
public:
    typedef T value_type;
    typedef utility::u32string string_type;
    typedef L lockable_type;
    typedef reference_u32property<value_type, lockable_type> this_type;

public:
    virtual ~reference_u32property() GO_BOOST_DEFAULT_DESTRUCTOR

    explicit reference_u32property(const utility::u32string& property_name)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name)
    {
    }

    reference_u32property(const utility::u32string& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type, lockable_type>(property_name, v)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_WRITE_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
