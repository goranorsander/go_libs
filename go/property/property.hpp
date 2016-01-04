#ifndef GO_PROPERTY_PROPERTY_HPP_INCLUDED
#define GO_PROPERTY_PROPERTY_HPP_INCLUDED

//
//  property.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <go/property/detail/property_base.hpp>
#include <go/property/policy/proxy.hpp>
//#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/access.hpp>

namespace go
{
namespace property
{

template<class T, class S = std::string> class property : public detail::property_base<T, policy::proxy<T>, S>
{
public:
    typedef T value_type;
    typedef S string_type;
    typedef property<value_type, string_type> this_type;
    typedef std::function<value_type(void)> get_function_signature;
    typedef std::function<void(const value_type&)> set_function_signature;

public:
    virtual ~property()
    {
    }

    explicit property(const string_type& property_name)
        : detail::property_base<value_type, policy::proxy<value_type>, string_type>(policy::proxy<value_type>(), property_name)
    {
    }

    explicit property(const string_type& property_name, const get_function_signature& get_function, const set_function_signature& set_function)
        : detail::property_base<value_type, policy::proxy<value_type>, string_type>(policy::proxy<value_type>(get_function, set_function), property_name)
    {
    }

#include <go/property/detail/assignment_operator.hpp>

    void getter(const get_function_signature& f)
    {
        storage().getter(f);
    }

    void setter(const set_function_signature& f)
    {
        storage().setter(f);
    }
};

} // namespace property
} // namespace go

#endif  // #ifndef GO_PROPERTY_PROPERTY_HPP_INCLUDED
