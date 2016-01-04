#ifndef GO_PROPERTY_OPTIONAL_SCALAR_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_OPTIONAL_SCALAR_PROPERTY_HPP_INCLUDED

//
//  optional_scalar_property.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/property/detail/property_base.hpp>
#include <go/property/policy/optional.hpp>
#include <algorithm>
//#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/access.hpp>

namespace go
{
namespace property
{

template<class T, class S = std::string> class optional_scalar_property : public detail::property_base<T, policy::optional<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef optional_scalar_property<value_type, string_type> this_type;

public:
    virtual ~optional_scalar_property()
    {
    }

    explicit optional_scalar_property(const string_type& property_name)
        : detail::property_base<value_type, policy::optional<value_type>, string_type>(policy::optional<value_type>(), property_name)
    {
    }

    explicit optional_scalar_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::optional<value_type>, string_type>(policy::optional<value_type>(v), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>

    bool empty() const
    {
        return storage().empty();
    }

    void clear()
    {
        return storage().clear();
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

inline bool operator==(const optional_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return lhs.empty() ? false : std::equal(lhs.get(), rhs);
}

inline bool operator!=(const optional_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const optional_scalar_property<std::string, std::string>& rhs)
{
    return rhs.empty() ? false : std::equal(lhs, rhs.get());
}

inline bool operator!=(const std::string& lhs, const optional_scalar_property<std::string, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const optional_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return lhs.empty() ? false : std::equal(lhs.get(), rhs);
}

inline bool operator!=(const optional_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const optional_scalar_property<std::wstring, std::string>& rhs)
{
    return rhs.empty() ? false : std::equal(lhs, rhs.get());
}

inline bool operator!=(const std::wstring& lhs, const optional_scalar_property<std::wstring, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const optional_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return lhs.empty() ? false : std::equal(lhs.get(), rhs);
}

inline bool operator!=(const optional_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const optional_scalar_property<std::string, std::wstring>& rhs)
{
    return rhs.empty() ? false : std::equal(lhs, rhs.get());
}

inline bool operator!=(const std::string& lhs, const optional_scalar_property<std::string, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const optional_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return lhs.empty() ? false : std::equal(lhs.get(), rhs);
}

inline bool operator!=(const optional_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const optional_scalar_property<std::wstring, std::wstring>& rhs)
{
    return rhs.empty() ? false : std::equal(lhs, rhs.get());
}

inline bool operator!=(const std::wstring& lhs, const optional_scalar_property<std::wstring, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_OPTIONAL_SCALAR_PROPERTY_HPP_INCLUDED
