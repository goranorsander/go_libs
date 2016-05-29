#ifndef GO_MVVM_RELAY_COMMAND_HPP_INCLUDED
#define GO_MVVM_RELAY_COMMAND_HPP_INCLUDED

//
//  relay_command.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/command.hpp>

namespace go
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
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;
    typedef typename std::function<bool(const std::shared_ptr<command_parameters>&)> can_execute_command_signature;
    typedef typename std::function<void(const std::shared_ptr<command_parameters>&)> execute_command_signature;

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

private:
    basic_relay_command(const this_type&) = delete;

public:
    static ptr create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
    {
        return ptr(new this_type(cmd_name, execute_command, can_execute_command, params));
    }

private:
    virtual bool can_execute(const std::shared_ptr<command_parameters>& params)
    {
        return _can_execute ? _can_execute(params) : true;
    }

    virtual void execute(const std::shared_ptr<command_parameters>& params)
    {
        if(_execute)
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

private:
    relay_command(const this_type&) = delete;

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

private:
    relay_wcommand(const this_type&) = delete;

public:
    static ptr create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
    {
        return ptr(new this_type(cmd_name, execute_command, can_execute_command, params));
    }
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_RELAY_COMMAND_HPP_INCLUDED
