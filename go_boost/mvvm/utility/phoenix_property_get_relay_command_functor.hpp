#ifndef GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_GET_RELAY_COMMAND_FUNCTOR_HPP_INCLUDED
#define GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_GET_RELAY_COMMAND_FUNCTOR_HPP_INCLUDED

//
//  phoenix_property_get_relay_command_functor.hpp
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

#include <string>
#include <boost/phoenix/phoenix.hpp>
#include <go_boost/utility/placebo_mutex.hpp>
#include <go_boost/utility/u8string.hpp>
#include <go_boost/utility/u16string.hpp>
#include <go_boost/utility/u32string.hpp>

namespace go_boost
{
namespace mvvm
{
namespace utility
{

struct get_property_relay_command_functor
{
    typedef std::string string_type;
    typedef boost::recursive_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if(!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

struct get_wproperty_relay_wcommand_functor
{
    typedef std::wstring string_type;
    typedef boost::recursive_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if(!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

struct get_u8property_relay_u8command_functor
{
    typedef go_boost::utility::u8string string_type;
    typedef boost::recursive_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if (!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

struct get_u16property_relay_u16command_functor
{
    typedef go_boost::utility::u16string string_type;
    typedef boost::recursive_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if (!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

struct get_u32property_relay_u32command_functor
{
    typedef go_boost::utility::u32string string_type;
    typedef boost::recursive_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if (!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

static const boost::phoenix::function<get_property_relay_command_functor> get_property_relay_command;
static const boost::phoenix::function<get_wproperty_relay_wcommand_functor> get_wproperty_relay_wcommand;
static const boost::phoenix::function<get_u8property_relay_u8command_functor> get_u8property_relay_u8command;
static const boost::phoenix::function<get_u16property_relay_u16command_functor> get_u16property_relay_u16command;
static const boost::phoenix::function<get_u32property_relay_u32command_functor> get_u32property_relay_u32command;

namespace single_threaded
{

struct get_property_relay_command_functor
{
    typedef std::string string_type;
    typedef go_boost::utility::placebo_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if(!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

struct get_wproperty_relay_wcommand_functor
{
    typedef std::wstring string_type;
    typedef go_boost::utility::placebo_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if(!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

struct get_u8property_relay_u8command_functor
{
    typedef go_boost::utility::u8string string_type;
    typedef go_boost::utility::placebo_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if (!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

struct get_u16property_relay_u16command_functor
{
    typedef go_boost::utility::u16string string_type;
    typedef go_boost::utility::placebo_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if (!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

struct get_u32property_relay_u32command_functor
{
    typedef go_boost::utility::u32string string_type;
    typedef go_boost::utility::placebo_mutex lockable_type;

    template <typename Sig>
    struct result;

    template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    struct result<This(const Arg1&, const Arg2&, const Arg3&, const Arg4&, Arg5&)>
    {
        typedef typename go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr type;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    go_boost::mvvm::basic_command_interface<string_type, lockable_type>::ptr operator()(const Arg1& cmd_name, const Arg2& execute_cmd, const Arg3& can_execute_cmd, const Arg4& params, Arg5& relay_cmd) const
    {
        if (!relay_cmd)
        {
            relay_cmd = go_boost::mvvm::basic_relay_command<string_type, lockable_type>::create(cmd_name, execute_cmd, can_execute_cmd, params);
        }
        return relay_cmd;
    }
};

static const boost::phoenix::function<get_property_relay_command_functor> get_property_relay_command;
static const boost::phoenix::function<get_wproperty_relay_wcommand_functor> get_wproperty_relay_wcommand;
static const boost::phoenix::function<get_u8property_relay_u8command_functor> get_u8property_relay_u8command;
static const boost::phoenix::function<get_u16property_relay_u16command_functor> get_u16property_relay_u16command;
static const boost::phoenix::function<get_u32property_relay_u32command_functor> get_u32property_relay_u32command;

}

} // namespace utility
} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_UTILITY_PHOENIX_PROPERTY_GET_RELAY_COMMAND_FUNCTOR_HPP_INCLUDED
