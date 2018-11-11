#ifndef GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
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

#include <deque>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <go_boost/mvvm/notify_command_execution_interface.hpp>
#include <go_boost/utility/placebo_mutex.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, typename M> class basic_command_manager;
typedef basic_command_manager<std::string, boost::recursive_mutex> command_manager;
typedef basic_command_manager<std::wstring, boost::recursive_mutex> wcommand_manager;

namespace single_threaded
{

typedef basic_command_manager<std::string, go_boost::utility::placebo_mutex> command_manager;
typedef basic_command_manager<std::wstring, go_boost::utility::placebo_mutex> wcommand_manager;

}

template<class S, typename M = boost::recursive_mutex>
class basic_command_manager
    : public basic_notify_command_execution_interface<S, M>
    , private go_boost::utility::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef M mutex_type;
    typedef basic_command_manager<S, M> this_type;
    typedef typename boost::shared_ptr<basic_command_manager<S, M>> ptr;
    typedef typename boost::weak_ptr<basic_command_manager<S, M>> wptr;

public:
    virtual ~basic_command_manager();

protected:
    basic_command_manager();

public:
    static boost::shared_ptr<basic_command_manager<S, M>> create();

    void execute(const boost::shared_ptr<basic_command_interface<S, M>>& command) const;
    void post(const boost::shared_ptr<basic_command_interface<S, M>>& command, const bool keep_command_alive = false);
    void execute_commands();

    size_t commands() const;

private:
    mutable mutex_type _commands_guard;
    std::deque<std::pair<boost::weak_ptr<basic_command_interface<S, M>>, boost::shared_ptr<basic_command_interface<S, M>>>> _commands;
};

template<>
inline basic_command_manager<std::string, boost::recursive_mutex>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring, boost::recursive_mutex>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::string, go_boost::utility::placebo_mutex>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring, go_boost::utility::placebo_mutex>::~basic_command_manager()
{
    _commands.clear();
}

template<class S, typename M>
inline basic_command_manager<S, M>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::string, boost::recursive_mutex>::basic_command_manager()
    : basic_notify_command_execution_interface<std::string, boost::recursive_mutex>()
    , go_boost::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring, boost::recursive_mutex>::basic_command_manager()
    : basic_notify_command_execution_interface<std::wstring, boost::recursive_mutex>()
    , go_boost::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::string, go_boost::utility::placebo_mutex>::basic_command_manager()
    : basic_notify_command_execution_interface<std::string, go_boost::utility::placebo_mutex>()
    , go_boost::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring, go_boost::utility::placebo_mutex>::basic_command_manager()
    : basic_notify_command_execution_interface<std::wstring, go_boost::utility::placebo_mutex>()
    , go_boost::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<class S, typename M>
inline basic_command_manager<S, M>::basic_command_manager()
    : basic_notify_command_execution_interface<S, M>()
    , go_boost::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline void basic_command_manager<std::string, boost::recursive_mutex>::execute(const boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>& command) const
{
    if(command)
    {
        const boost::shared_ptr<command_parameters> params = command->parameters();
        if(command->can_execute(params))
        {
            command->execute(params);
            notify_command_executed(command);
        }
        else
        {
            notify_command_not_executed(command);
        }
    }
}

template<>
inline void basic_command_manager<std::wstring, boost::recursive_mutex>::execute(const boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>& command) const
{
    if(command)
    {
        const boost::shared_ptr<command_parameters> params = command->parameters();
        if(command->can_execute(params))
        {
            command->execute(params);
            notify_command_executed(command);
        }
        else
        {
            notify_command_not_executed(command);
        }
    }
}

template<>
inline void basic_command_manager<std::string, go_boost::utility::placebo_mutex>::execute(const boost::shared_ptr<basic_command_interface<std::string, go_boost::utility::placebo_mutex>>& command) const
{
    if (command)
    {
        const boost::shared_ptr<command_parameters> params = command->parameters();
        if (command->can_execute(params))
        {
            command->execute(params);
            notify_command_executed(command);
        }
        else
        {
            notify_command_not_executed(command);
        }
    }
}

template<>
inline void basic_command_manager<std::wstring, go_boost::utility::placebo_mutex>::execute(const boost::shared_ptr<basic_command_interface<std::wstring, go_boost::utility::placebo_mutex>>& command) const
{
    if (command)
    {
        const boost::shared_ptr<command_parameters> params = command->parameters();
        if (command->can_execute(params))
        {
            command->execute(params);
            notify_command_executed(command);
        }
        else
        {
            notify_command_not_executed(command);
        }
    }
}

template<class S, typename M>
inline void basic_command_manager<S, M>::execute(const boost::shared_ptr<basic_command_interface<S, M>>& command) const
{
    if(command)
    {
        const boost::shared_ptr<command_parameters> params = command->parameters();
        if(command->can_execute(params))
        {
            command->execute(params);
            basic_notify_command_execution_interface<S, M>::notify_command_executed(command);
        }
        else
        {
            basic_notify_command_execution_interface<S, M>::notify_command_not_executed(command);
        }
    }
}

template<>
inline void basic_command_manager<std::string, boost::recursive_mutex>::post(const boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<std::string, boost::recursive_mutex>>, boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>>(boost::weak_ptr<basic_command_interface<std::string, boost::recursive_mutex>>(command), keep_command_alive ? command : boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>()));
    }
}

template<>
inline void basic_command_manager<std::wstring, boost::recursive_mutex>::post(const boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>, boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>>(boost::weak_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>(command), keep_command_alive ? command : boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>()));
    }
}

template<>
inline void basic_command_manager<std::string, go_boost::utility::placebo_mutex>::post(const boost::shared_ptr<basic_command_interface<std::string, go_boost::utility::placebo_mutex>>& command, const bool keep_command_alive)
{
    if (command)
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<std::string, go_boost::utility::placebo_mutex>>, boost::shared_ptr<basic_command_interface<std::string, go_boost::utility::placebo_mutex>>>(boost::weak_ptr<basic_command_interface<std::string, go_boost::utility::placebo_mutex>>(command), keep_command_alive ? command : boost::shared_ptr<basic_command_interface<std::string, go_boost::utility::placebo_mutex>>()));
    }
}

template<>
inline void basic_command_manager<std::wstring, go_boost::utility::placebo_mutex>::post(const boost::shared_ptr<basic_command_interface<std::wstring, go_boost::utility::placebo_mutex>>& command, const bool keep_command_alive)
{
    if (command)
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<std::wstring, go_boost::utility::placebo_mutex>>, boost::shared_ptr<basic_command_interface<std::wstring, go_boost::utility::placebo_mutex>>>(boost::weak_ptr<basic_command_interface<std::wstring, go_boost::utility::placebo_mutex>>(command), keep_command_alive ? command : boost::shared_ptr<basic_command_interface<std::wstring, go_boost::utility::placebo_mutex>>()));
    }
}

template<class S, typename M>
inline void basic_command_manager<S, M>::post(const boost::shared_ptr<basic_command_interface<S, M>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<S, M>>, boost::shared_ptr<basic_command_interface<S, M>>>(boost::weak_ptr<basic_command_interface<S, M>>(command), keep_command_alive ? command : boost::shared_ptr<basic_command_interface<S, M>>()));
    }
}

template<>
inline void basic_command_manager<std::string, boost::recursive_mutex>::execute_commands()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_command_interface<std::string, boost::recursive_mutex>>, boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>>> command_list_type;
    command_list_type commands;
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(commands, _commands);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME command_list_type::value_type& wcommand, commands)
    {
        const boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>> command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline void basic_command_manager<std::wstring, boost::recursive_mutex>::execute_commands()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>, boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>>> command_list_type;
    command_list_type commands;
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(commands, _commands);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME command_list_type::value_type& wcommand, commands)
    {
        const boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>> command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline void basic_command_manager<std::string, go_boost::utility::placebo_mutex>::execute_commands()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_command_interface<std::string, go_boost::utility::placebo_mutex>>, boost::shared_ptr<basic_command_interface<std::string, go_boost::utility::placebo_mutex>>>> command_list_type;
    command_list_type commands;
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_commands_guard);
        std::swap(commands, _commands);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME command_list_type::value_type& wcommand, commands)
    {
        const boost::shared_ptr<basic_command_interface<std::string, go_boost::utility::placebo_mutex>> command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline void basic_command_manager<std::wstring, go_boost::utility::placebo_mutex>::execute_commands()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_command_interface<std::wstring, go_boost::utility::placebo_mutex>>, boost::shared_ptr<basic_command_interface<std::wstring, go_boost::utility::placebo_mutex>>>> command_list_type;
    command_list_type commands;
    {
        const go_boost::utility::placebo_mutex::scoped_lock lock(_commands_guard);
        std::swap(commands, _commands);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME command_list_type::value_type& wcommand, commands)
    {
        const boost::shared_ptr<basic_command_interface<std::wstring, go_boost::utility::placebo_mutex>> command = wcommand.first.lock();
        execute(command);
    }
}

template<class S, typename M>
inline void basic_command_manager<S, M>::execute_commands()
{
    typedef typename std::deque<std::pair<boost::weak_ptr<basic_command_interface<S, M>>, boost::shared_ptr<basic_command_interface<S, M>>>> command_list_type;
    command_list_type commands;
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(commands, _commands);
    }
    BOOST_FOREACH(const typename command_list_type::value_type& wcommand, commands)
    {
        const boost::shared_ptr<basic_command_interface<S, M>> command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline size_t basic_command_manager<std::string, boost::recursive_mutex>::commands() const
{
    const boost::recursive_mutex::scoped_lock lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::wstring, boost::recursive_mutex>::commands() const
{
    const boost::recursive_mutex::scoped_lock lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::string, go_boost::utility::placebo_mutex>::commands() const
{
    const go_boost::utility::placebo_mutex::scoped_lock lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::wstring, go_boost::utility::placebo_mutex>::commands() const
{
    const go_boost::utility::placebo_mutex::scoped_lock lock(_commands_guard);
    return _commands.size();
}

template<class S, typename M>
inline size_t basic_command_manager<S, M>::commands() const
{
    const boost::recursive_mutex::scoped_lock lock(_commands_guard);
    return _commands.size();
}

template<>
inline boost::shared_ptr<basic_command_manager<std::string, boost::recursive_mutex>> basic_command_manager<std::string, boost::recursive_mutex>::create()
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    return boost::make_shared<make_shared_enabler>();
#else
    return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_command_manager<std::wstring, boost::recursive_mutex>> basic_command_manager<std::wstring, boost::recursive_mutex>::create()
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    return boost::make_shared<make_shared_enabler>();
#else
    return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_command_manager<std::string, go_boost::utility::placebo_mutex>> basic_command_manager<std::string, go_boost::utility::placebo_mutex>::create()
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    return boost::make_shared<make_shared_enabler>();
#else
    return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_command_manager<std::wstring, go_boost::utility::placebo_mutex>> basic_command_manager<std::wstring, go_boost::utility::placebo_mutex>::create()
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    return boost::make_shared<make_shared_enabler>();
#else
    return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
}

template<class S, typename M>
inline boost::shared_ptr<basic_command_manager<S, M>> basic_command_manager<S, M>::create()
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    return boost::make_shared<make_shared_enabler>();
#else
    return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED
