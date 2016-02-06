#ifndef GO_PROPERTY_WO_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_WO_PROPERTY_HPP_INCLUDED

//
//  wo_property.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/property/detail/wo_property_base.hpp>
#include <go/property/policy/proxy.hpp>

namespace go
{
namespace property
{

template<class T, class S = std::string> class wo_property
    : public detail::wo_property_base<T, policy::proxy<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef wo_property<value_type, string_type> this_type;
    typedef std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~wo_property()
    {
    }

    wo_property(const string_type& property_name)
        : detail::wo_property_base<value_type, policy::proxy<value_type>, string_type>(policy::proxy<value_type>(), property_name)
    {
    }

    explicit wo_property(const string_type& property_name, const set_function_signature& set_function)
        : detail::wo_property_base<value_type, policy::proxy<value_type>, string_type>(policy::proxy<value_type>(nullptr, set_function), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>

    void setter(const set_function_signature& f)
    {
        storage().setter(f);
    }
};

} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_WO_PROPERTY_HPP_INCLUDED
