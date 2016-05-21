#ifndef GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_GET_RELAY_COMMAND_FUNCTOR_HPP_INCLUDED
#define GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_GET_RELAY_COMMAND_FUNCTOR_HPP_INCLUDED

//
//  phoenix_property_get_relay_command_functor.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/phoenix/phoenix.hpp>

namespace go_boost
{
namespace mvvm
{
namespace utility
{

struct get_property_relay_command_functor
{
    typedef typename std::string string_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::command::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::command::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if(!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::relay_command::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

struct get_wproperty_relay_wcommand_functor
{
    typedef typename std::wstring string_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::wcommand::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::wcommand::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if(!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::relay_wcommand::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

static const boost::phoenix::function<get_property_relay_command_functor> get_property_relay_command;
static const boost::phoenix::function<get_wproperty_relay_wcommand_functor> get_wproperty_relay_wcommand;

} // namespace utility
} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_GET_RELAY_COMMAND_FUNCTOR_HPP_INCLUDED
