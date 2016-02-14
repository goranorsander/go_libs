#ifndef GO_MVVM_RELAY_COMMAND_HPP_INCLUDED
#define GO_MVVM_RELAY_COMMAND_HPP_INCLUDED

//
//  relay_command.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/mvvm/command.hpp>

namespace go
{
namespace mvvm
{

template<class S = std::string>
class relay_command
    : public command<S>
{
public:
    typedef S string_type;
    typedef std::shared_ptr<relay_command<string_type>> ptr;
    typedef std::weak_ptr<relay_command<string_type>> wptr;
    typedef std::function<bool(const command_parameters_type_ptr&)> can_execute_command_signature;
    typedef std::function<void(const command_parameters_type_ptr&)> execute_command_signature;

public:
    virtual ~relay_command()
    {
    }

protected:
    relay_command(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
        : command<string_type>(cmd_name, params)
        , _can_execute(can_execute_command)
        , _execute(execute_command)
    {
    }

private:
    relay_command(const relay_command&) = delete;

public:
    static ptr create(const string_type& cmd_name, const execute_command_signature& execute_command, const can_execute_command_signature& can_execute_command, const command_parameters::ptr& params)
    {
        return ptr(new relay_command(cmd_name, execute_command, can_execute_command, params));
    }

private:
    virtual bool can_execute(const command_parameters_type_ptr& params)
    {
        return _can_execute ? _can_execute(params) : true;
    }

    virtual void execute(const command_parameters_type_ptr& params)
    {
        if (_execute)
        {
            _execute(params);
        }
    }

private:
    can_execute_command_signature _can_execute;
    execute_command_signature _execute;
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_RELAY_COMMAND_HPP_INCLUDED
