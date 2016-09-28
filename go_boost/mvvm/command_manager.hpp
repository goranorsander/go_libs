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

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <vector>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <go_boost/mvvm/notify_command_execution_interface.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S> class basic_command_manager;
typedef basic_command_manager<std::string> command_manager;
typedef basic_command_manager<std::wstring> wcommand_manager;

template<class S>
class basic_command_manager
    : public basic_notify_command_execution_interface<S>
    , private boost::noncopyable
{
public:
    typedef S string_type;
    typedef basic_command_manager<S> this_type;
    typedef typename boost::shared_ptr<basic_command_manager<S>> ptr;
    typedef typename boost::weak_ptr<basic_command_manager<S>> wptr;

public:
    virtual ~basic_command_manager();

protected:
    basic_command_manager();

public:
    static boost::shared_ptr<basic_command_manager<S>> create();

    void issue_command(const boost::shared_ptr<basic_command<S>>& cmd);

    void execute_commands();

    size_t commands() const;

private:
    mutable boost::recursive_mutex _commands_guard;
    std::vector<boost::weak_ptr<basic_command<S>>> _commands;
};

template<>
inline basic_command_manager<std::string>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring>::~basic_command_manager()
{
    _commands.clear();
}

template<class S>
inline basic_command_manager<S>::~basic_command_manager()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::string>::basic_command_manager()
    : basic_notify_command_execution_interface<std::string>()
    , boost::noncopyable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline basic_command_manager<std::wstring>::basic_command_manager()
    : basic_notify_command_execution_interface<std::wstring>()
    , boost::noncopyable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<class S>
inline basic_command_manager<S>::basic_command_manager()
    : basic_notify_command_execution_interface<S>()
    , boost::noncopyable()
    , _commands_guard()
    , _commands()
{
    _commands.clear();
}

template<>
inline boost::shared_ptr<basic_command_manager<std::string>> basic_command_manager<std::string>::create()
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public basic_command_manager<std::string>
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler() : basic_command_manager<std::string>() {}
    };

    return boost::make_shared<make_shared_enabler>();
#else
    return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_command_manager<std::wstring>> basic_command_manager<std::wstring>::create()
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public basic_command_manager<std::wstring>
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler() : basic_command_manager<std::wstring>() {}
    };

    return boost::make_shared<make_shared_enabler>();
#else
    return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
}

template<class S>
inline boost::shared_ptr<basic_command_manager<S>> basic_command_manager<S>::create()
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public basic_command_manager<S>
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler() : basic_command_manager<S>() {}
    };

    return boost::make_shared<make_shared_enabler>();
#else
    return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
}

template<>
inline void basic_command_manager<std::string>::issue_command(const boost::shared_ptr<basic_command<std::string>>& cmd)
{
    if(cmd)
    {
        boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(boost::weak_ptr<basic_command<std::string>>(cmd));
    }
}

template<>
inline void basic_command_manager<std::wstring>::issue_command(const boost::shared_ptr<basic_command<std::wstring>>& cmd)
{
    if(cmd)
    {
        boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(boost::weak_ptr<basic_command<std::wstring>>(cmd));
    }
}

template<class S>
inline void basic_command_manager<S>::issue_command(const boost::shared_ptr<basic_command<S>>& cmd)
{
    if(cmd)
    {
        boost::recursive_mutex::scoped_lock lock(_commands_guard);
        _commands.push_back(boost::weak_ptr<basic_command<S>>(cmd));
    }
}

template<>
inline void basic_command_manager<std::string>::execute_commands()
{
    std::vector<boost::weak_ptr<basic_command<std::string>>> cmds;
    {
        boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    BOOST_FOREACH(boost::weak_ptr<basic_command<std::string>> wcmd, cmds)
    {
        const boost::shared_ptr<basic_command<std::string>> cmd = wcmd.lock();
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
}

template<>
inline void basic_command_manager<std::wstring>::execute_commands()
{
    std::vector<boost::weak_ptr<basic_command<std::wstring>>> cmds;
    {
        boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    BOOST_FOREACH(boost::weak_ptr<basic_command<std::wstring>> wcmd, cmds)
    {
        const boost::shared_ptr<basic_command<std::wstring>> cmd = wcmd.lock();
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
}

template<class S>
inline void basic_command_manager<S>::execute_commands()
{
    std::vector<boost::weak_ptr<basic_command<S>>> cmds;
    {
        boost::recursive_mutex::scoped_lock lock(_commands_guard);
        std::swap(cmds, _commands);
    }
    BOOST_FOREACH(boost::weak_ptr<basic_command<S>> wcmd, cmds)
    {
        const boost::shared_ptr<basic_command<S>> cmd = wcmd.lock();
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
}

template<>
inline size_t basic_command_manager<std::string>::commands() const
{
    boost::recursive_mutex::scoped_lock lock(_commands_guard);
    return _commands.size();
}

template<>
inline size_t basic_command_manager<std::wstring>::commands() const
{
    boost::recursive_mutex::scoped_lock lock(_commands_guard);
    return _commands.size();
}

template<class S>
inline size_t basic_command_manager<S>::commands() const
{
    boost::recursive_mutex::scoped_lock lock(_commands_guard);
    return _commands.size();
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_COMMAND_MANAGER_HPP_INCLUDED
