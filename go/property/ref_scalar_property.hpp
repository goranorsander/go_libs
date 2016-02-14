#ifndef GO_PROPERTY_REF_SCALAR_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_REF_SCALAR_PROPERTY_HPP_INCLUDED

//
//  ref_scalar_property.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/property/detail/property_base.hpp>
#include <go/property/policy/ref.hpp>

namespace go
{
namespace property
{

template<class T, class S = std::string> class ref_scalar_property
    : public detail::property_base<T, policy::ref<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef ref_scalar_property<value_type, string_type> this_type;

public:
    virtual ~ref_scalar_property()
    {
    }

    explicit ref_scalar_property(const string_type& property_name)
        : detail::property_base<value_type, policy::ref<value_type>, string_type>(policy::ref<value_type>(), property_name)
    {
    }

    explicit ref_scalar_property(const string_type& property_name, const value_type& v)
        : detail::property_base<value_type, policy::ref<value_type>, string_type>(policy::ref<value_type>(v), property_name)
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

inline bool operator==(const ref_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return lhs.empty() ? false : lhs.get() == rhs;
}

inline bool operator!=(const ref_scalar_property<std::string, std::string>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const ref_scalar_property<std::string, std::string>& rhs)
{
    return rhs.empty() ? false : lhs == rhs.get();
}

inline bool operator!=(const std::string& lhs, const ref_scalar_property<std::string, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const ref_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return lhs.empty() ? false : lhs.get() == rhs;
}

inline bool operator!=(const ref_scalar_property<std::wstring, std::string>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const ref_scalar_property<std::wstring, std::string>& rhs)
{
    return rhs.empty() ? false : lhs == rhs.get();
}

inline bool operator!=(const std::wstring& lhs, const ref_scalar_property<std::wstring, std::string>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const ref_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return lhs.empty() ? false : lhs.get() == rhs;
}

inline bool operator!=(const ref_scalar_property<std::string, std::wstring>& lhs, const std::string& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::string& lhs, const ref_scalar_property<std::string, std::wstring>& rhs)
{
    return rhs.empty() ? false : lhs == rhs.get();
}

inline bool operator!=(const std::string& lhs, const ref_scalar_property<std::string, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const ref_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return lhs.empty() ? false : lhs.get() == rhs;
}

inline bool operator!=(const ref_scalar_property<std::wstring, std::wstring>& lhs, const std::wstring& rhs)
{
    return !operator==(lhs, rhs);
}

inline bool operator==(const std::wstring& lhs, const ref_scalar_property<std::wstring, std::wstring>& rhs)
{
    return rhs.empty() ? false : lhs == rhs.get();
}

inline bool operator!=(const std::wstring& lhs, const ref_scalar_property<std::wstring, std::wstring>& rhs)
{
    return !operator==(lhs, rhs);
}

} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_REF_SCALAR_PROPERTY_HPP_INCLUDED
