#ifndef GO_PROPERTY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  reference_property.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <string>
#include <go/property/detail/property_base.hpp>
#include <go/property/policy/reference.hpp>

namespace go
{
namespace property
{

template<class T, class S> class basic_reference_property
    : public detail::property_base<T, policy::reference<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef basic_reference_property<value_type, string_type> this_type;
    typedef typename policy::reference<value_type> policy_type;

public:
    virtual ~basic_reference_property()
    {
    }

    explicit basic_reference_property(const string_type& property_name)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    explicit basic_reference_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(v), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>

    bool empty() const
    {
        return detail::property_base<value_type, policy_type, string_type>::storage().empty();
    }

    void clear()
    {
        return detail::property_base<value_type, policy_type, string_type>::storage().clear();
    }

    explicit operator bool() const
    {
        return !empty();
    }

    bool operator!() const
    {
        return empty();
    }
};

template<class T> class reference_property
    : public basic_reference_property<T, std::string>
{
public:
    typedef T value_type;
    typedef std::string string_type;
    typedef reference_property<value_type> this_type;

public:
    virtual ~reference_property()
    {
    }

    explicit reference_property(const string_type& property_name)
        : basic_reference_property<value_type, string_type>(property_name)
    {
    }

    explicit reference_property(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class reference_wproperty
    : public basic_reference_property<T, std::wstring>
{
public:
    typedef T value_type;
    typedef std::wstring string_type;
    typedef reference_wproperty<value_type> this_type;

public:
    virtual ~reference_wproperty()
    {
    }

    explicit reference_wproperty(const string_type& property_name)
        : basic_reference_property<value_type, string_type>(property_name)
    {
    }

    explicit reference_wproperty(const string_type& property_name, const value_type& v)
        : basic_reference_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

inline bool operator==(const basic_reference_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return lhs.empty() ? false : lhs.get() == rhs;
}

inline bool operator!=(const basic_reference_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const basic_reference_property<std::string, std::string>& rhs)
{
    return rhs.empty() ? false : lhs == rhs.get();
}

inline bool operator!=(const std::string& lhs, const basic_reference_property<std::string, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_reference_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return lhs.empty() ? false : lhs.get() == rhs;
}

inline bool operator!=(const basic_reference_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const basic_reference_property<std::wstring, std::string>& rhs)
{
    return rhs.empty() ? false : lhs == rhs.get();
}

inline bool operator!=(const std::wstring& lhs, const basic_reference_property<std::wstring, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_reference_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return lhs.empty() ? false : lhs.get() == rhs;
}

inline bool operator!=(const basic_reference_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const basic_reference_property<std::string, std::wstring>& rhs)
{
    return rhs.empty() ? false : lhs == rhs.get();
}

inline bool operator!=(const std::string& lhs, const basic_reference_property<std::string, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_reference_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return lhs.empty() ? false : lhs.get() == rhs;
}

inline bool operator!=(const basic_reference_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const basic_reference_property<std::wstring, std::wstring>& rhs)
{
    return rhs.empty() ? false : lhs == rhs.get();
}

inline bool operator!=(const std::wstring& lhs, const basic_reference_property<std::wstring, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

} // namespace property
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_PROPERTY_REFERENCE_PROPERTY_HPP_INCLUDED
