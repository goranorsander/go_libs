#ifndef GO_PROPERTY_WRITE_ONLY_REF_SCALAR_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_WRITE_ONLY_REF_SCALAR_PROPERTY_HPP_INCLUDED

//
//  write_only_ref_scalar_property.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <string>
#include <go/property/detail/write_only_property_base.hpp>
#include <go/property/policy/ref.hpp>

namespace go
{
namespace property
{
namespace write_only
{

template<class T, class S> class basic_ref_scalar_property
    : public detail::property_base<T, policy::ref<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef policy::ref<T> policy_type;
    typedef basic_ref_scalar_property<value_type, string_type> this_type;

public:
    virtual ~basic_ref_scalar_property()
    {
    }

    basic_ref_scalar_property(const string_type& property_name)
        : detail::property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    explicit basic_ref_scalar_property(const string_type& property_name, const value_type& v)
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

template<class T> class ref_scalar_property
    : public basic_ref_scalar_property<T, std::string>
{
public:
    typedef ref_scalar_property<value_type> this_type;

public:
    virtual ~ref_scalar_property()
    {
    }

    explicit ref_scalar_property(const string_type& property_name)
        : basic_ref_scalar_property<value_type, string_type>(property_name)
    {
    }

    explicit ref_scalar_property(const string_type& property_name, const value_type& v)
        : basic_ref_scalar_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

template<class T> class ref_scalar_wproperty
    : public basic_ref_scalar_property<T, std::wstring>
{
public:
    typedef ref_scalar_wproperty<value_type> this_type;

public:
    virtual ~ref_scalar_wproperty()
    {
    }

    explicit ref_scalar_wproperty(const string_type& property_name)
        : basic_ref_scalar_property<value_type, string_type>(property_name)
    {
    }

    explicit ref_scalar_wproperty(const string_type& property_name, const value_type& v)
        : basic_ref_scalar_property<value_type, string_type>(property_name, v)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

} // namespace write_only
} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_WRITE_ONLY_REF_SCALAR_PROPERTY_HPP_INCLUDED
