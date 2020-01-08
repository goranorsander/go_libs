#ifndef GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
//
//  Copyright 2015-2020 Göran Orsander
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
#include <go_boost/async/placebo_lockable.hpp>
#include <go_boost/mvvm/notify_command_execution_interface.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class L> class basic_command_manager;
typedef basic_command_manager<std::string, boost::recursive_mutex> command_manager;
typedef basic_command_manager<std::wstring, boost::recursive_mutex> wcommand_manager;

namespace single_threaded
{

typedef basic_command_manager<std::string, go_boost::async::placebo_lockable> command_manager;
typedef basic_command_manager<std::wstring, go_boost::async::placebo_lockable> wcommand_manager;

}

template<class S, class L = boost::recursive_mutex>
class basic_command_manager
    : public basic_notify_command_execution_interface<S, L>
    , private go_boost::type_traits::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_command_manager<S, L> this_type;
    typedef typename boost::shared_ptr<basic_command_manager<S, L>> ptr;
    typedef typename boost::weak_ptr<basic_command_manager<S, L>> wptr;

public:
    virtual ~basic_command_manager();

protected:
    basic_command_manager();

public:
    static boost::shared_ptr<basic_command_manager<S, L>> create();

    void execute(const boost::shared_ptr<basic_command_interface<S, L>>& command) const;
    void post(const boost::shared_ptr<basic_command_interface<S, L>>& command, const bool keep_command_alive = false);
    void execute_commands();

    size_t commands() const;

private:
    mutable lockable_type _commands_guard;
    std::deque<std::pair<boost::weak_ptr<basic_command_interface<S, L>>, boost::shared_ptr<basic_command_interface<S, L>>>> _commands;
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
inline basic_command_manager<std::string, go_boost::async::placebo_lockable>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring, go_boost::async::placebo_lockable>::~basic_command_manager()
{
    _commands.clear();
}

template<class S, class L>
inline basic_command_manager<S, L>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::string, boost::recursive_mutex>::basic_command_manager()
    : basic_notify_command_execution_interface<std::string, boost::recursive_mutex>()
    , go_boost::type_traits::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring, boost::recursive_mutex>::basic_command_manager()
    : basic_notify_command_execution_interface<std::wstring, boost::recursive_mutex>()
    , go_boost::type_traits::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::string, go_boost::async::placebo_lockable>::basic_command_manager()
    : basic_notify_command_execution_interface<std::string, go_boost::async::placebo_lockable>()
    , go_boost::type_traits::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring, go_boost::async::placebo_lockable>::basic_command_manager()
    : basic_notify_command_execution_interface<std::wstring, go_boost::async::placebo_lockable>()
    , go_boost::type_traits::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<class S, class L>
inline basic_command_manager<S, L>::basic_command_manager()
    : basic_notify_command_execution_interface<S, L>()
    , go_boost::type_traits::noncopyable_nonmovable()
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
inline void basic_command_manager<std::string, go_boost::async::placebo_lockable>::execute(const boost::shared_ptr<basic_command_interface<std::string, go_boost::async::placebo_lockable>>& command) const
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
inline void basic_command_manager<std::wstring, go_boost::async::placebo_lockable>::execute(const boost::shared_ptr<basic_command_interface<std::wstring, go_boost::async::placebo_lockable>>& command) const
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

template<class S, class L>
inline void basic_command_manager<S, L>::execute(const boost::shared_ptr<basic_command_interface<S, L>>& command) const
{
    if(command)
    {
        const boost::shared_ptr<command_parameters> params = command->parameters();
        if(command->can_execute(params))
        {
            command->execute(params);
            basic_notify_command_execution_interface<S, L>::notify_command_executed(command);
        }
        else
        {
            basic_notify_command_execution_interface<S, L>::notify_command_not_executed(command);
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
inline void basic_command_manager<std::string, go_boost::async::placebo_lockable>::post(const boost::shared_ptr<basic_command_interface<std::string, go_boost::async::placebo_lockable>>& command, const bool keep_command_alive)
{
    if (command)
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<std::string, go_boost::async::placebo_lockable>>, boost::shared_ptr<basic_command_interface<std::string, go_boost::async::placebo_lockable>>>(boost::weak_ptr<basic_command_interface<std::string, go_boost::async::placebo_lockable>>(command), keep_command_alive ? command : boost::shared_ptr<basic_command_interface<std::string, go_boost::async::placebo_lockable>>()));
    }
}

template<>
inline void basic_command_manager<std::wstring, go_boost::async::placebo_lockable>::post(const boost::shared_ptr<basic_command_interface<std::wstring, go_boost::async::placebo_lockable>>& command, const bool keep_command_alive)
{
    if (command)
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<std::wstring, go_boost::async::placebo_lockable>>, boost::shared_ptr<basic_command_interface<std::wstring, go_boost::async::placebo_lockable>>>(boost::weak_ptr<basic_command_interface<std::wstring, go_boost::async::placebo_lockable>>(command), keep_command_alive ? command : boost::shared_ptr<basic_command_interface<std::wstring, go_boost::async::placebo_lockable>>()));
    }
}

template<class S, class L>
inline void basic_command_manager<S, L>::post(const boost::shared_ptr<basic_command_interface<S, L>>& command, const bool keep_command_alive)
{
    if(command)
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<S, L>>, boost::shared_ptr<basic_command_interface<S, L>>>(boost::weak_ptr<basic_command_interface<S, L>>(command), keep_command_alive ? command : boost::shared_ptr<basic_command_interface<S, L>>()));
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
inline void basic_command_manager<std::string, go_boost::async::placebo_lockable>::execute_commands()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_command_interface<std::string, go_boost::async::placebo_lockable>>, boost::shared_ptr<basic_command_interface<std::string, go_boost::async::placebo_lockable>>>> command_list_type;
    command_list_type commands;
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_commands_guard);
        std::swap(commands, _commands);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME command_list_type::value_type& wcommand, commands)
    {
        const boost::shared_ptr<basic_command_interface<std::string, go_boost::async::placebo_lockable>> command = wcommand.first.lock();
        execute(command);
    }
}

template<>
inline void basic_command_manager<std::wstring, go_boost::async::placebo_lockable>::execute_commands()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_command_interface<std::wstring, go_boost::async::placebo_lockable>>, boost::shared_ptr<basic_command_interface<std::wstring, go_boost::async::placebo_lockable>>>> command_list_type;
    command_list_type commands;
    {
        const go_boost::async::placebo_lockable::scoped_lock lock(_commands_guard);
        std::swap(commands, _commands);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME command_list_type::value_type& wcommand, commands)
    {
        const boost::shared_ptr<basic_command_interface<std::wstring, go_boost::async::placebo_lockable>> command = wcommand.first.lock();
        execute(command);
    }
}

template<class S, class L>
inline void basic_command_manager<S, L>::execute_commands()
{
    typedef typename std::deque<std::pair<boost::weak_ptr<basic_command_interface<S, L>>, boost::shared_ptr<basic_command_interface<S, L>>>> command_list_type;
    command_list_type commands;
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(commands, _commands);
    }
    BOOST_FOREACH(const typename command_list_type::value_type& wcommand, commands)
    {
        const boost::shared_ptr<basic_command_interface<S, L>> command = wcommand.first.lock();
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
inline size_t basic_command_manager<std::string, go_boost::async::placebo_lockable>::commands() const
{
    const go_boost::async::placebo_lockable::scoped_lock lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::wstring, go_boost::async::placebo_lockable>::commands() const
{
    const go_boost::async::placebo_lockable::scoped_lock lock(_commands_guard);
    return _commands.size();
}

template<class S, class L>
inline size_t basic_command_manager<S, L>::commands() const
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
inline boost::shared_ptr<basic_command_manager<std::string, go_boost::async::placebo_lockable>> basic_command_manager<std::string, go_boost::async::placebo_lockable>::create()
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
inline boost::shared_ptr<basic_command_manager<std::wstring, go_boost::async::placebo_lockable>> basic_command_manager<std::wstring, go_boost::async::placebo_lockable>::create()
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

template<class S, class L>
inline boost::shared_ptr<basic_command_manager<S, L>> basic_command_manager<S, L>::create()
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
