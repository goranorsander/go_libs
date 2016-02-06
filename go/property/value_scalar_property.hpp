#ifndef GO_PROPERTY_VALUE_SCALAR_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_VALUE_SCALAR_PROPERTY_HPP_INCLUDED

//
//  value_scalar_property.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/property/detail/property_base.hpp>
#include <go/property/policy/value.hpp>
#include <algorithm>

namespace go
{
namespace property
{

template<class T, class S = std::string> class value_scalar_property
    : public detail::property_base<T, policy::value<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef value_scalar_property<value_type, string_type> this_type;

public:
    virtual ~value_scalar_property()
    {
    }

    explicit value_scalar_property(const string_type& property_name)
        : detail::property_base<value_type, policy::value<value_type>, string_type>(policy::value<value_type>(), property_name)
    {
    }

    explicit value_scalar_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::value<value_type>, string_type>(policy::value<value_type>(v), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

inline bool operator==(const value_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return lhs.get() == rhs;
}

inline bool operator!=(const value_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const value_scalar_property<std::string, std::string>& rhs)
{
    return lhs == rhs.get();
}

inline bool operator!=(const std::string& lhs, const value_scalar_property<std::string, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const value_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return lhs.get() == rhs;
}

inline bool operator!=(const value_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const value_scalar_property<std::wstring, std::string>& rhs)
{
    return lhs == rhs.get();
}

inline bool operator!=(const std::wstring& lhs, const value_scalar_property<std::wstring, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const value_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return lhs.get() == rhs;
}

inline bool operator!=(const value_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const value_scalar_property<std::string, std::wstring>& rhs)
{
    return lhs == rhs.get();
}

inline bool operator!=(const std::string& lhs, const value_scalar_property<std::string, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const value_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return lhs.get() == rhs;
}

inline bool operator!=(const value_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const value_scalar_property<std::wstring, std::wstring>& rhs)
{
    return lhs == rhs.get();
}

inline bool operator!=(const std::wstring& lhs, const value_scalar_property<std::wstring, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_VALUE_SCALAR_PROPERTY_HPP_INCLUDED
