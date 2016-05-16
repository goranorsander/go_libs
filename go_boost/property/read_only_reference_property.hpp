#ifndef GO_BOOST_PROPERTY_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  read_only_reference_property.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

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

template<class T, class S> class basic_reference_property
    : public detail::property_base<T, policy::reference<T>, S>
{
public:
    typedef typename T value_type;
    typedef typename S string_type;
    typedef typename policy::reference<value_type> policy_type;
    typedef typename basic_reference_property<value_type, string_type> this_type;

public:
    virtual ~basic_reference_property()
    {
    }

    explicit basic_reference_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::reference<value_type>, string_type>(policy::reference<value_type>(const_cast<value_type&>(v)), property_name)
    {
    }

    bool empty() const
    {
        return detail::property_base<value_type, policy_type, string_type>::storage().empty();
    }

    BOOST_EXPLICIT_OPERATOR_BOOL()

    bool operator!() const
    {
        return empty();
    }
};

template<class T> class reference_property
    : public basic_reference_property<T, std::string>
{
public:
    typedef typename T value_type;
    typedef typename std::string string_type;
    typedef typename reference_property<value_type> this_type;

public:
    virtual ~reference_property()
    {
    }

    explicit reference_property(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }
};

template<class T> class reference_wproperty
    : public basic_reference_property<T, std::wstring>
{
public:
    typedef typename T value_type;
    typedef typename std::wstring string_type;
    typedef typename reference_wproperty<value_type> this_type;

public:
    virtual ~reference_wproperty()
    {
    }

    explicit reference_wproperty(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }
};

inline bool operator==(const basic_reference_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return lhs.empty() ? false : boost::equals(lhs.get(), rhs);
}

inline bool operator!=(const basic_reference_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const basic_reference_property<std::string, std::string>& rhs)
{
    return rhs.empty() ? false : boost::equals(lhs, rhs.get());
}

inline bool operator!=(const std::string& lhs, const basic_reference_property<std::string, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_reference_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return lhs.empty() ? false : boost::equals(lhs.get(), rhs);
}

inline bool operator!=(const basic_reference_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const basic_reference_property<std::wstring, std::string>& rhs)
{
    return rhs.empty() ? false : boost::equals(lhs, rhs.get());
}

inline bool operator!=(const std::wstring& lhs, const basic_reference_property<std::wstring, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_reference_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return lhs.empty() ? false : boost::equals(lhs.get(), rhs);
}

inline bool operator!=(const basic_reference_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const basic_reference_property<std::string, std::wstring>& rhs)
{
    return rhs.empty() ? false : boost::equals(lhs, rhs.get());
}

inline bool operator!=(const std::string& lhs, const basic_reference_property<std::string, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_reference_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return lhs.empty() ? false : boost::equals(lhs.get(), rhs);
}

inline bool operator!=(const basic_reference_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const basic_reference_property<std::wstring, std::wstring>& rhs)
{
    return rhs.empty() ? false : boost::equals(lhs, rhs.get());
}

inline bool operator!=(const std::wstring& lhs, const basic_reference_property<std::wstring, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

} // namespace read_only
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_READ_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
