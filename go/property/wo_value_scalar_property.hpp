#ifndef GO_PROPERTY_WO_VALUE_SCALAR_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_WO_VALUE_SCALAR_PROPERTY_HPP_INCLUDED

//
//  wo_value_scalar_property.hpp
//
//  Copyright 2015 G�ran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/property/detail/wo_property_base.hpp>
#include <go/property/policy/value.hpp>
//#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/access.hpp>

namespace go
{
namespace property
{

template<class T, class S = std::string> class wo_value_scalar_property : public detail::wo_property_base<T, policy::value<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef wo_value_scalar_property<value_type, string_type> this_type;

public:
    virtual ~wo_value_scalar_property()
    {
    }

    wo_value_scalar_property(const string_type& property_name)
        : detail::wo_property_base<value_type, policy::value<value_type>, string_type>(policy::value<value_type>(), property_name)
    {
    }

    explicit wo_value_scalar_property(const string_type& property_name, const value_type& v)
        : detail::wo_property_base<value_type, policy::value<value_type>, string_type>(policy::value<value_type>(v), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>
};

} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_WO_VALUE_SCALAR_PROPERTY_HPP_INCLUDED
