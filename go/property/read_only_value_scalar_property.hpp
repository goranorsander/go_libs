#ifndef GO_PROPERTY_READ_ONLY_VALUE_SCALAR_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_READ_ONLY_VALUE_SCALAR_PROPERTY_HPP_INCLUDED

//
//  read_only_value_scalar_property.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <algorithm>
#include <string>
#include <go/property/detail/read_only_property_base.hpp>
#include <go/property/policy/value.hpp>

namespace go
{
namespace property
{
namespace read_only
{

template<class T, class S> class basic_value_scalar_property
    : public detail::property_base<T, policy::value<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef policy::value<T> policy_type;
    typedef basic_value_scalar_property<value_type, string_type> this_type;

public:
    virtual ~basic_value_scalar_property()
    {
    }

    explicit basic_value_scalar_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(v), property_name)
    {
    }
};

template<class T> class value_scalar_property
    : public basic_value_scalar_property<T, std::string>
{
public:
    typedef value_scalar_property<value_type> this_type;

public:
    virtual ~value_scalar_property()
    {
    }

    explicit value_scalar_property(const string_type& property_name, const value_type& v)
        : basic_value_scalar_property<value_type, string_type>(property_name, v)
    {
    }
};

template<class T> class value_scalar_wproperty
    : public basic_value_scalar_property<T, std::wstring>
{
public:
    typedef value_scalar_wproperty<value_type> this_type;

public:
    virtual ~value_scalar_wproperty()
    {
    }

    explicit value_scalar_wproperty(const string_type& property_name, const value_type& v)
        : basic_value_scalar_property<value_type, string_type>(property_name, v)
    {
    }
};

inline bool operator==(const basic_value_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return lhs.get() == rhs;
}

inline bool operator!=(const basic_value_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const basic_value_scalar_property<std::string, std::string>& rhs)
{
    return lhs == rhs.get();
}

inline bool operator!=(const std::string& lhs, const basic_value_scalar_property<std::string, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_value_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return lhs.get() == rhs;
}

inline bool operator!=(const basic_value_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const basic_value_scalar_property<std::wstring, std::string>& rhs)
{
    return lhs == rhs.get();
}

inline bool operator!=(const std::wstring& lhs, const basic_value_scalar_property<std::wstring, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_value_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return lhs.get() == rhs;
}

inline bool operator!=(const basic_value_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const basic_value_scalar_property<std::string, std::wstring>& rhs)
{
    return lhs == rhs.get();
}

inline bool operator!=(const std::string& lhs, const basic_value_scalar_property<std::string, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const basic_value_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return lhs.get() == rhs;
}

inline bool operator!=(const basic_value_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const basic_value_scalar_property<std::wstring, std::wstring>& rhs)
{
    return lhs == rhs.get();
}

inline bool operator!=(const std::wstring& lhs, const basic_value_scalar_property<std::wstring, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

} // namespace read_only
} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_READ_ONLY_VALUE_SCALAR_PROPERTY_HPP_INCLUDED
