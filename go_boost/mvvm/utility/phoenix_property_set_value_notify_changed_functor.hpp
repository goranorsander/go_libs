#ifndef GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_SET_VALUE_NOTIFY_CHANGED_FUNCTOR_HPP_INCLUDED
#define GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_SET_VALUE_NOTIFY_CHANGED_FUNCTOR_HPP_INCLUDED

//
//  phoenix_property_set_value_notify_changed_functor.hpp
//
//  Copyright 2015-2018 Göran Orsander
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

struct set_property_value_notify_changed_functor
{
    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3>
    struct result<This(const Arg1&, Arg2, Arg3&, const Arg3&)>
    {
        typedef void type;
    };

    template <typename Arg1, typename Arg2, typename Arg3>
    void operator()(const Arg1& property_name, Arg2 on_property_changed, Arg3& current_value, const Arg3& new_value) const
    {
        if(new_value != current_value)
        {
            current_value = new_value;
            on_property_changed(property_name);
        }
    }
};

static const boost::phoenix::function<set_property_value_notify_changed_functor> set_property_value_notify_changed;

} // namespace utility
} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_SET_VALUE_NOTIFY_CHANGED_FUNCTOR_HPP_INCLUDED
