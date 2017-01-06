#ifndef GO_BOOST_PROPERTY_NAMELESS_WRITE_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED
#define GO_BOOST_PROPERTY_NAMELESS_WRITE_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED

//
//  write_only_reference_property.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/property/nameless/detail/write_only_property_base.hpp>
#include <go_boost/property/policy/reference.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

namespace go_boost
{
namespace property
{
namespace nameless
{
namespace write_only
{

template<class T> class reference_property
    : public detail::property_base<T, policy::reference<T>>
{
public:
    typedef T value_type;
    typedef reference_property<value_type> this_type;
    typedef typename policy::reference<value_type> policy_type;

public:
    virtual ~reference_property()
    {
    }

    reference_property()
        : detail::property_base<value_type, policy::reference<value_type>>(policy::reference<value_type>())
    {
    }

    explicit reference_property(const value_type& v)
        : detail::property_base<value_type, policy::reference<value_type>>(policy::reference<value_type>(v))
    {
    }

#include <go_boost/property/detail/assignment_operator.hpp>

    bool empty() const
    {
        return detail::property_base<value_type, policy_type>::storage().empty();
    }

    void clear()
    {
        return detail::property_base<value_type, policy_type>::storage().clear();
    }

    BOOST_EXPLICIT_OPERATOR_BOOL()

        bool operator!() const
    {
        return empty();
    }
};

} // namespace write_only
} // namespace nameless
} // namespace property
} // namespace go_boost

#endif  // #ifndef GO_BOOST_PROPERTY_NAMELESS_WRITE_ONLY_REFERENCE_PROPERTY_HPP_INCLUDED