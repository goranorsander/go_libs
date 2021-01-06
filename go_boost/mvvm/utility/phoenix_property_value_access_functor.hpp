#ifndef GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_VALUE_ACCESS_FUNCTOR_HPP_INCLUDED
#define GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_VALUE_ACCESS_FUNCTOR_HPP_INCLUDED

//
//  phoenix_property_value_access_functor.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/phoenix/phoenix.hpp>

namespace go_boost
{
namespace mvvm
{
namespace utility
{

struct get_property_value_functor
{
    template <typename Sig>
    struct result;

    template <typename This, class Arg>
    struct result<This(const Arg&)>
    {
        typedef Arg type;
    };

    template <typename Arg>
    Arg operator()(const Arg& current_value) const
    {
        return current_value;
    }
};

struct set_property_value_functor
{
    template <typename Sig>
    struct result;

    template <typename This, typename Arg>
    struct result<This(Arg&, const Arg&)>
    {
        typedef void type;
    };

    template <typename Arg>
    void operator()(Arg& current_value, const Arg& new_value) const
    {
        if(new_value != current_value)
        {
            current_value = new_value;
        }
    }
};

static const boost::phoenix::function<get_property_value_functor> get_property_value;
static const boost::phoenix::function<set_property_value_functor> set_property_value;

} // namespace utility
} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_VALUE_ACCESS_FUNCTOR_HPP_INCLUDED
