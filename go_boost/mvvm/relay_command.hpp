#ifndef GO_BOOST_MVVM_RELAY_COMMAND_HPP_INCLUDED
#define GO_BOOST_MVVM_RELAY_COMMAND_HPP_INCLUDED

//
//  relay_command.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/mvvm/command.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S>
class basic_relay_command
    : public basic_command<S>
{
public:
    typedef S string_type;
    typedef basic_relay_command<string_type> this_type;
    typedef boost::shared_ptr<this_type> ptr;
    typedef boost::weak_ptr<this_type> wptr;
    typedef typename basic_command<string_type>::command_parameters_type_ptr command_parameters_type_ptr;
    typedef boost::function<bool(const command_parameters_type_ptr&)> can_execute_command_signature;
    typedef boost::function<void(const command_parameters_type_ptr&)> execute_command_signature;

public:
    virtual ~basic_relay_command()
    {
    }

protected:
    basic_relay_command(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
        : basic_command<string_type>(cmd_name, params)
        , _can_execute(can_execute_command)
        , _execute(execute_command)
    {
    }

public:
    static ptr create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
    {
        return ptr(new basic_relay_command(cmd_name, execute_command, can_execute_command, params));
    }

private:
    virtual bool can_execute(const command_parameters_type_ptr& params)
    {
        return _can_execute.empty() ? true : _can_execute(params);
    }

    virtual void execute(const command_parameters_type_ptr& params)
    {
        if (!_execute.empty())
        {
            _execute(params);
        }
    }

private:
    can_execute_command_signature _can_execute;
    execute_command_signature _execute;
};

class relay_command
    : public basic_relay_command<std::string>
{
public:
    typedef std::string string_type;
    typedef relay_command this_type;

public:
    virtual ~relay_command()
    {
    }

protected:
    relay_command(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
        : basic_relay_command<string_type>(cmd_name, execute_command, can_execute_command, params)
    {
    }

public:
    static ptr create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
    {
        return ptr(new this_type(cmd_name, execute_command, can_execute_command, params));
    }
};

class relay_wcommand
    : public basic_relay_command<std::wstring>
{
public:
    typedef std::wstring string_type;
    typedef relay_wcommand this_type;

public:
    virtual ~relay_wcommand()
    {
    }

protected:
    relay_wcommand(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
        : basic_relay_command<string_type>(cmd_name, execute_command, can_execute_command, params)
    {
    }

public:
    static ptr create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
    {
        return ptr(new this_type(cmd_name, execute_command, can_execute_command, params));
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_RELAY_COMMAND_HPP_INCLUDED
