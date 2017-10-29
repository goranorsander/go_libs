#ifndef GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED
#define GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED

//
//  command_manager.hpp
//
//  Copyright 2015-2017 Göran Orsander
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
#include <boost/thread/recursive_mutex.hpp>
#include <go_boost/mvvm/notify_command_execution_interface.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, typename M> class basic_command_manager;
typedef basic_command_manager<std::string, boost::recursive_mutex> command_manager;
typedef basic_command_manager<std::wstring, boost::recursive_mutex> wcommand_manager;

template<class S, typename M>
class basic_command_manager
    : public basic_notify_command_execution_interface<S>
    , private go_boost::utility::noncopyable_nonmovable
{
public:
    typedef S string_type;
    typedef basic_command_manager<S, M> this_type;
    typedef typename boost::shared_ptr<basic_command_manager<S, M>> ptr;
    typedef typename boost::weak_ptr<basic_command_manager<S, M>> wptr;

public:
    virtual ~basic_command_manager();

protected:
    basic_command_manager();

public:
    static boost::shared_ptr<basic_command_manager<S, M>> create();

    void execute(const boost::shared_ptr<basic_command_interface<S, M>>& cmd) const;
    void post(const boost::shared_ptr<basic_command_interface<S, M>>& cmd, const bool keep_cmd_alive = false);
    void execute_commands();

    size_t commands() const;

private:
    mutable boost::recursive_mutex _commands_guard;
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

template<class S, typename M>
inline basic_command_manager<S, M>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::string, boost::recursive_mutex>::basic_command_manager()
    : basic_notify_command_execution_interface<std::string>()
    , go_boost::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring, boost::recursive_mutex>::basic_command_manager()
    : basic_notify_command_execution_interface<std::wstring>()
    , go_boost::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<class S, typename M>
inline basic_command_manager<S, M>::basic_command_manager()
    : basic_notify_command_execution_interface<S>()
    , go_boost::utility::noncopyable_nonmovable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline void basic_command_manager<std::string, boost::recursive_mutex>::execute(const boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>& cmd) const
{
    if(cmd)
    {
        const boost::shared_ptr<command_parameters> params = cmd->parameters();
        if(cmd->can_execute(params))
        {
            cmd->execute(params);
            command_executed(cmd);
        }
        else
        {
            command_not_executed(cmd);
        }
    }
}

template<>
inline void basic_command_manager<std::wstring, boost::recursive_mutex>::execute(const boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>& cmd) const
{
    if(cmd)
    {
        const boost::shared_ptr<command_parameters> params = cmd->parameters();
        if(cmd->can_execute(params))
        {
            cmd->execute(params);
            command_executed(cmd);
        }
        else
        {
            command_not_executed(cmd);
        }
    }
}

template<class S, typename M>
inline void basic_command_manager<S, M>::execute(const boost::shared_ptr<basic_command_interface<S, M>>& cmd) const
{
    if(cmd)
    {
        const boost::shared_ptr<command_parameters> params = cmd->parameters();
        if(cmd->can_execute(params))
        {
            cmd->execute(params);
            command_executed(cmd);
        }
        else
        {
            command_not_executed(cmd);
        }
    }
}

template<>
inline void basic_command_manager<std::string, boost::recursive_mutex>::post(const boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>& cmd, const bool keep_cmd_alive)
{
    if(cmd)
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<std::string, boost::recursive_mutex>>, boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>>(boost::weak_ptr<basic_command_interface<std::string, boost::recursive_mutex>>(cmd), keep_cmd_alive ? cmd : boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>()));
    }
}

template<>
inline void basic_command_manager<std::wstring, boost::recursive_mutex>::post(const boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>& cmd, const bool keep_cmd_alive)
{
    if(cmd)
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>, boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>>(boost::weak_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>(cmd), keep_cmd_alive ? cmd : boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>()));
    }
}

template<class S, typename M>
inline void basic_command_manager<S, M>::post(const boost::shared_ptr<basic_command_interface<S, M>>& cmd, const bool keep_cmd_alive)
{
    if(cmd)
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(std::pair<boost::weak_ptr<basic_command_interface<S, M>>, boost::shared_ptr<basic_command_interface<S, M>>>(boost::weak_ptr<basic_command_interface<S, M>>(cmd), keep_cmd_alive ? cmd : boost::shared_ptr<basic_command_interface<S, M>>()));
    }
}

template<>
inline void basic_command_manager<std::string, boost::recursive_mutex>::execute_commands()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_command_interface<std::string, boost::recursive_mutex>>, boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>>>> cmd_list_type;
    cmd_list_type cmds;
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME cmd_list_type::value_type& wcmd, cmds)
    {
        const boost::shared_ptr<basic_command_interface<std::string, boost::recursive_mutex>> cmd = wcmd.first.lock();
        execute(cmd);
    }
}

template<>
inline void basic_command_manager<std::wstring, boost::recursive_mutex>::execute_commands()
{
    typedef GO_BOOST_TYPENAME std::deque<std::pair<boost::weak_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>, boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>>>> cmd_list_type;
    cmd_list_type cmds;
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    BOOST_FOREACH(const GO_BOOST_TYPENAME cmd_list_type::value_type& wcmd, cmds)
    {
        const boost::shared_ptr<basic_command_interface<std::wstring, boost::recursive_mutex>> cmd = wcmd.first.lock();
        execute(cmd);
    }
}

template<class S, typename M>
inline void basic_command_manager<S, M>::execute_commands()
{
    typedef typename std::deque<std::pair<boost::weak_ptr<basic_command_interface<S, M>>, boost::shared_ptr<basic_command_interface<S, M>>>> cmd_list_type;
    cmd_list_type cmds;
    {
        const boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    BOOST_FOREACH(const typename cmd_list_type::value_type& wcmd, cmds)
    {
        const boost::shared_ptr<basic_command_interface<S, M>> cmd = wcmd.first.lock();
        execute(cmd);
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
