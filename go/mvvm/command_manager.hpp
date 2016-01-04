#ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <vector>
//#include <boost/foreach.hpp>
#include <go/mvvm/command.hpp>
//#include <boost/noncopyable.hpp>
//#include <boost/thread.hpp>
#include <mutex>

namespace go
{
namespace mvvm
{

template<class S = std::string>
class command_manager
    : private boost::noncopyable
{
public:
    typedef S string_type;
    typedef boost::shared_ptr<command_manager<string_type>> ptr;
    typedef boost::signals2::signal<void(const string_type&)> requery_suggested_signal;

protected:
    typedef command<string_type> command_type;
    typedef boost::shared_ptr<command_type> command_type_ptr;
    typedef boost::weak_ptr<command_type> command_type_wptr;
    typedef std::vector<command_type_wptr> command_vector;

public:
    virtual ~command_manager()
    {
        _commands.clear();
    }

protected:
    command_manager()
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
        return ptr(new command_manager<string_type>());
    }

    void add_command(const command_type_ptr& cmd)
    {
        if(cmd)
        {
            std::recursive_mutex::scoped_lock lock(_commands_guard);
            _commands.push_back(command_type_wptr(cmd));
        }
    }

    void execute_commands()
    {
        command_vector cmds;
        {
            std::recursive_mutex::scoped_lock lock(_commands_guard);
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
        std::recursive_mutex::scoped_lock lock(_commands_guard);
        return _commands.size();
    }

private:
    mutable std::recursive_mutex _commands_guard;
    command_vector _commands;
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_COMMAND_MANAGER_HPP_INCLUDED
