#ifndef GO_BOOST_PROPERTY_VALUE_SCALAR_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_VALUE_SCALAR_PROPERTY_HPP_INCLUDED

//
//  value_scalar_property.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/property/detail/property_base.hpp>
#include <go_boost/property/policy/value.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace go_boost
{
namespace property
{

template<class T, class S> class basic_value_scalar_property
    : public detail::property_base<T, policy::value<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef policy::value<value_type> policy_type;
    typedef basic_value_scalar_property<value_type, string_type> this_type;

public:
    virtual ~basic_value_scalar_property()
    {
    }

    explicit basic_value_scalar_property(const string_type& property_name)
        : detail::property_base<value_type, policy::value<value_type>, string_type>(policy::value<value_type>(), property_name)
    {
    }

    explicit basic_value_scalar_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::value<value_type>, string_type>(policy::value<value_type>(v), property_name)
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>
};

template<class T> class value_scalar_property
    : public basic_value_scalar_property<T, std::string>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef value_scalar_property<value_type> this_type;

public:
    virtual ~value_scalar_property()
    {
    }

    explicit value_scalar_property(const string_type& property_name)
        : basic_value_scalar_property<value_type, string_type>(property_name)
    {
    }

    explicit value_scalar_property(const string_type& property_name, const value_type& v)
        : basic_value_scalar_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class value_scalar_wproperty
    : public basic_value_scalar_property<T, std::wstring>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef value_scalar_wproperty<value_type> this_type;

public:
    virtual ~value_scalar_wproperty()
    {
    }

    explicit value_scalar_wproperty(const string_type& property_name)
        : basic_value_scalar_property<value_type, string_type>(property_name)
    {
    }

    explicit value_scalar_wproperty(const string_type& property_name, const value_type& v)
        : basic_value_scalar_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

inline bool operator==(const basic_value_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return boost::equals(lhs.get(), rhs);
}

inline bool operator!=(const basic_value_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const basic_value_scalar_property<std::string, std::string>& rhs)
{
    return boost::equals(lhs, rhs.get());
}

inline bool operator!=(const std::string& lhs, const basic_value_scalar_property<std::string, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_value_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return boost::equals(lhs.get(), rhs);
}

inline bool operator!=(const basic_value_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const basic_value_scalar_property<std::wstring, std::string>& rhs)
{
    return boost::equals(lhs, rhs.get());
}

inline bool operator!=(const std::wstring& lhs, const basic_value_scalar_property<std::wstring, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_value_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return boost::equals(lhs.get(), rhs);
}

inline bool operator!=(const basic_value_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const basic_value_scalar_property<std::string, std::wstring>& rhs)
{
    return boost::equals(lhs, rhs.get());
}

inline bool operator!=(const std::string& lhs, const basic_value_scalar_property<std::string, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_value_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return boost::equals(lhs.get(), rhs);
}

inline bool operator!=(const basic_value_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const basic_value_scalar_property<std::wstring, std::wstring>& rhs)
{
    return boost::equals(lhs, rhs.get());
}

inline bool operator!=(const std::wstring& lhs, const basic_value_scalar_property<std::wstring, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_VALUE_SCALAR_PROPERTY_HPP_INCLUDED
