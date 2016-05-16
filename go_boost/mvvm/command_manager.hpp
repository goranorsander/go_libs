#ifndef GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
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

#include <vector>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <go_boost/mvvm/command.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S>
class basic_command_manager
    : private boost::noncopyable
{
public:
    typedef typename S string_type;
    typedef typename basic_command_manager<string_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;
    typedef typename boost::signals2::signal<void(const string_type&)> requery_suggested_signal;

protected:
    typedef typename basic_command<string_type> command_type;
    typedef typename boost::shared_ptr<command_type> command_type_ptr;
    typedef typename boost::weak_ptr<command_type> command_type_wptr;
    typedef typename std::vector<command_type_wptr> command_vector;

public:
    virtual ~basic_command_manager()
    {
        _commands.clear();
    }

protected:
    basic_command_manager()
        : boost::noncopyable()
        , requery_suggested()
        , _commands_guard()
        , _commands()
    {
    }

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
            boost::recursive_mutex::scoped_lock lock(_commands_guard);
            _commands.push_back(command_type_wptr(cmd));
        }
    }

    void execute_commands()
    {
        command_vector cmds;
        {
            boost::recursive_mutex::scoped_lock lock(_commands_guard);
            std::swap(cmds, _commands);
        }
        BOOST_FOREACH(command_type_wptr wcmd, cmds)
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
        boost::recursive_mutex::scoped_lock lock(_commands_guard);
        return _commands.size();
    }

private:
    mutable boost::recursive_mutex _commands_guard;
    command_vector _commands;
};

class command_manager
    : public basic_command_manager<std::string>
{
public:
    typedef typename command_manager this_type;

public:
    virtual ~command_manager()
    {
    }

protected:
    command_manager()
        : basic_command_manager<string_type>()
    {
    }

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
    typedef typename wcommand_manager this_type;

public:
    virtual ~wcommand_manager()
    {
    }

protected:
    wcommand_manager()
        : basic_command_manager<string_type>()
    {
    }

public:
    static ptr create()
    {
        return ptr(new wcommand_manager());
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED
