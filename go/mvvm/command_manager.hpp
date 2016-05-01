#ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <mutex>
#include <vector>
#include <go/mvvm/command.hpp>

namespace go
{
namespace mvvm
{

template<class S>
class basic_command_manager
{
public:
    typedef S string_type;
    typedef basic_command_manager<string_type> this_type;
    typedef std::shared_ptr<this_type> ptr;
    typedef std::weak_ptr<this_type> wptr;
    typedef go::signals::signal<std::function<void(const string_type&)>> requery_suggested_signal;

protected:
    typedef basic_command<string_type> command_type;
    typedef std::shared_ptr<command_type> command_type_ptr;
    typedef std::weak_ptr<command_type> command_type_wptr;
    typedef std::vector<command_type_wptr> command_vector;

public:
    virtual ~basic_command_manager()
    {
        _commands.clear();
    }

protected:
    basic_command_manager()
        : requery_suggested()
        , _commands_guard()
        , _commands()
    {
    }

private:
    basic_command_manager(const basic_command_manager&) = delete;

public:
    requery_suggested_signal requery_suggested;

public:
    static ptr create()
    {
        return ptr(new this_type());
    }

    void add_command(const command_type_ptr& cmd)
    {
        if(cmd)
        {
            std::lock_guard<std::recursive_mutex> lock(_commands_guard);
            _commands.push_back(command_type_wptr(cmd));
        }
    }

    void execute_commands()
    {
        command_vector cmds;
        {
            std::lock_guard<std::recursive_mutex> lock(_commands_guard);
            std::swap(cmds, _commands);
        }
        for(command_type_wptr wcmd: cmds)
        {
            const command_type_ptr cmd = wcmd.lock();
            if(cmd)
            {
                const command_parameters::ptr params = cmd->parameters();
                if(cmd->can_execute(params))
                {
                    cmd->execute(params);
                }
            }
        }
    }

    size_t commands() const
    {
        std::lock_guard<std::recursive_mutex> lock(_commands_guard);
        return _commands.size();
    }

private:
    mutable std::recursive_mutex _commands_guard;
    command_vector _commands;
};

class command_manager
    : public basic_command_manager<std::string>
{
public:
    typedef command_manager this_type;

public:
    virtual ~command_manager()
    {
    }

protected:
    command_manager()
        : basic_command_manager<string_type>()
    {
    }

private:
    command_manager(const command_manager&) = delete;

public:
    static ptr create()
    {
        return ptr(new command_manager());
    }
};

class wcommand_manager
    : public basic_command_manager<std::wstring>
{
public:
    typedef wcommand_manager this_type;

public:
    virtual ~wcommand_manager()
    {
    }

protected:
    wcommand_manager()
        : basic_command_manager<string_type>()
    {
    }

private:
    wcommand_manager(const wcommand_manager&) = delete;

public:
    static ptr create()
    {
        return ptr(new wcommand_manager());
    }
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
