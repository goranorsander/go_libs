#ifndef GO_PROPERTY_RO_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_RO_PROPERTY_HPP_INCLUDED

//
//  ro_property.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/property/detail/ro_property_base.hpp>
#include <go/property/policy/proxy.hpp>

namespace go
{
namespace property
{

template<class T, class S = std::string> class ro_property
    : public detail::ro_property_base<T, policy::proxy<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef policy::proxy<T> policy_type;
    typedef ro_property<value_type, string_type> this_type;
    typedef std::function<value_type(void)> get_function_signature;

public:
    virtual ~ro_property()
    {
    }

    ro_property(const string_type& property_name)
        : detail::ro_property_base<value_type, policy_type, string_type>(policy_type(), property_name)
    {
    }

    explicit ro_property(const string_type& property_name, const get_function_signature& get_function)
        : detail::ro_property_base<value_type, policy_type, string_type>(policy_type(get_function, nullptr), property_name)
    {
    }

    void getter(const get_function_signature& f)
    {
        const_cast<policy_type&>(detail::ro_property_base<value_type, policy_type, string_type>::storage()).getter(f);
    }
};

} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_RO_PROPERTY_HPP_INCLUDED
