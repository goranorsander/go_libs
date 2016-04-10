#ifndef GO_PROPERTY_WO_REF_SCALAR_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_WO_REF_SCALAR_PROPERTY_HPP_INCLUDED

//
//  wo_ref_scalar_property.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/property/detail/wo_property_base.hpp>
#include <go/property/policy/ref.hpp>

namespace go
{
namespace property
{

template<class T, class S> class wo_ref_scalar_property
    : public detail::wo_property_base<T, policy::ref<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef policy::ref<T> policy_type;
    typedef wo_ref_scalar_property<value_type, string_type> this_type;

public:
    virtual ~wo_ref_scalar_property()
    {
    }

    wo_ref_scalar_property(const string_type& property_name)
        : detail::wo_property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    explicit wo_ref_scalar_property(const string_type& property_name, const value_type& v)
        : detail::wo_property_base<value_type, policy_type, string_type>(policy_type(v), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>

    bool empty() const
    {
        return detail::wo_property_base<value_type, policy_type, string_type>::storage().empty();
    }

    void clear()
    {
        return detail::wo_property_base<value_type, policy_type, string_type>::storage().clear();
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

} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_WO_REF_SCALAR_PROPERTY_HPP_INCLUDED
